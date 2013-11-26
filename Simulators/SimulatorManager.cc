/*
 * SimulatorManager.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "SimulatorManager.h"
#include "Parameters.h"
namespace simulators
{

SimulatorManager::SimulatorManager() {
	listSims = new list<ByzantineSimulator>();
}

SimulatorManager::~SimulatorManager() {

}

void SimulatorManager::addSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
				string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	addSimulation(deploying, toleranceType, 1, totalTimes, inputFolder, outputFolder, numberCPUs, sampleSize);
}

void SimulatorManager::addSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
					string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	Parameters params[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		params[i].set(deploying, toleranceType, hopCount, totalTimes, i, numberCPUs,
				inputFolder, outputFolder, sampleSize, Parameters::setAllStepsRunningByThreadId);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThread, params[i]));
	}
	threads.join_all();
	cout << "Success!" << endl;
}

void SimulatorManager::addSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, string outputFolder, int numberCPUs, int networkSize)
{
	addSimulationForGrid(toleranceType, 1, totalTimes, outputFolder, numberCPUs, networkSize);
}

void SimulatorManager::addSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, string outputFolder, int numberCPUs, int networkSize)
{
	Parameters params[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		params[i].setForGrid(toleranceType, hopCount, totalTimes, i, numberCPUs,
				outputFolder, networkSize, Parameters::setAllStepsRunningByThreadId);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThread, params[i]));
	}
	threads.join_all();
	cout << "Success!" << endl;
}

void SimulatorManager::addOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
		double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	addOneStepSimulation(deploying, toleranceType, 1, totalTimes, nothingProb, inputFolder, outputFolder, numberCPUs, sampleSize);
}
void SimulatorManager::addOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
		double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	Parameters params[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		params[i].nothingStart = (int)round(nothingProb * 100);
		params[i].set(deploying, toleranceType, hopCount, totalTimes, i, numberCPUs,
				inputFolder, outputFolder, sampleSize, Parameters::setOneStepRunningByThreadId);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, params[i]));
	}
	threads.join_all();
}

void SimulatorManager::addOneStepSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, double nothingProb,
		string outputFolder, int numberCPUs, int networkSize)
{
	addOneStepSimulationForGrid(toleranceType, 1, totalTimes, nothingProb, outputFolder, numberCPUs, networkSize);
}

void SimulatorManager::addOneStepSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
		string outputFolder, int numberCPUs, int networkSize)
{
	Parameters params[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		params[i].nothingStart = (int)round(nothingProb * 100);
		params[i].setForGrid(toleranceType, hopCount, totalTimes, i, numberCPUs,
				outputFolder, networkSize, Parameters::setOneStepRunningByThreadId);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, params[i]));
	}
	threads.join_all();
}

void SimulatorManager::addOneStepSimulationForScaleFree(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
		string inputFolder, string outputFolder, int numberCPUs, int sampleSize, bool hubOnly)
{
	Parameters params[numberCPUs];
	boost::thread_group threads;

	for (int i = 0; i < numberCPUs; i++)
	{
		params[i].nothingStart = (int)round(nothingProb * 100);
		params[i].setForScaleFree(toleranceType, hopCount, totalTimes, i, numberCPUs, inputFolder,
				outputFolder, sampleSize, hubOnly, Parameters::setOneStepRunningByThreadId);
		threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, params[i]));
	}
	threads.join_all();
}

void SimulatorManager::runSimulations()
{

}

void SimulatorManager::readResults(DeployingType deploying, TypeOfTolerance toleranceType,
		string inputFolder, string output, int numberCPUs)
{
	for (int i = 0; i < numberCPUs; i++)
	{
		Parameters param;
		param.setToRead(deploying, toleranceType, i, numberCPUs, inputFolder, output, 0);
		ByzantineSimulator::callbackReader(param, true);
	}
	for (int j = numberCPUs - 1; j >= 0; j--)
	{
		Parameters param;
		param.setToRead(deploying, toleranceType, j, numberCPUs, inputFolder, output, 0);
		ByzantineSimulator::callbackReader(param, false);
	}
	cout << "Success!" << endl;
}

void SimulatorManager::readOneStepResults(DeployingType deploying, TypeOfTolerance toleranceType,
			string inputFolder, string output, double nothingProb, double intervalByz)
{
	Parameters param;
	param.nothingStart = (int)round(nothingProb * 100);
	param.setToRead(deploying, toleranceType, nothingProb, 100, inputFolder, output, Parameters::setOneStepRunningByThreadId);
	ByzantineSimulator::callbackOneStepReader(param);// deploying, toleranceType, inputFolder, output, nothingProb, intervalByz);
}

void SimulatorManager::convert2HopInformation(DeployingType deployingType, string inputfolder, string outputFolder, int sampleSize,
		bool using2HopInfo)
{
	Parameters param;
	param.setToConvert(deployingType, inputfolder, outputFolder, sampleSize);
	ByzantineSimulator::callbackConvert(param, using2HopInfo);
}

}
