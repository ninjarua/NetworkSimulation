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

using namespace protocols;

namespace simulators {

class ByzantineSimulator: public SimulatorBase {
private:
	ByzantineProtocol _byzantine;
public:
	ByzantineSimulator();
	virtual ~ByzantineSimulator();

	TypeOfTolerance ToleranceType;

//	NetworkInfo* GetNetworkInfo();
	virtual void SetTolerance(TypeOfTolerance toleranceType);
	void InitializeSimulator(double byzantineProb, double nothingProb, TypeOfTolerance toleranceType, bool draw = false);
	bool RunSimulationStep(bool draw = false);
	void DrawNetwork();
	void AddOneStepReport();
	ByzantineReport* FinishReport();
	bool StopPrediction(ByzantineReport* report);
	void RunSimulationByInterval(int times);
	string GetResultFilename();
	void RunSimulation(int times, double intervalByz, double intervalNothing,
                        TypeOfTolerance toleranceType, void (*output)(ByzantineReport&, string),
                        double startingNothing = 0, double startingByzantine = 0,
                        double endNothing = 1, double endByzantine = 1);
	void RunOneStep(void (*output)(ByzantineReport&, string), double byzantineProb, double nothingProb, int times);
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
