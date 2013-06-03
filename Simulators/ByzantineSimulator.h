/*
 * PropagationSimulator.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef PROPAGATIONSIMULATOR_H_
#define PROPAGATIONSIMULATOR_H_

#include "SimulatorBase.h"
#include "ByzantineReport.h"
#include "Parameters.h"
#include "GridGenerator.h"
#include "TorusGridGenerator.h"
#include "FixedRangeGenerator.h"

using namespace protocols;
using namespace generators;

namespace simulators {

class ByzantineSimulator: public SimulatorBase {
private:
	ByzantineProtocol byzantine;
	Parameter params;
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
	virtual void SetDeployment(DeployingType deployingType);

	void RunSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
					string inputfolder, string outputFolder,
					double startingNothing = 0, double startingByzantine = 0,
					double endingNothing = 1, double endingByzantine = 1,
					double intervalByz = 0.01, double intervalNothing = 0.01, int sampleSize = 1);
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
