/*
 * GridDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "GridDeploying.h"

namespace deployment {

GridDeploying::GridDeploying() {

}

GridDeploying::GridDeploying(int size) : Deploying() {
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

string GridDeploying::GetDeployingName()
{
	return "Grid";
}

bool GridDeploying::ObtainTopology(Network* network)
{
	Deploying::ObtainTopology(network);
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
		NodePtr newNode(new Node(GetPosX(i), GetPosY(i)));
		network->AddNode(newNode);
	}
//	topology->XTerr = topology->Distance * (sqrt(topology->NumNodes) - 1);
//	topology->YTerr = topology->Distance * (sqrt(topology->NumNodes) - 1);
	return true;
}

double GridDeploying::GetPosX(int nodeSequenceId)
{
	int sqrtNumNodes = (int)sqrt(topology->numNodes);
	return (nodeSequenceId % sqrtNumNodes) * topology->range;
}

double GridDeploying::GetPosY(int nodeSequenceId)
{
	int sqrtNumNodes = (int)sqrt(topology->numNodes);
	return (nodeSequenceId / sqrtNumNodes) * topology->range;
}

bool GridDeploying::IsNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

} /* namespace protocols */
