/*
 * GridDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "GridDeploying.h"

namespace deployment {

GridDeploying::GridDeploying() : Deploying() {

}

GridDeploying::GridDeploying(int size) : Deploying() {
	topology->numNodes = size;
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
		//Logger.GetInstance().Debug("Error: value of GRID_UNIT must be greater than D0");
		return false;
	}
//	int sqrtNumNodes = (int)sqrt(topology->NumNodes);
//	if (sqrtNumNodes != sqrt(topology->NumNodes))
//	{
//		//Logger.GetInstance().Debug("Error: on GRID topology, NUMBER_OF_NODES should be the square of a natural number");
//		return false;
//	}
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node(getPosX(i), getPosY(i)));
		network->addNode(newNode);
	}
//	topology->XTerr = topology->Distance * (sqrt(topology->NumNodes) - 1);
//	topology->YTerr = topology->Distance * (sqrt(topology->NumNodes) - 1);
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

bool GridDeploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

} /* namespace protocols */
