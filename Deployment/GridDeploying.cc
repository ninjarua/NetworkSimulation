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

GridDeploying::~GridDeploying() {

}

bool GridDeploying::ObtainTopology(Network* network)
{
	Deploying::ObtainTopology(network);
	if (networkTopology->Distance < networkTopology->D0)
	{
		//Logger.GetInstance().Debug("Error: value of GRID_UNIT must be greater than D0");
		return false;
	}
	int sqrtNumNodes = (int)sqrt(networkTopology->NumNodes);
	if (sqrtNumNodes != sqrt(networkTopology->NumNodes))
	{
		//Logger.GetInstance().Debug("Error: on GRID topology, NUMBER_OF_NODES should be the square of a natural number");
		return false;
	}
	for (int i = 0; i < networkTopology->NumNodes; i++)
	{
		network->AddNode(new Node(GetPosX(i), GetPosY(i)));
	}
	networkTopology->XTerr = networkTopology->Distance * (sqrt(networkTopology->NumNodes) - 1);
	networkTopology->YTerr = networkTopology->Distance * (sqrt(networkTopology->NumNodes) - 1);
	return true;
}

double GridDeploying::GetPosX(int nodeSequenceId)
{
	int sqrtNumNodes = (int)sqrt(networkTopology->NumNodes);
	return (nodeSequenceId % sqrtNumNodes) * networkTopology->Distance;
}

double GridDeploying::GetPosY(int nodeSequenceId)
{
	int sqrtNumNodes = (int)sqrt(networkTopology->NumNodes);
	return (nodeSequenceId / sqrtNumNodes) * networkTopology->Distance;
}

bool GridDeploying::IsNeighbors(Network network, Node node, Node neighbor)
{
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

} /* namespace protocols */
