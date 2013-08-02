/*
 * RepeatParameters.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef REPEATPARAMETERS_H_
#define REPEATPARAMETERS_H_
#include "enums.h"
#include "ToleranceBase.h"

using namespace protocols;

namespace simulators{

class Parameters
{
public:
	Parameters();
	~Parameters();
	DeployingType deployingType;
	TypeOfTolerance toleranceType;

	int networkSize;
	int hopCount;
	bool hubOnly;

	int totalTimes;
	string inputFolder;
	string output;

	int nothingStart;
	int byzantineStart;
	int nothingEnd;
	int byzantineEnd;
	double nothingInterval;
	double byzantineInterval;

	int byzantineSteps;
	int nothingSteps;

	int sampleSize;

	static void setOneStepRunningByThreadId(Parameters* params, int _threadId, int _totalThread);
	static void setAllStepsRunningByThreadId(Parameters* params, int _threadId, int _totalThread);
	static void compensateAllStepsRunningByThreadId(Parameters* params);

	void setToRead(DeployingType _deploying, TypeOfTolerance _toleranceType, int _threadId,
				int _totalThread, string _inputFolder, string _outputFolder,
				void (*setRunning)(Parameters* params, int, int));
	void set(DeployingType _deploying, TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes, int _threadId,
			int _totalThread, string _inputFolder, string _outputFolder, int _sampleSize,
			void (*setRunning)(Parameters* params, int, int));
	void setForScaleFree(TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes, int _threadId,
			int _totalThread, string _inputFolder, string _outputFolder, bool _hubOnly, int _sampleSize,
			void (*setRunning)(Parameters* params, int, int));
	void setForGrid(TypeOfTolerance _toleranceType, int _hopCount, int _totalTimes, int _threadId,
				int _totalThread, string _outputFolder, int _networkSize,
				void (*setRunning)(Parameters* params, int, int));
};

}
#endif /* REPEATPARAMETERS_H_ */
