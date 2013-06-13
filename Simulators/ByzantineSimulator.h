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
	void SetParameters(int totalTimes, string inputFolder, string outputFolder,
			double startingNothing, double startingByzantine,
			double endingNothing, double endingByzantine,
			double intervalByz, double intervalNothing, int topologyUsage);
	bool RunSimulationStep(bool draw = false);
	void RunSimulationByInterval();
	void RunOneStep(double byzantineProb, double nothingProb, int times);

	bool StopPrediction(ByzantineReport* report);

	string GetResultFilename(double nothingProb, double byzantineProb);
	void PrintToFile(ByzantineReport& report, string filename);

	void AddOneStepReport();
	ByzantineReport* FinishReport();

public:
	ByzantineSimulator();
	virtual ~ByzantineSimulator();
	virtual void SetTolerance(TypeOfTolerance toleranceType);
	virtual void SetDeployment(DeployingType deployingType, int networkSize);

	static void CallbackThread(ThreadArguments args);
	static void CallbackReader(ThreadArguments args, bool isFirstInSlot);
	static void CallbackOneStepReader(DeployingType deployingType, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb, double intervalByz = 0.01);

	void RunReaderByThreadId(DeployingType deployingType, TypeOfTolerance toleranceType, int threadId, int totalThread,
			string resultsFolder, string outputFilename, bool isFirstInSlot, double intervalNothing = 0.01);
	void ReadOneStep(DeployingType deployingType, TypeOfTolerance toleranceType,
			string resultsFolder, string outputFilename, double nothingProb, double intervalByz);
	void Read(DeployingType deployingType, TypeOfTolerance toleranceType,
			string resultsFolder, string outputFilename,
			double startingNothing, double startingByz,
			double intervalNothing = 0.01, double intervalByz = 0.01);
	void RunSimulationByThreadId(DeployingType deployingType, TypeOfTolerance toleranceType,
					int threadId, int totalThread, int totalTimes,
					string inputFolder, string outputFolder,
					double intervalByz, double intervalNothing, int sampleSize = 1, int networkSize = 100);
	void RunSimulation(DeployingType deployingType, TypeOfTolerance toleranceType, int totalTimes,
					string inputfolder, string outputFolder,
					double startingNothing = 0, double startingByzantine = 0,
					double endingNothing = 1, double endingByzantine = 1,
					double intervalByz = 0.01, double intervalNothing = 0.01, int sampleSize = 1, int networkSize = 100);
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
