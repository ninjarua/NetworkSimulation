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
	void printToFile(NetworkStatistic& networkStatistic, string filename);

	void addOneStepReport();
	ByzantineReport* finishReport();
	virtual void setDeployment();
	virtual void setTolerance();

public:
	ByzantineSimulator(Parameters _params);
	virtual ~ByzantineSimulator();

	static void callbackThread(Parameters args);
	static void callbackThreadOneStep(Parameters args);
	static void callbackReader(Parameters args, bool isFirstInSlot);
	static void callbackOneStepReader(Parameters args);
	static void callbackConvert(Parameters args, bool using2HopInfo);

	void runReaderByThreadId(bool isFirstInSlot);
	void readOneStep();
	void read();
	void runAllStepsSimulationByThreadId();
	void runSimulation();
	void addingAdditionalInfo(bool using2HopInfo);
	void analyseNetwork(bool using2HopInfo);
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
