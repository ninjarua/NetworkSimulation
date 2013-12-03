/*
 * PropagationSimulator.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef SIMULATORBASE_H_
#define SIMULATORBASE_H_

#include "stdafx.h"
#include <string>
#include <fstream>

#include "Network.h"
#include "Logger.h"
#include "ByzantineProtocol.h"
#include "NetworkGenerator.h"
#include "enums.h"

using namespace domain;
using namespace generators;
using namespace protocols;

namespace simulators {

class SimulatorBase {
public:
	SimulatorBase();
	virtual ~SimulatorBase();
	bool need2HopInfo;
protected:
	NetworkGenerator* generator;
	//NetworkGraphics _networkGraphics;
	Network* network;
	int _currentTimeslot;
	ByzantineProtocol _fault;

public:
	//int timeslot;
	string generateGridNetwork(int times, int size, string folder);
	string generateTorusGridNetwork(int times, int size, string folder);
	string generateFixedRangeNetwork(int times, int size, string folder,
			float xTerr, float yTerr, float range, float d0);
	string generateSmallworldNetwork(int times, int size, string folder, int numberOfShortEdges, int numberOfLongEdges,
			float xTerr, float yTerr, float range, float d0);
	string generateER_RandomNetwork(int times, int size, string folder, double prob);
	string generateScaleFreeNetwork(int times, string folder, int cliqueSize, int size, int edge);
};

} /* namespace deployment */
#endif /* SIMULATORBASE_H_ */
