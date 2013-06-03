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

using namespace protocols;

namespace simulators {

class ByzantineSimulator: public SimulatorBase {
private:
	ByzantineProtocol byzantine;
	Parameter params;
	void SetRepeatParameter(int totalTimes, string folder, double startingNothing, double startingByzantine,
			double endingNothing, double endingNothing,
			double intervalByz, double intervalNothing, int topologyUsage);
public:
	ByzantineSimulator();
	virtual ~ByzantineSimulator();

	TypeOfTolerance ToleranceType;

	virtual void SetTolerance(TypeOfTolerance toleranceType);
	void AddOneStepReport();
	ByzantineReport* FinishReport();
	bool StopPrediction(ByzantineReport* report);
	string GetResultFilename();

	bool RunSimulationStep(bool draw = false);
	void RunSimulationByInterval();
	void RunSimulation(DeployingType deploying, TypeOfTolerance toleranceType, string folder, int totalTimes,
					double startingNothing = 0, double startingByzantine = 0,
					double endingNothing = 1, double endingByzantine = 1,
					double intervalByz = 0.01, double intervalNothing = 0.01, int sampleSize = 1);
	void RunOneStep(double byzantineProb, double nothingProb, int times);
	static void PrintToFile(ByzantineReport& report, string filename);
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
