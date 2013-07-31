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

void SimulatorManager::runSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
				string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	runSimulation(deploying, toleranceType, 1, totalTimes, inputFolder, outputFolder, numberCPUs, sampleSize);
}

void SimulatorManager::runSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].set(deploying, toleranceType, hopCount, totalTimes, i, numberCPUs, inputFolder, outputFolder, sampleSize);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThread, thread_data[i]));
	}
	threads.join_all();
	cout << "Success!" << endl;
}

void SimulatorManager::runSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, string outputFolder, int numberCPUs, int networkSize)
{
	runSimulationForGrid(toleranceType, 1, totalTimes, outputFolder, numberCPUs, networkSize);
}

void SimulatorManager::runSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, string outputFolder, int numberCPUs, int networkSize)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].setForGrid(toleranceType, hopCount, totalTimes, i, numberCPUs, outputFolder, networkSize);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThread, thread_data[i]));
	}
	threads.join_all();
	cout << "Success!" << endl;
}

void SimulatorManager::runOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
		double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	runOneStepSimulation(deploying, toleranceType, 1, totalTimes, nothingProb, inputFolder, outputFolder, numberCPUs, sampleSize);
}
void SimulatorManager::runOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
		double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].set(deploying, toleranceType, hopCount, totalTimes, i, numberCPUs, inputFolder, outputFolder, sampleSize);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, thread_data[i], nothingProb));
	}
	threads.join_all();
}

void SimulatorManager::runOneStepSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, double nothingProb,
		string outputFolder, int numberCPUs, int networkSize)
{
	runOneStepSimulationForGrid(toleranceType, 1, totalTimes, nothingProb, outputFolder, numberCPUs, networkSize);
}

void SimulatorManager::runOneStepSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
		string outputFolder, int numberCPUs, int networkSize)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].setForGrid(toleranceType, hopCount, totalTimes, i, numberCPUs, outputFolder, networkSize);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, thread_data[i], nothingProb));
	}
	threads.join_all();
}

void SimulatorManager::runOneStepSimulationForScaleFree(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
		string inputFolder, string outputFolder, int numberCPUs, int sampleSize, bool hubOnly)
{
	ThreadArguments thread_data[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		thread_data[i].setForScaleFree(toleranceType, hopCount, totalTimes, i, numberCPUs, inputFolder,
				outputFolder, sampleSize, hubOnly);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, thread_data[i], nothingProb));
	}
	threads.join_all();
}

void SimulatorManager::readResults(DeployingType deploying, TypeOfTolerance toleranceType,
		string inputFolder, string output, int numberCPUs)
{
	for (int i = 0; i < numberCPUs; i++)
	{
		ThreadArguments thread_data;
		thread_data.set(deploying, toleranceType, i, numberCPUs, inputFolder, output, 0);
		ByzantineSimulator::callbackReader(thread_data, true);
	}
	for (int j = numberCPUs - 1; j >= 0; j--)
	{
		ThreadArguments thread_data;
		thread_data.set(deploying, toleranceType, j, numberCPUs, inputFolder, output, 0);
		ByzantineSimulator::callbackReader(thread_data, false);
	}
	cout << "Success!" << endl;
}

void SimulatorManager::readOneStepResults(DeployingType deploying, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb, double intervalByz)
{
	ByzantineSimulator::callbackOneStepReader(deploying, toleranceType, inputFolder, output, nothingProb, intervalByz);
}

}
