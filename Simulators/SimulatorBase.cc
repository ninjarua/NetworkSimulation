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
#include "SmallworldGenerator.h"
#include <stdlib.h>
#include <stdio.h>

namespace simulators {

SimulatorBase::SimulatorBase() {
	generator = new NetworkGenerator();
	network = new Network();
	_currentTimeslot = 1;
//	timeslot = 0;
}

SimulatorBase::~SimulatorBase() {

}
string SimulatorBase::generateFixedRangeNetwork(int times, int size, string folder,
		float xTerr, float yTerr, float range, float d0)
{
	network->transRange = range;
	generator = new FixedRangeGenerator(size, xTerr, yTerr, range);
	generator->generateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::generateSmallworldNetwork(int times, int size, string folder, int numberOfShortEdges, int numberOfLongEdges,
			float xTerr, float yTerr, float range, float d0)
{
	network->transRange = range;
	generator = new SmallworldGenerator(size, xTerr, yTerr, range, numberOfShortEdges, numberOfLongEdges);
	generator->generateToFiles(network, folder, times);
	cout << endl;
	return "Success";
}

string SimulatorBase::generateER_RandomNetwork(int times, int size, string folder, double prob)
{
	generator = new ERRandomGenerator(size, prob);
	generator->generateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::generateScaleFreeNetwork(int times, string folder, int cliqueSize, int size, int edge)
{
	generator = new ScaleFreeGenerator(cliqueSize, edge, size);
	generator->generateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::generateGridNetwork(int times, int size, string folder)
{
	generator = new GridGenerator(size);
	generator->generateToFiles(network, folder, times);
	return "Success";
}

string SimulatorBase::generateTorusGridNetwork(int times, int size, string folder)
{
	generator = new TorusGridGenerator(size);
	generator->generateToFiles(network, folder, times);
	return "Success";
}

} /* namespace deployment */
