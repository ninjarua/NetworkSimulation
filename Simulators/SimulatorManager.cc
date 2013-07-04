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
//	ThreadArguments thread_data;
//	thread_data.set(deploying, toleranceType, totalTimes, 1, numberCPUs, inputFolder, outputFolder, sampleSize);
//	ByzantineSimulator::CallbackThread(thread_data);
	cout << "Success!" << endl;
}

void SimulatorManager::RunOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
		string inputFolder, string outputFolder, int numberCPUs, int sampleSize, int networkSize)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].set(deploying, toleranceType, totalTimes, i, numberCPUs, inputFolder, outputFolder, sampleSize);
		threads.create_thread(boost::bind(ByzantineSimulator::CallbackThreadOneStep, thread_data[i]));
	}
	threads.join_all();

//	ByzantineSimulator* sim = new ByzantineSimulator();
//	for (int i = 11; i < 100; i++)
//	{
//		double byzProb = (double)i * 0.01;
//		sim->RunSimulation(deploying, toleranceType, totalTimes, inputFolder, outputFolder, 0, byzProb, 0, byzProb, 0.01, 0.01, sampleSize);
//	}
}

void SimulatorManager::ReadResults(DeployingType deploying, TypeOfTolerance toleranceType,
		string inputFolder, string output, int numberCPUs)
{
	for (int i = 0; i < numberCPUs; i++)
	{
		ThreadArguments thread_data;
		thread_data.set(deploying, toleranceType, 0, i, numberCPUs, inputFolder, output, 0);
		ByzantineSimulator::CallbackReader(thread_data, true);
	}
	for (int j = numberCPUs - 1; j >= 0; j--)
	{
		ThreadArguments thread_data;
		thread_data.set(deploying, toleranceType, 0, j, numberCPUs, inputFolder, output, 0);
		ByzantineSimulator::CallbackReader(thread_data, false);
	}
	cout << "Success!" << endl;
}

void SimulatorManager::ReadOneStepResults(DeployingType deploying, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb, double intervalByz)
{
	ByzantineSimulator::CallbackOneStepReader(deploying, toleranceType, inputFolder, output, nothingProb, intervalByz);
}

}
