/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "SimulatorBase.h"
#include "GridDeploying.h"
#include "FixedRangeRandomDeploying.h"
#include "TorusGridDeploying.h"
#include <stdlib.h>
#include <stdio.h>

namespace simulators {

SimulatorBase::SimulatorBase() {
	_deploying = new Deploying();
	//NetworkGraphics _networkGraphics;
	_network = new Network();
	_topology = Topology();
	_hasTopology = false;
	_currentTimeslot = 1;
}

SimulatorBase::~SimulatorBase() {

}

void SimulatorBase::SetDeployment(DeployingType type)
{
	switch(type)
	{
	case Ring:
		break;
	case TorusGrid:
		_deploying = new TorusGridDeploying();
		break;
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

void SimulatorBase::GetParameters(DeployingType deployment, int numberOfNodes, int transRange, float xTerr, float yTerr, float d0)
{
    _topology.NumNodes = numberOfNodes;
    _topology.XTerr = xTerr;
    _topology.YTerr = yTerr;
    _topology.D0 = d0;
    _topology.Distance = transRange;

    SetDeployment(deployment);
    _deploying->networkTopology = _topology;

    _network->transRange = transRange;
    //_network.collisionChecking = checkConflict;
}

string GetFilename(int id)
{
	char number[9];
	sprintf(number, "%04d.out", id);
	string filename("graph_");
	filename = filename + number;
	return filename;
}

string GetVerifyFilename(int id)
{
	char number[18];
	sprintf(number, "%04d_verified.out", id);
	string filename("graph_");
	filename = filename + number;
	return filename;
}

string GetFailureString(int count)
{
	char number[5];
	string results("Cannot create all graphs!\n");
	results = results + "Only create";
	sprintf(number, "%04d", count);
	results = results + number;
	return results;
}

string SimulatorBase::GetFilenameByDeployment(int number)
{
	return _deploying->GetDeployingName() + "_" + GetFilename(number);
}

string SimulatorBase::DeployNetwork(int times, bool drawNetwork)
{
	for (int i = 0; i < times; i++)
	{
		_hasTopology = _deploying->RunDeploy(_network);
		if (_hasTopology)
		{
			Logger::Write(_network, GetFilenameByDeployment(i + 1));
			//if (drawNetwork)
		}
		else
		{
			return GetFailureString(i + 1);
		}
	}
	return "Success";
}

string SimulatorBase::GenerateNetworkFromFile(int fileNumber, bool drawNetwork)
{
	ifstream f(GetFilenameByDeployment(fileNumber).c_str(), ifstream::in);
	f >> (*_network);
	f.close();
	return "Success";
}

} /* namespace deployment */
