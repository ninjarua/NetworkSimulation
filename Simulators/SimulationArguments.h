/*
 * SimulationArguments.h
 *
 *  Created on: Nov 27, 2013
 *      Author: thanh
 */

#ifndef SIMULATIONARGUMENTS_H_
#define SIMULATIONARGUMENTS_H_
#include "enums.h"
#include "ToleranceBase.h"

using namespace protocols;

namespace simulators {

enum ArgumentType {GeneralAllSteps = 0, GeneralOneStep = 1, GridAllSteps = 2, GridOneStep = 3, ScaleFreeOneStep = 4};

class SimulationArguments {
public:
	DeployingType _deployingType;
	TypeOfTolerance _toleranceType;
	ArgumentType _argumentType;
	int _cpus;

	double _nothingStart;
	int _sampleSize;
	int _gridSize;

	int _hopCount;
	bool _hubOnly;

	int _totalTimes;
	string _inputFolder;
	string _output;
public:
	SimulationArguments();
	SimulationArguments(ArgumentType argumentType, DeployingType deployingType, TypeOfTolerance toleranceType,
			int totalTimes, string inputFolder, string output, int sampleSize, int cpus,
			int nothingStart = 0, int hopCount=0, bool hubOnly=false);
	SimulationArguments(ArgumentType argumentType, TypeOfTolerance toleranceType, int totalTimes, string output,
			int gridSize, int cpus, int nothingStart = 0, int hopCount=0);
	virtual ~SimulationArguments();
};

} /* namespace generators */
#endif /* SIMULATIONARGUMENTS_H_ */
