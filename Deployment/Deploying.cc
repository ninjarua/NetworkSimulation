/*
 * Deploying.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Deploying.h"

namespace deployment {
Deploying::Deploying() {
	topology = new Topology();
	using2HopInfo = false;
}

Deploying::~Deploying() {

}

bool Deploying::obtainTopology(Network* network)
{
	network->Reset();
	network->size = topology->numNodes;
	return true;
}

double Deploying::getPosX(int nodeSequenceId)
{
	return 0;
}

double Deploying::getPosY(int nodeSequenceId)
{
	return 0;
}

double Deploying::getCellLength()
{
	return 0;
}

bool Deploying::isValidDistance(const Node& node, const Node& neighbor)
{
	double Xdist, Ydist, dist;
	Xdist = node.posX - neighbor.posX;
	Ydist = node.posY - neighbor.posY;
	dist = pow((Xdist * Xdist + Ydist * Ydist), 0.5);
	return (dist >= topology->d0);
}

bool Deploying::isAllDistanceValid(const Network& network, const Node& node)
{
	int size = network.nodes.size();
	for (int j = 0; j < size - 1; j = j + 1)
	{
		if (!isValidDistance(node, *network.nodes.at(j)))
		{
			return false;
		}
	}
	return true;
}

string Deploying::getDeployingName()
{
	return "General";
}

bool Deploying::runDeploy(Network* network)
{
	if (obtainTopology(network))
	{
		neighborInitialization(network);
		if (using2HopInfo)
			network->createAdvancedInformation();
		return true;
	}
	return false;
}

void Deploying::neighborInitialization(Network* network)
{
	int nSize = network->nodes.size();
	for (int i = 0; i < nSize - 1; i++)
	{
		for (unsigned int j = i + 1; j < network->nodes.size(); j++)
		{
			if (isNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				network->makeNeighbors(i, j);
			}
		}
	}
	createInformationOfGraph(network);
}

void Deploying::createInformationOfGraph(Network* network)
{

}

bool Deploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	// test for commit
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

}
/* namespace deployment */
