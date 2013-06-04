/*
 * RepeatParameters.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef REPEATPARAMETERS_H_
#define REPEATPARAMETERS_H_
#include "stdafx.h"
namespace simulators{

struct Parameters
{
	int totalTimes;
	int sampleSize;
	int nothingStart;
	int byzantineStart;
	int nothingEnd;
	int byzantineEnd;
	int byzantineSteps;
	int nothingSteps;
	string inputFolder;
	string outputFolder;
};

}
#endif /* REPEATPARAMETERS_H_ */
