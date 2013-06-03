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

string SimulatorBase::GenerateNetwork(DeployingType deployment, int numberOfNode, float xTerr, float yTerr,
			float range, float d0, int times, string folder)
{
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
		generator = new FixedRangeGenerator(numberOfNode, xTerr, yTerr, range);
		generator->GenerateToFiles(network, folder, times);
		break;
	case Ring:
		break;
	case ER_Random:
		break;
	case ScaleFree:
		break;
	default:
		break;
	}
	return "Success";
}

} /* namespace deployment */
