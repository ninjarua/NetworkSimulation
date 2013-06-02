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
#include "Topology.h"
#include "Deploying.h"
#include "ByzantineProtocol.h"

using namespace domain;
using namespace deployment;
using namespace protocols;

namespace simulators {

class SimulatorBase {
public:
	SimulatorBase();
	virtual ~SimulatorBase();
protected:
	Deploying* _deploying;
	//NetworkGraphics _networkGraphics;
	Network* _network;
	Topology _topology;
	bool _hasTopology;
	int _currentTimeslot;
	ByzantineProtocol _fault;
	virtual void SetDeployment(DeployingType type);

public:
	int timeslot;
	//void (*Writer)(Network*, string);
	void GetParameters(DeployingType deployingType, int numberOfNodes, int transRange, float xTerr, float yTerr, float d0);
	//void CreateGraphic(Graphics graphic, float width, float height, float margin, Color backColor);
	string GetFilenameByDeployment(int number);
	string DeployNetwork(int times, bool drawNetwork);
	string GenerateNetworkFromFile(int fileNumber, bool drawNetwork);
};

} /* namespace deployment */
#endif /* SIMULATORBASE_H_ */
