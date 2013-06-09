/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineSimulator.h"
#include <iostream>

namespace simulators {

ByzantineSimulator::ByzantineSimulator() : SimulatorBase() {
	byzantine = ByzantineProtocol(0.5, 0.5);
}

ByzantineSimulator::~ByzantineSimulator() {

}

void ByzantineSimulator::SetTolerance(TypeOfTolerance toleranceType)
{
	switch(toleranceType)
	{
	case K01:
		byzantine.tolerance = new K01Tolerance();
		break;
	default:
		byzantine.tolerance = new ToleranceBase();
		break;
	}
}

void ByzantineSimulator::SetDeployment(DeployingType deployingType)
{
	switch(deployingType)
	{
	case Grid:
		generator = new GridGenerator();
		break;
	case TorusGrid:
		generator = new TorusGridGenerator();
		break;
	case FixedRange:
		generator = new FixedRangeGenerator();
		break;
	case Ring:
		break;
	case ScaleFree:
		break;
	case ER_Random:
		break;
	default:
		break;
	}
}

bool ByzantineSimulator::RunSimulationStep(bool draw)
{
	bool stop = byzantine.RunStepCheckFinish(network, &Network::noNewMessageInNetwork);
	//_networkGraphics.DrawNetwork(_network, false, false, true);
	return stop;
}

void ByzantineSimulator::AddOneStepReport()
{
	byzantine.report->byzantineProb = byzantine.byzantineProb;
	byzantine.report->AddByzantineValue(byzantine.statisticInfo->infections);
	byzantine.report->AddSacrificeValue(byzantine.statisticInfo->inactives);
	byzantine.report->AddDetectorValue(byzantine.statisticInfo->detectors);
	byzantine.report->AddNormalValue(byzantine.statisticInfo->sanes);
	byzantine.report->AddLargestConnectedAreaValue(byzantine.statisticInfo->lca);
}

ByzantineReport* ByzantineSimulator::FinishReport()
{
	byzantine.report->Clear();
	AddOneStepReport();
	byzantine.report->Summarize(0.05);
	return byzantine.report;
}

bool ByzantineSimulator::StopPrediction(ByzantineReport* report)
{
    bool averageCondition = (report->ciOfByzantines < .8)
        && (report->ciOfNormals < 0.01 || (report->ciOfNormals < .8 && report->ciOfNormals <= report->averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::RunSimulationByInterval()
{
	byzantine.report->Clear();
	byzantine.report->nothingProb = byzantine.nothingProb;
	int times = params.totalTimes;
	if (round(byzantine.nothingProb + byzantine.byzantineProb) > 0.99)
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
			generator->GenerateFromFiles(network, params.inputFolder, sampleId);
			int i = 0;
			while (i < sampleRepeat)
			{
				byzantine.Refresh(network);
				byzantine.RunFault(network);
				AddOneStepReport();
				count++;
				i++;
			}
			sampleId++;
		}
		byzantine.report->Summarize(0.05);
		if (StopPrediction(byzantine.report))
			times = prediction;	// reduce the running time and quit
		else
			prediction += 1000;
	}
}

void ByzantineSimulator::PrintToFile(ByzantineReport& report, string filename)
{
	filesystem::path dir(params.outputFolder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(params.outputFolder + OS_SEP + filename);
	Logger::Write(report, file.string(), ofstream::out | ofstream::app);
}

string ByzantineSimulator::GetResultFilename(double nothingProb, double byzantineProb)
{
	string filename = generator->GetDeployingName();
	filename += "_";
	filename += byzantine.tolerance->GetToleranceName();

	char number[11];
		sprintf(number, "_%.2f_%.2f", nothingProb, byzantineProb);

	filename += number;
	filename += ".out";
	return filename;
}

void ByzantineSimulator::SetParameters(int totalTimes, string inputFolder, string outputFolder,
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

void ByzantineSimulator::RunSimulationByThreadId(DeployingType deploying, TypeOfTolerance toleranceType,
		int threadId, int totalThread, int totalTimes,
		string inputFolder, string outputFolder,
		double intervalByz, double intervalNothing, int sampleSize)
{
	double slotSize = 50 / totalThread;
	double startingNothing1 = intervalNothing * threadId * slotSize;
	double endingNothing1 = startingNothing1 + ((slotSize - 1) * intervalNothing);
	double startingNothing2 = (99 - (endingNothing1 * 100))/100;
	double endingNothing2 = (99 - (startingNothing1 * 100))/ 100;
	char number[5];
	sprintf(number, "%d", threadId);
	string inputDir = inputFolder + OS_SEP + number;
	string outputDir = outputFolder + OS_SEP + number;

//	filesystem::path file(outputFolder + OS_SEP + number + ".out");
//	ofstream fout;
//	fout.open(file.string().c_str(), ofstream::out | ofstream::app);
//	fout << "From: " << startingNothing1 << "\t" << endingNothing1 << "\t" << startingNothing2 << "\t" << endingNothing2 << endl;
//	fout.close();

	RunSimulation(deploying, toleranceType, totalTimes, inputDir, outputDir, startingNothing1, 0,
			endingNothing1, 1 - endingNothing1, intervalByz, intervalNothing, sampleSize);
	RunSimulation(deploying, toleranceType, totalTimes, inputDir, outputDir, startingNothing2, 0,
			endingNothing2, 1 - endingNothing2, intervalByz, intervalNothing, sampleSize);
}

void ByzantineSimulator::RunSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int times,
		string inputfolder, string outputFolder,
		double startingNothing, double startingByzantine,
		double endingNothing, double endingByzantine,
		double intervalByz, double intervalNothing, int sampleSize)
{
	SetTolerance(toleranceType);
	SetDeployment(deploying);
	SetParameters(times, inputfolder, outputFolder, startingNothing, startingByzantine, endingNothing,
			endingByzantine, intervalByz, intervalNothing, sampleSize);
	//double ratio = (double)params.nothingSteps / params.byzantineSteps;

	if (params.nothingStart == params.nothingEnd)
	{
		for (int j = params.byzantineStart; j <= params.byzantineEnd; j++)
			RunOneStep(j * intervalByz, params.nothingStart * intervalNothing, times);
	}
	else
	{
		for (int j = params.byzantineStart; j <= params.nothingSteps - params.nothingStart; j++)
			// (int)((params.nothingSteps - params.nothingStart)/ratio); j++)
			RunOneStep(j * intervalByz, params.nothingStart * intervalNothing, times);
		for (int i = params.nothingStart + 1; i < params.nothingEnd && i < params.nothingSteps; i++)
		{
			for (int j = 0; j <= params.nothingSteps - i; i++)// / ratio); j++)
				RunOneStep(j * intervalByz, i * intervalNothing, times);
		}
		for (int j = 0; j <= params.byzantineEnd && j <= params.nothingSteps - params.nothingEnd; j++)
		//(int)((params.nothingSteps - params.nothingEnd) / ratio); j++)
			RunOneStep(j * intervalByz, params.nothingEnd * intervalNothing, times);
	}
}

void ByzantineSimulator::RunOneStep(double byzantineProb, double nothingProb, int times)
{
	byzantine.Initialize(network, byzantineProb, nothingProb);
	RunSimulationByInterval();
	PrintToFile(*byzantine.report, GetResultFilename(params.nothingStart, params.byzantineStart));
}

void ByzantineSimulator::CallbackThread(ThreadArguments args)
{
	ByzantineSimulator* sim = new ByzantineSimulator();
	sim->RunSimulationByThreadId(args.deploying, args.toleranceType, args.threadId, args.numberCPUs, args.totalTimes,
			args.inputFolder, args.outputFolder, 0.01, 0.01, args.sampleSize);
//	ThreadArguments* ar = (ThreadArguments*)args;
//	sim->RunSimulationByThreadId(ar->deploying, ar->toleranceType, 1, 2, ar->totalTimes,
//			ar->inputFolder, ar->outputFolder, 0.01, 0.01, ar->sampleSize);
//	return args;
}

} /* namespace deployment */
