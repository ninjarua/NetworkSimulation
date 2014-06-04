/*
 * TorusGridDeploying.cc
 *
 *  Created on: Jun 1, 2013
 *      Author: thanh
 */

#include "TorusGridDeploying.h"
#include <stdlib.h>

namespace deployment {

TorusGridDeploying::TorusGridDeploying()
{
    topology->range = 1;
}

TorusGridDeploying::TorusGridDeploying(int size) : Deploying() {
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

TorusGridDeploying::~TorusGridDeploying() {

}

bool TorusGridDeploying::obtainTopology(Network* network)
{
    Deploying::obtainTopology(network);
    int sqrtNumNodes = (int)sqrt(topology->numNodes);
    if (sqrtNumNodes != sqrt(topology->numNodes))
    {
        return false;
    }
    for (int i = 0; i < topology->numNodes; i++)
    {
    	NodePtr newNode(new Node());
        network->addNode(newNode);
    }
    topology->xTerr = topology->range * (sqrt(topology->numNodes) - 1);
    topology->yTerr = topology->range * (sqrt(topology->numNodes) - 1);
    network->transRange = topology->range;
    return true;
}

double TorusGridDeploying::getPosX(int nodeSequenceId)
{
    int sqrtNumNodes = (int)sqrt(topology->numNodes);
    return (nodeSequenceId % sqrtNumNodes) * topology->range;
}

double TorusGridDeploying::getPosY(int nodeSequenceId)
{
    int sqrtNumNodes = (int)sqrt(topology->numNodes);
    return (nodeSequenceId / sqrtNumNodes) * topology->range;
}

bool TorusGridDeploying::isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor)
{
	long sqrtNodes = (long)sqrt(topology->numNodes);
	long x = node->id % sqrtNodes;
	long nx = neighbor->id % sqrtNodes;
	long maxX = (x > nx) ? x : nx;
	long minX = (x < nx) ? x : nx;
	long y = node->id / sqrtNodes;
	long ny = neighbor->id / sqrtNodes;
	long maxY = (y > ny) ? y : ny;
	long minY = (y < ny) ? y : ny;

	if (maxX == sqrtNodes - 1)
		maxX = -1;
	if (maxY == sqrtNodes - 1)
		maxY = -1;

    // distance between a given pair of nodes
    return abs(maxX - minX + maxY - minY) == 1;
}

string TorusGridDeploying::getDeployingName()
{
	return "TorusGrid";
}

} /* namespace domain */
