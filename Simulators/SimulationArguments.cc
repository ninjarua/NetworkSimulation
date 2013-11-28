/*
 * SimulationArguments.cc
 *
 *  Created on: Nov 27, 2013
 *      Author: thanh
 */

#include "SimulationArguments.h"

namespace simulators {

SimulationArguments::SimulationArguments() {
	_argumentType = GeneralAllSteps;
	_deployingType = TorusGrid;
	_toleranceType = KSelf;
	_cpus = 1;

	_sampleSize = 100;
	_gridSize = 0;

	_hopCount = 1;
	_hubOnly = false;

	_totalTimes = 10000;
	_inputFolder = "";
	_output = "";
	_nothingStart = 0;
}

SimulationArguments::~SimulationArguments() {

}

SimulationArguments::SimulationArguments(ArgumentType argumentType, DeployingType deployingType, TypeOfTolerance toleranceType,
		int totalTimes, string inputFolder, string output, int sampleSize, int cpus,
		int nothingStart, int hopCount, bool hubOnly)
{
	_argumentType = argumentType;
	_deployingType = deployingType;
	_toleranceType = toleranceType;
	_cpus = cpus;

	_sampleSize = sampleSize;
	_gridSize = 0;

	_hopCount = hopCount;
	_hubOnly = hubOnly;

	_totalTimes = totalTimes;
	_inputFolder = inputFolder;
	_output = output;
	_nothingStart = nothingStart;
}

SimulationArguments::SimulationArguments(ArgumentType argumentType, TypeOfTolerance toleranceType, int totalTimes, string output,
		int gridSize, int cpus, int nothingStart, int hopCount)
{
	_argumentType = argumentType;
	_deployingType = TorusGrid;
	_toleranceType = toleranceType;
	_cpus = cpus;

	_sampleSize = 100;
	_gridSize = gridSize;

	_hopCount = hopCount;
	_hubOnly = false;

	_totalTimes = totalTimes;
	_inputFolder = "";
	_output = output;
	_nothingStart = nothingStart;
}

} /* namespace generators */
