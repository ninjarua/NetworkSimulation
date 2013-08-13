/*
 * Parameters.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: thanhnd
 */

#include "Parameters.h"

namespace simulators{

Parameters::Parameters()
{
	nothingInterval = byzantineInterval = 0.01;
}

Parameters::~Parameters()
{

}

void Parameters::setOneStepRunningByThreadId(Parameters* params, int _threadId, int _totalThread)
{
	int interval = (101 - params->nothingStart)/_totalThread;
	params->nothingEnd = params->nothingStart;
	params->byzantineStart = _threadId * interval;
	params->byzantineEnd = (double)(_threadId + 1) * interval - 1;
}

void Parameters::setAllStepsRunningByThreadId(Parameters* params, int _threadId, int _totalThread)
{
	int slotSize = 50 / _totalThread;
	params->nothingStart = _threadId * slotSize;
	params->nothingEnd = params->nothingStart + (slotSize - 1);
	params->byzantineStart = 0;
	params->byzantineEnd = 100 - params->nothingEnd;
}

void Parameters::compensateAllStepsRunningByThreadId(Parameters* params)
{
	int oldStart = params->nothingStart;
	params->nothingStart = 99 - params->nothingEnd;
	params->nothingEnd = 99 - oldStart;
	params->byzantineEnd = 100 - params->nothingEnd;
}

void Parameters::setToRead(DeployingType _deploying, TypeOfTolerance _toleranceType, int _threadId,
			int _totalThread, string _inputFolder, string _outputFolder,
			void (*setRunning)(Parameters* params, int, int))
{
	nothingInterval = byzantineInterval = 0.01;
	hopCount = 0;
	deployingType = _deploying;
	toleranceType = _toleranceType;
	totalTimes = 0;
	inputFolder = _inputFolder;
	output = _outputFolder;
	sampleSize = 1;
	setRunning(this, _threadId, _totalThread);
	networkSize = 100;
	hubOnly = false;
}

void Parameters::setToConvert(DeployingType _deploying, string _inputFolder, string _outputFolder, int _sampleSize)
{
	nothingInterval = byzantineInterval = 0.01;
	hopCount = 0;
	deployingType = _deploying;
	toleranceType = K01;
	totalTimes = 0;
	inputFolder = _inputFolder;
	output = _outputFolder;
	sampleSize = _sampleSize;
	networkSize = 100;
	hubOnly = false;

}

void Parameters::set(DeployingType _deploying, TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes,
		int _threadId, int _totalThread, string _inputFolder, string _outputFolder, int _sampleSize,
		void (*setRunning)(Parameters* params, int, int))
{
	nothingInterval = byzantineInterval = 0.01;
	hopCount = _hopCount;
	deployingType = _deploying;
	toleranceType = _toleranceType;
	totalTimes = _totalTimes;
	inputFolder = _inputFolder;
	output = _outputFolder;
	sampleSize = _sampleSize;
	setRunning(this, _threadId, _totalThread);
	networkSize = 100;
	hubOnly = false;
}

void Parameters::setForScaleFree(TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes,
		int _threadId, int _totalThread, string _inputFolder, string _outputFolder,
		bool _hubOnly, int _sampleSize,
		void (*setRunning)(Parameters* params, int, int))
{
	nothingInterval = byzantineInterval = 0.01;
	hopCount = _hopCount;
	deployingType = ScaleFree;
	toleranceType = _toleranceType;
	totalTimes = _totalTimes;
	inputFolder = _inputFolder;
	output = _outputFolder;
	sampleSize = _sampleSize;
	setRunning(this, _threadId, _totalThread);
	networkSize = 100;
	hubOnly = _hubOnly;
}

void Parameters::setForGrid(TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes, int _threadId,
			int _totalThread, string _outputFolder, int _networkSize,
			void (*setRunning)(Parameters* params, int, int))
{
	nothingInterval = byzantineInterval = 0.01;
	hopCount = _hopCount;
	deployingType = TorusGrid;
	toleranceType = _toleranceType;
	totalTimes = _totalTimes;
	inputFolder = "";
	output = _outputFolder;
	sampleSize = 1;
	setRunning(this, _threadId, _totalThread);
	networkSize = _networkSize;
	hubOnly = false;
}

}
