/*
 * SimulatorManager.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef SIMULATORMANAGER_H_
#define SIMULATORMANAGER_H_
#include "stdafx.h"
//#include <pthread.h>
#include <boost/thread.hpp>
#include "ByzantineSimulator.h"

namespace simulators
{

class SimulatorManager {
public:
	SimulatorManager();
	virtual ~SimulatorManager();

	void runSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize);
	void runSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize);

	void runSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, string outputFolder, int numberCPUs, int networkSize=100);
	void runSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, string outputFolder, int numberCPUs, int networkSize=100);

	void runOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
			double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize);
	void runOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
			double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize);

	void runOneStepSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, double nothingProb,
			string outputFolder, int numberCPUs, int networkSize=100);
	void runOneStepSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
			string outputFolder, int numberCPUs, int networkSize=100);

	void runOneStepSimulationForScaleFree(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
			string inputFolder, string outputFolder, int numberCPUs, int sampleSize, bool hubOnly);

	void readResults(DeployingType deploying, TypeOfTolerance toleranceType,
					string inputFolder, string outputFolder, int numberCPUs);
	void readOneStepResults(DeployingType deploying, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb = 0, double intervalByz = 0.01);

	void convert2HopInformation(DeployingType deployingType, string inputfolder, string outputFolder, int sampleSize, bool using2HopInfo);

};

}
#endif /* SIMULATORMANAGER_H_ */
