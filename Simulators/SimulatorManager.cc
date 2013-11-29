/*
 * SimulatorManager.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "SimulatorManager.h"
#include "Parameters.h"
#include <cmath>

namespace simulators
{

SimulatorManager::SimulatorManager() {
	listArgumentSimulation = vector<SimulationArguments*>();
	numberCPUs = 0;
	totalThreadsNeedToRun = 0;
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
	listArgumentSimulation.push_back(new SimulationArguments(GeneralAllSteps, deploying, toleranceType, totalTimes, inputFolder, outputFolder,
			sampleSize, numberCPUs, 0, hopCount));
}

void SimulatorManager::addSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, string outputFolder, int numberCPUs, int networkSize)
{
	addSimulationForGrid(toleranceType, 1, totalTimes, outputFolder, numberCPUs, networkSize);
}

void SimulatorManager::addSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, string outputFolder,
		int numberCPUs, int networkSize)
{
	listArgumentSimulation.push_back(new SimulationArguments(GridAllSteps, toleranceType, totalTimes, outputFolder,
			networkSize, numberCPUs, 0, hopCount));
}

void SimulatorManager::addOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int totalTimes,
		double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	addOneStepSimulation(deploying, toleranceType, 1, totalTimes, nothingProb, inputFolder, outputFolder, numberCPUs, sampleSize);
}

void SimulatorManager::addOneStepSimulation(DeployingType deploying, TypeOfTolerance toleranceType, int hopCount, int totalTimes,
		double nothingProb, string inputFolder, string outputFolder, int numberCPUs, int sampleSize)
{
	listArgumentSimulation.push_back(new SimulationArguments(GeneralOneStep, deploying, toleranceType, totalTimes, inputFolder, outputFolder,
			sampleSize, numberCPUs, nothingProb, hopCount));
}

void SimulatorManager::addOneStepSimulationForGrid(TypeOfTolerance toleranceType, int totalTimes, double nothingProb,
		string outputFolder, int numberCPUs, int networkSize)
{
	addOneStepSimulationForGrid(toleranceType, 1, totalTimes, nothingProb, outputFolder, numberCPUs, networkSize);
}

void SimulatorManager::addOneStepSimulationForGrid(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
		string outputFolder, int numberCPUs, int networkSize)
{
	listArgumentSimulation.push_back(new SimulationArguments(GridOneStep, toleranceType, totalTimes, outputFolder,
			networkSize, numberCPUs, nothingProb, hopCount));
}

void SimulatorManager::addOneStepSimulationForScaleFree(TypeOfTolerance toleranceType, int hopCount, int totalTimes, double nothingProb,
		string inputFolder, string outputFolder, int numberCPUs, int sampleSize, bool hubOnly)
{
	listArgumentSimulation.push_back(new SimulationArguments(ScaleFreeOneStep, ScaleFree, toleranceType, totalTimes, inputFolder, outputFolder,
			sampleSize, numberCPUs, nothingProb, hopCount, hubOnly));

}

void SimulatorManager::runSimulationsTest(unsigned int size, unsigned int rank)
{
	Parameters param;

//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for (unsigned int i=0; i < listArgumentSimulation.size(); i++)
		totalThreadsNeedToRun += listArgumentSimulation[i]->_cpus;

	unsigned int idxArgument = 0;
	unsigned int numberOfLoops = ceil((double)totalThreadsNeedToRun/size);
	cout << "Size: " << size << endl;
	cout << "Number of loops: " << numberOfLoops << endl;
	for (unsigned int i = 0; i < numberOfLoops; i++)
	{
		unsigned int count = 0;
		while (count <= rank && idxArgument < listArgumentSimulation.size())
		{// rank = 10, size = 100, _cpus = 100
			count += listArgumentSimulation[idxArgument]->_cpus;
			idxArgument++;
		}
		if (count <= rank)
		{
			cout << "Last one no need" << endl;
			break;
		}
		idxArgument--;
		count -= listArgumentSimulation[idxArgument]->_cpus;
		SimulationArguments* simArg = listArgumentSimulation[idxArgument];
		int j = rank - count;
		cout << "Argument index: " << idxArgument << ". Rank: " << rank << ". J: " << j << endl;
		while(count < size)
		{
			count += simArg->_cpus;
			idxArgument++;
		}
	}
}

void SimulatorManager::runSimulations()
{
	boost::thread_group threads;
	int numberOfLoops = ceil((double)totalThreadsNeedToRun/numberCPUs);

	int idxArgument = 0;
	for (int i = 0; i < numberOfLoops; i++)
	{
		int count = 0;
		while(count < numberCPUs)
		{
			SimulationArguments* simArg = listArgumentSimulation[idxArgument];
			count += simArg->_cpus;
			for (int j = 0; j < simArg->_cpus; j++)
			{
				Parameters params;
				switch(simArg->_argumentType)
				{
				case GeneralAllSteps:
					params.set(simArg->_deployingType, simArg->_toleranceType, simArg->_hopCount,
							simArg->_totalTimes, j, simArg->_cpus,
							simArg->_inputFolder, simArg->_output, simArg->_sampleSize,
							Parameters::setAllStepsRunningByThreadId);
					break;
				case GridAllSteps:
					params.setForGrid(simArg->_toleranceType, simArg->_hopCount,
							simArg->_totalTimes, j, simArg->_cpus,
							simArg->_output, simArg->_gridSize,
							Parameters::setAllStepsRunningByThreadId);
					break;
				case GeneralOneStep:
					params.nothingStart = (int)round(simArg->_nothingStart* 100);
					params.set(simArg->_deployingType, simArg->_toleranceType, simArg->_hopCount,
							simArg->_totalTimes, j, simArg->_cpus,
							simArg->_inputFolder, simArg->_output, simArg->_sampleSize,
							Parameters::setOneStepRunningByThreadId);
					break;
				case GridOneStep:
					params.nothingStart = (int)round(simArg->_nothingStart* 100);
					params.setForGrid(simArg->_toleranceType, simArg->_hopCount,
							simArg->_totalTimes, j, simArg->_cpus,
							simArg->_output, simArg->_gridSize,
							Parameters::setOneStepRunningByThreadId);
					break;
				case ScaleFreeOneStep:
					params.nothingStart = (int)round(simArg->_nothingStart* 100);
					params.setForScaleFree(simArg->_toleranceType, simArg->_hopCount,
							simArg->_totalTimes, j, simArg->_cpus,
							simArg->_inputFolder, simArg->_output,
							simArg->_sampleSize, simArg->_hubOnly, Parameters::setOneStepRunningByThreadId);
					break;
				}
				threads.create_thread(boost::bind(ByzantineSimulator::callbackThreadOneStep, params));
			}
			idxArgument++;
		}
		threads.join_all();
	}
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
