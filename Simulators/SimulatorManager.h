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

	void RunSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize, int size=100);
	void RunOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
						string inputFolder, string outputFolder, int numberCPUs, int sampleSize, int networkSize=100);
	void ReadResults(DeployingType deploying, TypeOfTolerance toleranceType,
					string inputFolder, string outputFolder, int numberCPUs);

};

}
#endif /* SIMULATORMANAGER_H_ */
