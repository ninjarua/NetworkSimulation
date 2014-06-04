/*
 * ERRandomDeploying.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "ERRandomDeploying.h"

namespace deployment {

ERRandomDeploying::ERRandomDeploying() : Deploying() {

}

ERRandomDeploying::ERRandomDeploying(int numberNodes, double probability)
{
	connectedProbability = probability;
	topology->numNodes = numberNodes;
	topology->xTerr = 100;
	topology->yTerr = 100;
	topology->range = 1;
	topology->d0 = 1;
}

ERRandomDeploying::~ERRandomDeploying() {
}

bool ERRandomDeploying::isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor)
{
	return ((double)rand() / RAND_MAX) < connectedProbability;
}

string ERRandomDeploying::getDeployingName()
{
	return "Erdos_Renyi";
}

double ERRandomDeploying::getPosX(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->xTerr;
}

double ERRandomDeploying::getPosY(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->yTerr;
}

bool ERRandomDeploying::obtainTopology(Network* network)
{
	Deploying::obtainTopology(network);
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node());
		network->addNode(newNode);
	}
	return true;
}

}
