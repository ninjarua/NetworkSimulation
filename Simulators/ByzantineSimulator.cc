/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineSimulator.h"

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
		//_fault->tolerance = ToleranceBase::GetBase();
		byzantine.tolerance = new ToleranceBase();
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

//void ByzantineSimulator::InitializeSimulator(double byzantineProb, double nothingProb, TypeOfTolerance toleranceType, bool draw)
//{
//	SetTolerance(toleranceType);
//	_byzantine.Initialize(_network, byzantineProb, nothingProb);
//	_byzantine.Refresh(_network);
//}

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
	if (byzantine.nothingProb + byzantine.byzantineProb > 0.991)
		times = 2;
	int predictionIt = 1000;
	int sampleRepeat = (int)((double) predictionIt/params.sampleSize);
	int prediction = (times < predictionIt) ? times : predictionIt;
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
	params.totalTimes = totalTimes;
	params.nothingSteps = (int)(100 / (int)(intervalNothing * 100));;
	params.byzantineSteps = (int)(100 / (int)(intervalByz * 100));
	params.nothingStart = (int)(startingNothing / intervalNothing);
	params.byzantineStart = (int)(startingByzantine / intervalNothing);
	params.nothingEnd = (int)(endingNothing / intervalNothing);
	params.byzantineEnd = (int)(endingByzantine / intervalNothing);
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
	double startingNothing1 = 0.01 * threadId * slotSize;
	double endingNothing1 = startingNothing1 + slotSize;
	double startingNothing2 = 0.99 - endingNothing1;
	double endingNothing2 = 0.99 - startingNothing1;
	RunSimulation(deploying, toleranceType, totalTimes, inputFolder, outputFolder, startingNothing1, 0,
			endingNothing1, 1 - endingNothing1, intervalByz, intervalNothing, sampleSize);
	RunSimulation(deploying, toleranceType, totalTimes, inputFolder, outputFolder, startingNothing2, 0,
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
	double ratio = (double)params.nothingSteps / params.byzantineSteps;

	if (params.nothingStart == params.nothingEnd)
	{
		for (int j = params.byzantineStart; j <= params.byzantineEnd; j++)
			RunOneStep(j * intervalByz, params.nothingStart * intervalNothing, times);
	}
	else
	{
		for (int j = params.byzantineStart; j <= (int)((params.nothingSteps - params.nothingStart)/ratio); j++)
			RunOneStep(j * intervalByz, params.nothingStart * intervalNothing, times);
		for (int i = params.nothingStart + 1; i < params.nothingEnd && i < params.nothingSteps; i++)
		{
			for (int j = 0; j <= (int)((params.nothingSteps - i) / ratio); j++)
				RunOneStep(j * intervalByz, i * intervalNothing, times);
		}
		for (int j = 0; j <= params.byzantineEnd && j <= (int)((params.nothingSteps - params.nothingEnd) / ratio); j++)
			RunOneStep(j * intervalByz, params.nothingEnd * intervalNothing, times);
	}
}

void ByzantineSimulator::RunOneStep(double byzantineProb, double nothingProb, int times)
{
	byzantine.Initialize(network, byzantineProb, nothingProb);
	RunSimulationByInterval();
	PrintToFile(*byzantine.report, GetResultFilename(params.nothingStart, params.byzantineStart));
}

void* ByzantineSimulator::CallbackThread(void* args)
{
	return args;
}

} /* namespace deployment */
