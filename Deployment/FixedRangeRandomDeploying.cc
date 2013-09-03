/*
 * FixedRangeRandomDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "FixedRangeRandomDeploying.h"

namespace deployment {

FixedRangeRandomDeploying::FixedRangeRandomDeploying() : Deploying()
{

}

FixedRangeRandomDeploying::FixedRangeRandomDeploying(int numberNodes, int xTerr, int yTerr, int range) : Deploying() {
	topology->numNodes = numberNodes;
	topology->xTerr = xTerr;
	topology->yTerr = yTerr;
	topology->range = range;
	topology->d0 = 1;
}

FixedRangeRandomDeploying::~FixedRangeRandomDeploying() {

}

void FixedRangeRandomDeploying::neighborInitialization(Network* network)
{
	Deploying::neighborInitialization(network);
}

bool FixedRangeRandomDeploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	return Deploying::isNeighbors(network, node, neighbor);
}

string FixedRangeRandomDeploying::getDeployingName()
{
	return "FixedRange";
}

bool FixedRangeRandomDeploying::obtainTopology(Network* network)
{
	Deploying::obtainTopology(network);
	if ((topology->xTerr < 0) | (topology->yTerr < 0))
	{
		string errorMessage = "Error: values of TERRAIN_DIMENSIONS must be positive";
		throw nsException(errorMessage);
	}
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node(getPosX(i), getPosY(i)));
		network->addNode(newNode);
	}
	return true;
}

double FixedRangeRandomDeploying::getPosX(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->xTerr;
}

double FixedRangeRandomDeploying::getPosY(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->yTerr;
}

double FixedRangeRandomDeploying::getCellLength()
{
	return sqrt(topology->Area() / topology->numNodes);
}

} /* namespace protocols */
