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
#include "KSelfTolerance.h"
#include "K1HopTolerance.h"
#include "KxHopTolerance.h"
#include "CSelfTolerance.h"
#include "C01K03Tolerance.h"
#include "CxHopTolerance.h"
#include "KCommonTolerance.h"

using namespace generators;

#include <iostream>

namespace simulators {

ByzantineSimulator::ByzantineSimulator(Parameters _params) : SimulatorBase() {
	params = _params;
	byzantine = ByzantineProtocol(0.5, 0.5);
}

ByzantineSimulator::~ByzantineSimulator() {

}

void ByzantineSimulator::setTolerance()
{
	setDeployment();
	switch(params.toleranceType)
	{
	case KSelf:
		byzantine.tolerance = new KSelfTolerance();
		break;
	case K1Hop:
		byzantine.tolerance = new K1HopTolerance();
		break;
	case KxHop:
		byzantine.tolerance = new KxHopTolerance(params.hopCount);
		break;
	case CSelf:
		byzantine.tolerance = new CSelfTolerance();
		break;
	case C01K03:
		byzantine.tolerance = new C01K03Tolerance();
		break;
	case CxHop:
		byzantine.tolerance = new CxHopTolerance();
		generator->turnOn2HopInfo(true);
		break;
	case KCommon:
		byzantine.tolerance = new KCommonTolerance();
		break;
	default:
		byzantine.tolerance = new ToleranceBase();
		break;
	}
}

void ByzantineSimulator::setDeployment()
{
	switch(params.deployingType)
	{
	case Grid:
		generator = new GridGenerator(params.networkSize);
		break;
	case TorusGrid:
		generator = new TorusGridGenerator(params.networkSize);
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
	byzantine.report->addByzantineValue(byzantine.statisticInfo->infections);
	byzantine.report->addSacrificeValue(byzantine.statisticInfo->inactives);
	byzantine.report->addDetectorValue(byzantine.statisticInfo->detectors);
	byzantine.report->addNormalValue(byzantine.statisticInfo->sanes);
	byzantine.report->addLargestConnectedAreaValue(byzantine.statisticInfo->lca);
	byzantine.report->addDegrees(byzantine.statisticInfo->degree);
	byzantine.report->addDiameters(byzantine.statisticInfo->diameter);
}

ByzantineReport* ByzantineSimulator::finishReport()
{
	byzantine.report->Clear();
	addOneStepReport();
	byzantine.report->summarize(0.05);
	return byzantine.report;
}

bool ByzantineSimulator::stopPrediction(ByzantineReport* report)
{
    bool averageCondition = (report->ciOfByzantines < .8)
        && (report->ciOfNormals < 0.01 || (report->ciOfNormals < .8 && report->ciOfNormals <= report->averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::addingAdditionalInfo(bool using2HopInfo)
{
	setDeployment();
	//setParameters(1, inputfolder, outputFolder, 0, 0, 0, 0, 0.01, 0.01, sampleSize);

	for (int i = 0; i <= 100; i++)
	{
		bool result = generator->generateFromFiles(network, params.inputFolder, i);
		if (result)
			generator->writeNetworkToFile(network, params.output, i);
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
				byzantine.Refresh(network, params.hubOnly); // temporary change to check with hub in ScaleFree
				byzantine.RunFault(network);
				addOneStepReport();
				count++;
				i++;
			}
			if (sampleId < params.sampleSize)
				sampleId++;
			else
				sampleId = 0;
		}
		byzantine.report->summarize(0.05);
		if (stopPrediction(byzantine.report))
			times = prediction;	// reduce the running time and quit
		else
			prediction += 1000;
	}
}

void ByzantineSimulator::printToFile(ByzantineReport& report, string filename)
{
	filesystem::path dir(params.output);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(params.output + OS_SEP + filename);
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

//void ByzantineSimulator::setParameters(int totalTimes, string inputFolder, string outputFolder,
//			double startingNothing, double startingByzantine,
//			double endingNothing, double endingByzantine,
//			double intervalByz, double intervalNothing, int sampleSize)
//{
//	int intervalNothingI = (int)(intervalNothing * 100);
//	int intervalByzI = (int)(intervalByz * 100);
//	params.totalTimes = totalTimes;
//	params.nothingSteps = (int)(100 / intervalNothingI);
//	params.byzantineSteps = (int)(100 / intervalByzI);
//	params.nothingStart = (int)(round(startingNothing * 100) / intervalNothingI);
//	params.byzantineStart = (int)(round(startingByzantine * 100) / intervalByzI);
//	params.nothingEnd = (int)(round(endingNothing * 100) / intervalNothingI);
//	params.byzantineEnd = (int)(round(endingByzantine * 100) / intervalByzI);
//	params.sampleSize = sampleSize;
//	params.inputFolder = inputFolder;
//	params.output = outputFolder;
//}

void ByzantineSimulator::read()
{
	params.sampleSize = 100;
	setTolerance();
//	int nothingStart = (int)(round(startingNothing * 100) / (int)(intervalNothing * 100));
//	int byzantineStart = (int)(round(startingByz * 100) / (int)(intervalByz * 100));

	filesystem::path dir(params.inputFolder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(params.inputFolder + OS_SEP +
			getResultFilename(params.nothingStart, params.byzantineStart));
	if (filesystem::exists(file))
		Logger::Copy(file.string(), params.output, false);
}

void ByzantineSimulator::readOneStep()
{
	int byzantingEndI = 100 - params.nothingStart;
	for (int i = 0; i <= byzantingEndI; i++)
	{
		params.byzantineStart = i;
		read();
	}
}

void ByzantineSimulator::runReaderByThreadId(bool isFirstInSlot)
{
//	double startingNothing1 = intervalNothing * threadId * slotSize;
//	double endingNothing1 = startingNothing1 + ((slotSize - 1) * intervalNothing);
//	double startingNothing2 = (99 - (endingNothing1 * 100))/100;
//	char number[5];
//	sprintf(number, "%d", threadId);
//	string inputDir = resultsFolder + OS_SEP + number;
	if (isFirstInSlot)
		read();
	else
	{
		Parameters::compensateAllStepsRunningByThreadId(&params);
		read();
	}
}

void ByzantineSimulator::runOneStep(double byzantineProb, double nothingProb, int times)
{
	byzantine.Initialize(network, byzantineProb, nothingProb);
	runSimulationByInterval();
	printToFile(*byzantine.report, getResultFilename(params.nothingStart, params.byzantineStart));
}

void ByzantineSimulator::runSimulation()
{
	setTolerance();
//	setParameters(times, inputfolder, outputFolder, startingNothing, startingByzantine, endingNothing,
//			endingByzantine, intervalByz, intervalNothing, sampleSize);
	//double ratio = round((double) params.nothingSteps / params.byzantineSteps);
	if (params.nothingStart == params.nothingEnd)
	{
		for (int j = params.byzantineStart; j <= params.byzantineEnd; j++)
		{
			runOneStep(j * params.byzantineInterval, params.nothingStart * params.nothingInterval,
					params.totalTimes);
		}
	}
	else
	{
		for (int j = params.byzantineStart; j <= params.nothingSteps - params.nothingStart; j++)
			// (int)((params.nothingSteps - params.nothingStart)/ratio); j++)
			runOneStep(j * params.byzantineInterval, params.nothingStart * params.nothingInterval,
					params.totalTimes);
		for (int i = params.nothingStart + 1; i < params.nothingEnd && i < params.nothingSteps; i++)
		{
			for (int j = 0; j <= params.nothingSteps - i; j++)// / ratio); j++)
				runOneStep(j * params.byzantineInterval, i * params.nothingInterval,
						params.totalTimes);
		}
		for (int j = 0; j <= params.byzantineEnd && j <= params.nothingSteps - params.nothingEnd; j++)
		//(int)((params.nothingSteps - params.nothingEnd) / ratio); j++)
			runOneStep(j * params.byzantineInterval, params.nothingEnd * params.nothingInterval,
					params.totalTimes);
	}
}

void ByzantineSimulator::runAllStepsSimulationByThreadId()
{
	//char number[5];
	//sprintf(number, "%d", params.threadId);
	//params.output = params.output + OS_SEP + number;
	runSimulation();
	Parameters::compensateAllStepsRunningByThreadId(&params);
	runSimulation();
}

void ByzantineSimulator::callbackThreadOneStep(Parameters args)
{
	ByzantineSimulator* sim = new ByzantineSimulator(args);
	sim->runSimulation();
}

void ByzantineSimulator::callbackThread(Parameters args)
{
	ByzantineSimulator* sim = new ByzantineSimulator(args);
	sim->runAllStepsSimulationByThreadId();
}

void ByzantineSimulator::callbackReader(Parameters args, bool isFirstInSlot)
{
	ByzantineSimulator* sim = new ByzantineSimulator(args);
	sim->runReaderByThreadId(isFirstInSlot);
}

void ByzantineSimulator::callbackOneStepReader(Parameters args)
{
	ByzantineSimulator* sim = new ByzantineSimulator(args);
	sim->readOneStep();
}

void ByzantineSimulator::callbackConvert(Parameters args, bool using2HopInfo)
{
	ByzantineSimulator* sim = new ByzantineSimulator(args);
	sim->addingAdditionalInfo(using2HopInfo);
}

} /* namespace deployment */
