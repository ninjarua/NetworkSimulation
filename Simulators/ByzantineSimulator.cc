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
#include "CCo0ETolerance.h"
#include "C01K03Tolerance.h"
#include "CxHopTolerance.h"
#include "KCo1Tolerance.h"
#include "KCo1CCo3Tolerance.h"
#include "CCo1ETolerance.h"
#include "KSelfCCo1ETolerance.h"
#include "CCo2ETolerance.h"
#include "KCo2Tolerance.h"
#include "CCo3ETolerance.h"
#include "CCoInfyETolerance.h"
#include "CCoENewTolerance.h"
#include "KCoInfyTolerance.h"

using namespace generators;

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
		byzantine.tolerance = new CCo0ETolerance();
		break;
	case C01K03:
		byzantine.tolerance = new C01K03Tolerance();
		break;
	case CxHop:
		byzantine.tolerance = new CxHopTolerance();
		generator->switch2HopInfo(true);
		break;
	case KCo1:
		byzantine.tolerance = new KCo1Tolerance();
		break;
	case CCo1E:
		byzantine.tolerance = new CCo1ETolerance();
		break;
	case KSelfCCo1E:
		byzantine.tolerance = new KSelfCCo1ETolerance();
		break;
	case CCo2E:
		byzantine.tolerance = new CCo2ETolerance();
		break;
	case KCo2:
		byzantine.tolerance = new KCo2Tolerance();
		break;
	case CCo3E:
		byzantine.tolerance = new CCo3ETolerance();
		break;
	case CCoInfyE:
		byzantine.tolerance = new CCoInfyETolerance();
		break;
	case KCo1CCo3:
		byzantine.tolerance = new KCo1CCo3Tolerance();
		break;
	case CCoENew:
		byzantine.tolerance = new CCoENewTolerance();
		break;
	case K1Short:
		byzantine.tolerance = new KCoInfyTolerance();
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
		generator = new NetworkGenerator();
		break;
	}
	generator->specificInputFile = params.specificInputFile;
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
    bool averageCondition = (report->average.ciOfByzantines < .8)
        && (report->average.ciOfNormals < 0.01 ||
        		(report->average.ciOfNormals < .8 && report->average.ciOfNormals <= report->average.averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::addingAdditionalInfo(bool using2HopInfo)
{
	setDeployment();
	generator->switch2HopInfo(using2HopInfo);
	//setParameters(1, inputfolder, outputFolder, 0, 0, 0, 0, 0.01, 0.01, sampleSize);

	for (int i = 0; i <= params.sampleSize; i++)
	{
		bool result = generator->generateFromFiles(network, params.inputFolder, i);
		if (result)
			generator->writeNetworkToFile(network, params.output, i);
	}
}

string getFilename(int id)
{
	string filename("graph");
	if (id > 0)
	{
		char number[6];
		sprintf(number, "_%04d", id);
		filename = filename + number;
	}
	filename = filename + ".out";
	return filename;
}

string getFilenameFullPath(string folder, int number)
{
	string filename("summary_" + getFilename(number));
	filesystem::path dir(folder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(folder + OS_SEP + filename);
	return file.string();
}

void ByzantineSimulator::analyseNetwork(bool using2HopInfo)
{
	setDeployment();
	generator->switch2HopInfo(using2HopInfo);
//	bool result = generator->generateFromFiles(network, params.inputFolder, 0);
//	if (result)
//		network->runFloyd();

	for (int i = 0; i <= 100; i++)
	{
		bool result = generator->generateFromFiles(network, params.inputFolder, i);
		if (result)
		{
			StatisticSummary summary = StatisticSummary();
			vector<double> ratioList = vector<double>();
			vector<NodePtr>::iterator it = network->nodes.begin();
			for(;it != network->nodes.end(); it++)
			{
				long numberCommonNodes = (*it)->commonNeighbors.size();
				long numberNeighbors = (*it)->links.size();
				cout << numberCommonNodes << "\t" << numberNeighbors << endl;// << "\t" << ratio << endl;
				if (numberCommonNodes != 0)
				{
					//	continue;
					double ratio = ((double) (numberNeighbors - numberCommonNodes)) / numberCommonNodes;
					ratioList.push_back(ratio);
				}
				//cout << ratioList[ratioList.size() - 1] << endl;
			}
			summary.summarize(ratioList);
//			cout << summary.mean << "\t" << summary.variance
//					<< "\t" << summary.standardDeviation << endl;
			Logger::Write(summary, params.output, ofstream::out | ofstream::app);
		}
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
	int sampleId = 0;
	bool hasTopology = false;
	while (count < times)
	{
		sampleId = 0;
		while (count < prediction)
		{
			if (!generator->specificInputFile || !hasTopology)
			{
				hasTopology = generator->generateFromFiles(network, params.inputFolder, sampleId);
				if (!hasTopology)
					return;
			}
			int i = 0;
			while (i < sampleRepeat)
			{
				byzantine.Refresh(network, params.hubOnly); // temporary change to check with hub in ScaleFree
				byzantine.RunFault(network);
				printToFile(*byzantine.statisticInfo, getResultFilename(params.nothingStart, params.byzantineStart));
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

void ByzantineSimulator::printToFile(NetworkStatistic& networkStatistic, string filename)
{
	filesystem::path dir(params.output);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	char byz[4];
	sprintf(byz, "%d", (int)(byzantine.byzantineProb * 100));
	filesystem::path file(params.output + OS_SEP + filename + "_" + byz + ".log");
	Logger::Write(networkStatistic, file.string(), ofstream::out | ofstream::app);
}

void ByzantineSimulator::printToFile(ByzantineReport& report, string filename)
{
	filesystem::path dir(params.output);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(params.output + OS_SEP + filename);
	Logger::Write(report.average, file.string(), ofstream::out | ofstream::app);
//
//	char byz[4];
//	sprintf(byz, "%d", (int)(report.byzantineProb * 100));
//	filesystem::path filelog(params.output + OS_SEP + filename + "_" + byz + ".log");
//	Logger::Write(report, filelog.string(), ofstream::out);
}

string ByzantineSimulator::getResultFilename(double nothingProb, double byzantineProb)
{
	string filename = generator->getDeployingName();
	filename += "_";
	filename += byzantine.tolerance->GetToleranceName();

	char number[14];
		sprintf(number, "_%.2f_%.2f", nothingProb, byzantineProb);

	filename += number;
	filename += ".out";
	return filename;
}

void ByzantineSimulator::read()
{
	params.sampleSize = 100;
	setTolerance();

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
			runOneStep(j * params.byzantineInterval, params.nothingStart * params.nothingInterval,
					params.totalTimes);
		for (int i = params.nothingStart + 1; i < params.nothingEnd && i < params.nothingSteps; i++)
		{
			for (int j = 0; j <= params.nothingSteps - i; j++)// / ratio); j++)
				runOneStep(j * params.byzantineInterval, i * params.nothingInterval,
						params.totalTimes);
		}
		for (int j = 0; j <= params.byzantineEnd && j <= params.nothingSteps - params.nothingEnd; j++)
			runOneStep(j * params.byzantineInterval, params.nothingEnd * params.nothingInterval,
					params.totalTimes);
	}
}

void ByzantineSimulator::runAllStepsSimulationByThreadId()
{
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
