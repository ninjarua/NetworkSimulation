/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineSimulator.h"
#include "GridGenerator.h"
#include "TorusGridGenerator.h"
#include "FixedRangeGenerator.h"
#include "ERRandomGenerator.h"
#include "ScaleFreeGenerator.h"
#include "SmallworldGenerator.h"
#include "K01Tolerance.h"
#include "K04Tolerance.h"
#include "KxHopTolerance.h"
#include "C01Tolerance.h"
#include "C01K03Tolerance.h"
#include "CxHopTolerance.h"

using namespace generators;

#include <iostream>

namespace simulators {

ByzantineSimulator::ByzantineSimulator() : SimulatorBase() {
	byzantine = ByzantineProtocol(0.5, 0.5);
}

ByzantineSimulator::~ByzantineSimulator() {

}

void ByzantineSimulator::setTolerance(TypeOfTolerance toleranceType, DeployingType deployingType, int networkSize, int hopCount)
{
	setDeployment(deployingType, networkSize);
	switch(toleranceType)
	{
	case K01:
		byzantine.tolerance = new K01Tolerance();
		break;
	case K04:
		byzantine.tolerance = new K04Tolerance();
		break;
	case KxHop:
		byzantine.tolerance = new KxHopTolerance(hopCount);
		break;
	case C01:
		byzantine.tolerance = new C01Tolerance();
		break;
	case C01K03:
		byzantine.tolerance = new C01K03Tolerance();
		break;
	case CxHop:
		byzantine.tolerance = new CxHopTolerance();
		generator->turnOn2HopInfo(true);
		break;
	default:
		byzantine.tolerance = new ToleranceBase();
		break;
	}
}

void ByzantineSimulator::setDeployment(DeployingType deployingType, int networkSize)
{
	switch(deployingType)
	{
	case Grid:
		generator = new GridGenerator(networkSize);
		break;
	case TorusGrid:
		generator = new TorusGridGenerator(networkSize);
		break;
	case FixedRange:
		generator = new FixedRangeGenerator();
		break;
	case Small_world:
		generator = new SmallworldGenerator();
		break;
	case Ring:
		break;
	case ScaleFree:
		generator = new ScaleFreeGenerator();
		break;
	case ER_Random:
		generator = new ERRandomGenerator();
		break;
	default:
		break;
	}
}

bool ByzantineSimulator::runSimulationStep(bool draw)
{
	bool stop = byzantine.RunStepCheckFinish(network, &Network::noNewMessageInNetwork);
	//_networkGraphics.DrawNetwork(_network, false, false, true);
	return stop;
}

void ByzantineSimulator::addOneStepReport()
{
	byzantine.report->byzantineProb = byzantine.byzantineProb;
	byzantine.report->AddByzantineValue(byzantine.statisticInfo->infections);
	byzantine.report->AddSacrificeValue(byzantine.statisticInfo->inactives);
	byzantine.report->AddDetectorValue(byzantine.statisticInfo->detectors);
	byzantine.report->AddNormalValue(byzantine.statisticInfo->sanes);
	byzantine.report->AddLargestConnectedAreaValue(byzantine.statisticInfo->lca);
	byzantine.report->AddDegrees(byzantine.statisticInfo->degree);
	byzantine.report->AddDiameters(byzantine.statisticInfo->diameter);
}

ByzantineReport* ByzantineSimulator::finishReport()
{
	byzantine.report->Clear();
	addOneStepReport();
	byzantine.report->Summarize(0.05);
	return byzantine.report;
}

bool ByzantineSimulator::stopPrediction(ByzantineReport* report)
{
    bool averageCondition = (report->ciOfByzantines < .8)
        && (report->ciOfNormals < 0.01 || (report->ciOfNormals < .8 && report->ciOfNormals <= report->averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::convert2HopInformation(DeployingType deployingType,
		string inputfolder, string outputFolder, int sampleSize)
{
	setDeployment(deployingType, 1000);
	setParameters(1, inputfolder, outputFolder, 0, 0, 0, 0, 0.01, 0.01, sampleSize);

	for (int i = 0; i <= 100; i++)
	{
		bool result = generator->generateFromFiles(network, params.inputFolder, i);
		if (result)
			generator->writeNetworkToFile(network, params.outputFolder, i);
	}
}

void ByzantineSimulator::runSimulationByInterval()
{
	byzantine.report->Clear();
	byzantine.report->nothingProb = byzantine.nothingProb;
	int times = params.totalTimes;
	if (byzantine.nothingProb + byzantine.byzantineProb > 0.99)
		times = 2;
	int prediction;
	int predictionIt = 1000;
	if (times < predictionIt)
	{
		prediction = times;
		predictionIt = times;
	}
	else
	{
		prediction = predictionIt;
	}
	int sampleRepeat = (predictionIt > params.sampleSize) ? (int)((double) predictionIt/params.sampleSize) : 1;
	int count = 0;
	while (count < times)
	{
		int sampleId = 0;
		while (count < prediction)
		{
			bool result = generator->generateFromFiles(network, params.inputFolder, sampleId);
			if (!result)
				return;
			int i = 0;
			while (i < sampleRepeat)
			{
				byzantine.Refresh(network);
				byzantine.RunFault(network);
				addOneStepReport();
				count++;
				i++;
			}
			sampleId++;
		}
		byzantine.report->Summarize(0.05);
		if (stopPrediction(byzantine.report))
			times = prediction;	// reduce the running time and quit
		else
			prediction += 1000;
	}
}

void ByzantineSimulator::printToFile(ByzantineReport& report, string filename)
{
	filesystem::path dir(params.outputFolder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(params.outputFolder + OS_SEP + filename);
	Logger::Write(report, file.string(), ofstream::out | ofstream::app);
}

string ByzantineSimulator::getResultFilename(double nothingProb, double byzantineProb)
{
	string filename = generator->getDeployingName();
	filename += "_";
	filename += byzantine.tolerance->GetToleranceName();

	char number[11];
		sprintf(number, "_%.2f_%.2f", nothingProb, byzantineProb);

	filename += number;
	filename += ".out";
	return filename;
}

void ByzantineSimulator::setParameters(int totalTimes, string inputFolder, string outputFolder,
			double startingNothing, double startingByzantine,
			double endingNothing, double endingByzantine,
			double intervalByz, double intervalNothing, int sampleSize)
{
	int intervalNothingI = (int)(intervalNothing * 100);
	int intervalByzI = (int)(intervalByz * 100);
	params.totalTimes = totalTimes;
	params.nothingSteps = (int)(100 / intervalNothingI);;
	params.byzantineSteps = (int)(100 / intervalByzI);
	params.nothingStart = (int)(round(startingNothing * 100) / intervalNothingI);
	params.byzantineStart = (int)(round(startingByzantine * 100) / intervalByzI);
	params.nothingEnd = (int)(round(endingNothing * 100) / intervalNothingI);
	params.byzantineEnd = (int)(round(endingByzantine * 100) / intervalByzI);
	params.sampleSize = sampleSize;
	params.inputFolder = inputFolder;
	params.outputFolder = outputFolder;
}

void ByzantineSimulator::read(DeployingType deployingType, TypeOfTolerance toleranceType,
		string resultsFolder, string outputFilename,
		double startingNothing, double startingByz,
		double intervalByz, double intervalNothing)
{
	setTolerance(toleranceType, deployingType, 100);
	int nothingStart = (int)(round(startingNothing * 100) / (int)(intervalNothing * 100));
	int byzantineStart = (int)(round(startingByz * 100) / (int)(intervalByz * 100));

	filesystem::path dir(resultsFolder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(resultsFolder + OS_SEP + getResultFilename(nothingStart, byzantineStart));
	if (filesystem::exists(file))
		Logger::Copy(file.string(), outputFilename, false);
}

void ByzantineSimulator::readOneStep(DeployingType deployingType, TypeOfTolerance toleranceType,
			string resultsFolder, string outputFilename, double nothingProb, double intervalByz)
{
	int byzantingEndI = 100 - nothingProb;
	for (int i = 0; i <= byzantingEndI; i++)
		read(deployingType, toleranceType, resultsFolder, outputFilename, nothingProb, i * intervalByz);
}

void ByzantineSimulator::runReaderByThreadId(DeployingType deployingType, TypeOfTolerance toleranceType, int threadId, int totalThread,
		string resultsFolder, string outputFilename, bool isFirstInSlot, double intervalNothing)
{
	int slotSize = 50 / totalThread;
	double startingNothing1 = intervalNothing * threadId * slotSize;
	double endingNothing1 = startingNothing1 + ((slotSize - 1) * intervalNothing);
	double startingNothing2 = (99 - (endingNothing1 * 100))/100;
	char number[5];
	sprintf(number, "%d", threadId);
	string inputDir = resultsFolder + OS_SEP + number;
	if (isFirstInSlot)
		read(deployingType, toleranceType, inputDir, outputFilename, startingNothing1, 0);
	else
		read(deployingType, toleranceType, inputDir, outputFilename, startingNothing2, 0);
}

void ByzantineSimulator::runOneStep(double byzantineProb, double nothingProb, int times)
{
	byzantine.Initialize(network, byzantineProb, nothingProb);
	runSimulationByInterval();
	printToFile(*byzantine.report, getResultFilename(params.nothingStart, params.byzantineStart));
}

void ByzantineSimulator::runSimulation(DeployingType deployingType, TypeOfTolerance toleranceType,
		int hopCount, int times,
		string inputfolder, string outputFolder,
		double startingNothing, double startingByzantine,
		double endingNothing, double endingByzantine,
		double intervalByz, double intervalNothing,
		int sampleSize, int networkSize)
{
	setTolerance(toleranceType, deployingType, networkSize, hopCount);
	setParameters(times, inputfolder, outputFolder, startingNothing, startingByzantine, endingNothing,
			endingByzantine, intervalByz, intervalNothing, sampleSize);
	//double ratio = round((double) params.nothingSteps / params.byzantineSteps);
	if (params.nothingStart == params.nothingEnd)
	{
		for (int j = params.byzantineStart; j <= params.byzantineEnd; j++)
		{
			runOneStep(j * intervalByz, params.nothingStart * intervalNothing, times);
		}
	}
	else
	{
		for (int j = params.byzantineStart; j <= params.nothingSteps - params.nothingStart; j++)
			// (int)((params.nothingSteps - params.nothingStart)/ratio); j++)
			runOneStep(j * intervalByz, params.nothingStart * intervalNothing, times);
		for (int i = params.nothingStart + 1; i < params.nothingEnd && i < params.nothingSteps; i++)
		{
			for (int j = 0; j <= params.nothingSteps - i; j++)// / ratio); j++)
				runOneStep(j * intervalByz, i * intervalNothing, times);
		}
		for (int j = 0; j <= params.byzantineEnd && j <= params.nothingSteps - params.nothingEnd; j++)
		//(int)((params.nothingSteps - params.nothingEnd) / ratio); j++)
			runOneStep(j * intervalByz, params.nothingEnd * intervalNothing, times);
	}
}

void ByzantineSimulator::runSimulationByThreadId(DeployingType deployingType, TypeOfTolerance toleranceType,
		int hopCount, int threadId, int totalThread, int totalTimes,
		string inputFolder, string outputFolder,
		double intervalByz, double intervalNothing, int sampleSize, int networkSize)
{
	int slotSize = 50 / totalThread;
	double startingNothing1 = intervalNothing * threadId * slotSize;
	double endingNothing1 = startingNothing1 + ((slotSize - 1) * intervalNothing);
	double startingNothing2 = (99 - (endingNothing1 * 100))/100;
	double endingNothing2 = (99 - (startingNothing1 * 100))/100;
	char number[5];
	sprintf(number, "%d", threadId);
	string inputDir = inputFolder;// + OS_SEP + number;
	string outputDir = outputFolder + OS_SEP + number;

	runSimulation(deployingType, toleranceType, hopCount, totalTimes, inputDir, outputDir, startingNothing1, 0,
			endingNothing1, 1 - endingNothing1, intervalByz, intervalNothing, sampleSize, networkSize);
	runSimulation(deployingType, toleranceType, hopCount, totalTimes, inputDir, outputDir, startingNothing2, 0,
			endingNothing2, 1 - endingNothing2, intervalByz, intervalNothing, sampleSize, networkSize);
}

void ByzantineSimulator::callbackThreadOneStep(ThreadArguments args, double nothingProb)
{
	ByzantineSimulator* sim = new ByzantineSimulator();
	int interval = (101 - (int)(nothingProb * 100))/args.numberCPUs;

	double startByzProb = (double)args.threadId * interval * 0.01;
	double endByzProb = (double)(args.threadId + 1) * interval * 0.01 - 0.01;
	sim->runSimulation(args.deploying, args.toleranceType, args.hopCount,
			args.totalTimes, args.inputFolder, args.output, nothingProb, startByzProb, nothingProb, endByzProb,
			0.01, 0.01, args.sampleSize, args.networkSize);
}

void ByzantineSimulator::callbackThread(ThreadArguments args)
{
	ByzantineSimulator* sim = new ByzantineSimulator();
	sim->runSimulationByThreadId(args.deploying, args.toleranceType, args.hopCount, args.threadId, args.numberCPUs, args.totalTimes,
			args.inputFolder, args.output, 0.01, 0.01, args.sampleSize, args.networkSize);
}

void ByzantineSimulator::callbackReader(ThreadArguments args, bool isFirstInSlot)
{
	ByzantineSimulator* sim = new ByzantineSimulator();
	sim->runReaderByThreadId(args.deploying, args.toleranceType, args.threadId, args.numberCPUs,
			args.inputFolder, args.output, isFirstInSlot);
}

void ByzantineSimulator::callbackOneStepReader(DeployingType deployingType, TypeOfTolerance toleranceType,
		string inputFolder, string output, double nothingProb, double intervalByz)
{
	ByzantineSimulator* sim = new ByzantineSimulator();
	sim->readOneStep(deployingType, toleranceType, inputFolder, output, nothingProb, intervalByz);
}

} /* namespace deployment */
