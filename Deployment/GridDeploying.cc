/*
 * GridDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "GridDeploying.h"

namespace deployment {

GridDeploying::GridDeploying() : Deploying() {
    topology->range = 1;
}

GridDeploying::GridDeploying(int size) : Deploying() {
	topology->numNodes = size;
	topology->range = 1;
	int sqrtNumNodes = (int)sqrt(topology->numNodes);
	if (sqrtNumNodes != sqrt(topology->numNodes))
	{
		throw nsException("Error: on GRID topology, NUMBER_OF_NODES should be the square of a natural number");
	}
	topology->xTerr = topology->range * (sqrt(topology->numNodes) - 1);
	topology->yTerr = topology->range * (sqrt(topology->numNodes) - 1);
}

GridDeploying::~GridDeploying() {

}

string GridDeploying::getDeployingName()
{
	return "Grid";
}

bool GridDeploying::obtainTopology(Network* network)
{
	Deploying::obtainTopology(network);
	if (topology->range < topology->d0)
	{
		return false;
	}
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node());
		network->addNode(newNode);
	}
	return true;
}

double GridDeploying::getPosX(int nodeSequenceId)
{
	int sqrtNumNodes = (int)sqrt(topology->numNodes);
	return (nodeSequenceId % sqrtNumNodes) * topology->range;
}

double GridDeploying::getPosY(int nodeSequenceId)
{
	int sqrtNumNodes = (int)sqrt(topology->numNodes);
	return (nodeSequenceId / sqrtNumNodes) * topology->range;
}

bool GridDeploying::isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor)
{
	long sqrtNodes = (long)sqrt(topology->numNodes);
	long x = node->id % sqrtNodes;
	long nx = neighbor->id % sqrtNodes;
	long y = node->id / sqrtNodes;
	long ny = neighbor->id % sqrtNodes;
	return (abs(nx - x) + abs(ny - y)) == 1;
}

} /* namespace protocols */
