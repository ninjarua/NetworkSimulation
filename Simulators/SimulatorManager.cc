/*
 * SimulatorManager.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "SimulatorManager.h"
#include "ThreadArguments.h"
namespace simulators
{

SimulatorManager::SimulatorManager() {

}

SimulatorManager::~SimulatorManager() {

}

void SimulatorManager::RunSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	pthread_t threads[numberCPUs];
	int rc;
	ThreadArguments thread_data(deploying, toleranceType, totalTimes, inputFolder, outputFolder, numberCPUs, sampleSize);

	for (int i = 0; i < numberCPUs; i++)
	{
		rc = pthread_create(&threads[i], NULL,
		                          ByzantineSimulator::CallbackThread, (void*)&thread_data);
		if (rc){
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
}

}
