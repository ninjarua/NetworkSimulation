/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "SimulatorBase.h"
#include "GridDeploying.h"
#include "FixedRangeRandomDeploying.h"

namespace simulators {

SimulatorBase::SimulatorBase() {
	_deploying = new Deploying();
	//NetworkGraphics _networkGraphics;
	_network = new Network();
	_topology = new Topology();
	_hasTopology = false;
	_currentTimeslot = 1;
}

SimulatorBase::~SimulatorBase() {
	// TODO Auto-generated destructor stub
}

void SimulatorBase::SetDeployment(DeployingType type)
{
	switch(type)
	{
	case Ring:
		break;
	case TorusGrid:
	case Grid:
		_deploying = new GridDeploying();
		break;
	case ER_Random:
	case ScaleFree:
	case FixedRange:
		_deploying = new FixedRangeRandomDeploying();
		break;
	default:
		break;
	}
}

void SimulatorBase::GetParameters(DeployingType deployment, int numberOfNodes, int transRange, float xTerr, float yTerr, float d0, bool checkConflict)
{
    _topology->NumNodes = numberOfNodes;
    _topology->XTerr = xTerr;
    _topology->YTerr = yTerr;
    _topology->D0 = d0;
    _topology->Distance = transRange;

    SetDeployment(deployment);
    _deploying->networkTopology = _topology;

    _network->transRange = transRange;
    //_network.collisionChecking = checkConflict;
}

string SimulatorBase::DeployNetwork(bool drawNetwork)
{
    _hasTopology = _deploying->RunDeploy(_network);
    if (_hasTopology && drawNetwork)
    {
        //_networkGraphics.DrawNetwork(_network, false, false, true);
        return "Success";
    }
    return "Cannot create network.";
}
} /* namespace deployment */
