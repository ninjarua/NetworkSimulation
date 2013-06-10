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
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize, int size)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].set(deploying, toleranceType, totalTimes, i, numberCPUs, inputFolder, outputFolder, sampleSize);
		threads.create_thread(boost::bind(ByzantineSimulator::CallbackThread, thread_data[i]));
	}
	threads.join_all();
	cout << "Success!" << endl;
}

void SimulatorManager::ReadResults(DeployingType deploying, TypeOfTolerance toleranceType,
		string inputFolder, string outputFolder, int numberCPUs)
{
	for (int i = 0; i < numberCPUs; i++)
	{
		ThreadArguments thread_data;
		thread_data.set(deploying, toleranceType, 0, i, numberCPUs, inputFolder, outputFolder, 0);
		ByzantineSimulator::CallbackReader(thread_data, true);
	}
	for (int j = numberCPUs - 1; j >= 0; j--)
	{
		ThreadArguments thread_data;
		thread_data.set(deploying, toleranceType, 0, j, numberCPUs, inputFolder, outputFolder, 0);
		ByzantineSimulator::CallbackReader(thread_data, false);
	}
	cout << "Success!" << endl;
}

}
