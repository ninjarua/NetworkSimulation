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
	//void (*Writer)(Network*, string);
	//void GetParameters(DeployingType deployingType, int numberOfNodes, int transRange, float xTerr, float yTerr, float d0);
	//void CreateGraphic(Graphics graphic, float width, float height, float margin, Color backColor);
	//string GetFilenameByDeployment(int number);
	string GenerateNetwork(DeployingType deployment, int numberOfNode, float xTerr, float yTerr,
			float range, float d0, int times, string folder);
	//string GenerateNetworkFromFile(int fileNumber, bool drawNetwork);
};

} /* namespace deployment */
#endif /* SIMULATORBASE_H_ */
