/*
 * SmallworldDeploying.cc
 *
 *  Created on: Jul 26, 2013
 *      Author: thanhnd
 */

#include "SmallworldDeploying.h"

namespace deployment {

SmallworldDeploying::SmallworldDeploying() : FixedRangeRandomDeploying()
{
	topology->range = 1;
}

SmallworldDeploying::SmallworldDeploying(int numberNodes, int xTerr, int yTerr, int range, int noOfLongEdge)
	: FixedRangeRandomDeploying(numberNodes, xTerr, yTerr, range)
{
	numberOfLongEdge = noOfLongEdge;
}

SmallworldDeploying::~SmallworldDeploying() {
	delete topology;
}

string SmallworldDeploying::getDeployingName()
{
	return "Smallworld";
}

bool SmallworldDeploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	// test for commit
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	bool result = pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
	if (result)
		return result;
	double value = (double)rand() / RAND_MAX;
	double prob = (double)numberOfLongEdge / (network.size - 20);
	return value <= prob; // Subtract to the degree of a node
}

void SmallworldDeploying::neighborInitialization(Network* network)
{
	unsigned int networkSize = network->nodes.size();
	for (unsigned int i=0; i < networkSize; i++)
	{
		for (unsigned int j = i + 1; j < networkSize; j++)
		{
			if (isNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				network->makeNeighbors(i, j);
			}
		}
	}
}

} /* namespace domain */
