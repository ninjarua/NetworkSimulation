/*
 * ThreadArguments.h
 *
 *  Created on: Jun 5, 2013
 *      Author: thanh
 */

#ifndef THREADARGUMENTS_H_
#define THREADARGUMENTS_H_

#include "ByzantineSimulator.h"

namespace simulators
{
class ThreadArguments
{
public:
	DeployingType deploying;
	TypeOfTolerance toleranceType;
	int totalTimes;
	string inputFolder;
	string outputFolder;
	int numberCPUs;
	int sampleSize;

	ThreadArguments(DeployingType _deploying, TypeOfTolerance _toleranceType, int _totalTimes,
			string _inputFolder, string _outputFolder, int _numberCPUs, int _sampleSize)
	{
		deploying = _deploying;
		toleranceType = _toleranceType;
		totalTimes = _totalTimes;
		inputFolder = _inputFolder;
		outputFolder = _outputFolder;
		numberCPUs = _numberCPUs;
		sampleSize = _sampleSize;
	}
};
}
#endif /* THREADARGUMENTS_H_ */
