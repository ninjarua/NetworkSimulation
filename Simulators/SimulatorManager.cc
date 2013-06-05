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
//	pthread_t threads[numberCPUs];
//	int rc;
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].set(deploying, toleranceType, totalTimes, i, numberCPUs, inputFolder, outputFolder, sampleSize);
		threads.create_thread(boost::bind(ByzantineSimulator::CallbackThread, thread_data[i]));
//		rc = pthread_create(&threads[i], NULL,
//					ByzantineSimulator::CallbackThread, (void*)&thread_data[i]);
//		if (rc){
//			cout << "Error:unable to create thread," << rc << endl;
//			exit(-1);
//		}
	}
	threads.join_all();
	cout << "Success!" << endl;
}

}
