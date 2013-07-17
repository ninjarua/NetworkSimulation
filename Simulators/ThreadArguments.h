/*
 * ThreadArguments.h
 *
 *  Created on: Jun 5, 2013
 *      Author: thanh
 */

#ifndef THREADARGUMENTS_H_
#define THREADARGUMENTS_H_

#include "enums.h"
#include "ByzantineSimulator.h"
#include "ToleranceBase.h"

using namespace protocols;

namespace simulators
{
class ThreadArguments
{
public:
	DeployingType deploying;
	TypeOfTolerance toleranceType;
	int totalTimes;
	string inputFolder;
	string output;
	int numberCPUs;
	int threadId;
	int sampleSize;
	int networkSize;
	int hopCount;

	ThreadArguments(){}

	void set(DeployingType _deploying, TypeOfTolerance _toleranceType, int _threadId,
			int _numberCPUs, string _inputFolder, string _outputFolder, int _sampleSize)
	{
		hopCount = 0;
		deploying = _deploying;
		toleranceType = _toleranceType;
		totalTimes = 0;
		inputFolder = _inputFolder;
		output = _outputFolder;
		numberCPUs = _numberCPUs;
		sampleSize = _sampleSize;
		threadId = _threadId;
		networkSize = 100;
	}

	void set(DeployingType _deploying, TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes, int _threadId,
			int _numberCPUs, string _inputFolder, string _outputFolder, int _sampleSize)
	{
		hopCount = _hopCount;
		deploying = _deploying;
		toleranceType = _toleranceType;
		totalTimes = _totalTimes;
		inputFolder = _inputFolder;
		output = _outputFolder;
		numberCPUs = _numberCPUs;
		sampleSize = _sampleSize;
		threadId = _threadId;
		networkSize = 100;
	}

	void setForGrid(TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes, int _threadId,
				int _numberCPUs, string _outputFolder, int _networkSize = 100)
	{
		hopCount = _hopCount;
		deploying = TorusGrid;
		toleranceType = _toleranceType;
		totalTimes = _totalTimes;
		inputFolder = "";
		output = _outputFolder;
		numberCPUs = _numberCPUs;
		sampleSize = 1;
		threadId = _threadId;
		networkSize = _networkSize;
	}
};
}
#endif /* THREADARGUMENTS_H_ */
