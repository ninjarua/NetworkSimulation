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
protected:
	NetworkGenerator* generator;
	//NetworkGraphics _networkGraphics;
	Network* network;
	int _currentTimeslot;
	ByzantineProtocol _fault;

public:
	int timeslot;
	string GenerateNetwork(DeployingType deployment, int numberOfNode, int times, string folder,
			float xTerr = 100, float yTerr = 100, float range = 1, float d0 = 1, double prob = 1);
};

} /* namespace deployment */
#endif /* SIMULATORBASE_H_ */
