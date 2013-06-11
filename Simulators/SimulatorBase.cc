/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "SimulatorBase.h"
#include "GridGenerator.h"
#include "FixedRangeGenerator.h"
#include "TorusGridGenerator.h"
#include "ERRandomGenerator.h"
#include "ScaleFreeGenerator.h"
#include <stdlib.h>
#include <stdio.h>

namespace simulators {

SimulatorBase::SimulatorBase() {
	generator = new NetworkGenerator();
	network = new Network();
	_currentTimeslot = 1;
}

SimulatorBase::~SimulatorBase() {

}
string SimulatorBase::GenerateFixedRangeNetwork(int times, int size, string folder,
		float xTerr, float yTerr, float range, float d0)
{
	generator = new FixedRangeGenerator(size, xTerr, yTerr, range);
	generator->GenerateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::GenerateER_RandomNetwork(int times, int size, string folder, double prob)
{
	generator = new ERRandomGenerator(size, prob);
	generator->GenerateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::GenerateScaleFreeNetwork(int times, string folder, int cliqueSize, int size, int edge)
{
	generator = new ScaleFreeGenerator(cliqueSize, edge, size);
	generator->GenerateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::GenerateNetwork(DeployingType deployment, int numberOfNode, int times, string folder,
			float xTerr, float yTerr, float range, float d0, double prob)
{
	string result;
	network->transRange = range;
	switch(deployment)
	{
	case Grid:
		generator = new GridGenerator(numberOfNode);
		generator->GenerateToFiles(network, folder);
		break;
	case TorusGrid:
		generator = new TorusGridGenerator(numberOfNode);
		generator->GenerateToFiles(network, folder);
		break;
	case FixedRange:
		result = GenerateFixedRangeNetwork(times, numberOfNode, folder, xTerr, yTerr, range, d0);
		break;
	case Ring:
		break;
	case ER_Random:
		result = GenerateER_RandomNetwork(times, numberOfNode, folder, prob);
		break;
	default:
		break;
	}
	return result;
}

} /* namespace deployment */
