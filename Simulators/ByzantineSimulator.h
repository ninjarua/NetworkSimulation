/*
 * PropagationSimulator.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef PROPAGATIONSIMULATOR_H_
#define PROPAGATIONSIMULATOR_H_

#include "stdafx.h"
#include <list>
#include <pthread.h>
#include <boost/filesystem.hpp>
#include "ByzantineReport.h"
#include "ByzantineProtocol.h"
#include "Parameters.h"
#include "ThreadArguments.h"
#include "SimulatorBase.h"

using namespace protocols;
using namespace boost;

namespace simulators {

class ByzantineSimulator: public SimulatorBase {
private:
	ByzantineProtocol byzantine;
	Parameters params;
	void setParameters(int totalTimes, string inputFolder, string outputFolder,
			double startingNothing, double startingByzantine,
			double endingNothing, double endingByzantine,
			double intervalByz, double intervalNothing, int topologyUsage);
	bool runSimulationStep(bool draw = false);
	void runSimulationByInterval();
	void runOneStep(double byzantineProb, double nothingProb, int times);

	bool stopPrediction(ByzantineReport* report);

	string getResultFilename(double nothingProb, double byzantineProb);
	void printToFile(ByzantineReport& report, string filename);

	void addOneStepReport();
	ByzantineReport* finishReport();
	virtual void setDeployment(DeployingType deployingType, int networkSize);
	virtual void setTolerance(TypeOfTolerance toleranceType, DeployingType deployingType, int networkSize, int hopCount=1);

public:
	ByzantineSimulator();
	virtual ~ByzantineSimulator();

	static void callbackThread(ThreadArguments args);
	static void callbackThreadOneStep(ThreadArguments args, double nothingProb);
	static void callbackReader(ThreadArguments args, bool isFirstInSlot);
	static void callbackOneStepReader(DeployingType deployingType, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb, double intervalByz = 0.01);

	void runReaderByThreadId(DeployingType deployingType, TypeOfTolerance toleranceType, int threadId, int totalThread,
			string resultsFolder, string outputFilename, bool isFirstInSlot, double intervalNothing = 0.01);
	void readOneStep(DeployingType deployingType, TypeOfTolerance toleranceType,
			string resultsFolder, string outputFilename, double nothingProb, double intervalByz);
	void read(DeployingType deployingType, TypeOfTolerance toleranceType,
			string resultsFolder, string outputFilename,
			double startingNothing, double startingByz,
			double intervalNothing = 0.01, double intervalByz = 0.01);
	void runSimulationByThreadId(DeployingType deployingType, TypeOfTolerance toleranceType,
					int hopCount, int threadId, int totalThread, int totalTimes,
					string inputFolder, string outputFolder,
					double intervalByz, double intervalNothing, int sampleSize = 1, int networkSize = 100);
	void runSimulation(DeployingType deployingType, TypeOfTolerance toleranceType, int totalTimes,
					string inputfolder, string outputFolder,
					double startingNothing = 0, double startingByzantine = 0,
					double endingNothing = 1, double endingByzantine = 1,
					double intervalByz = 0.01, double intervalNothing = 0.01, int sampleSize = 1, int networkSize = 100);
	void runSimulation(DeployingType deployingType, TypeOfTolerance toleranceType,
					int hopCount,int totalTimes,
					string inputfolder, string outputFolder,
					double startingNothing = 0, double startingByzantine = 0,
					double endingNothing = 1, double endingByzantine = 1,
					double intervalByz = 0.01, double intervalNothing = 0.01, int sampleSize = 1, int networkSize = 100);
	void convert2HopInformation(DeployingType deployingType,
			string inputfolder, string outputFolder, int sampleSize);
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
