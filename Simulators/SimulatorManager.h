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
	list<ByzantineSimulator>* listSims;
public:
	SimulatorManager();
	virtual ~SimulatorManager();

	void addSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize);
	void addSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
			string inputFolder, string outputFolder, int numberCPUs, int sampleSize);

	void addSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, string outputFolder, int numberCPUs, int networkSize=100);
	void addSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, string outputFolder, int numberCPUs, int networkSize=100);


	void addOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
			double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize);
	void addOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
			double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize);

	void addOneStepSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, double nothingProb,
			string outputFolder, int numberCPUs, int networkSize=100);
	void addOneStepSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
			string outputFolder, int numberCPUs, int networkSize=100);

	void addOneStepSimulationForScaleFree(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
			string inputFolder, string outputFolder, int numberCPUs, int sampleSize, bool hubOnly);

	void runSimulations();

	void readResults(DeployingType deploying, TypeOfTolerance toleranceType,
					string inputFolder, string outputFolder, int numberCPUs);
	void readOneStepResults(DeployingType deploying, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb = 0, double intervalByz = 0.01);

	void convert2HopInformation(DeployingType deployingType, string inputfolder, string outputFolder, int sampleSize, bool using2HopInfo);

};

}
#endif /* SIMULATORMANAGER_H_ */
