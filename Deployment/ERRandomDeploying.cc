/*
 * ERRandomDeploying.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "ERRandomDeploying.h"

namespace deployment {

ERRandomDeploying::ERRandomDeploying() {
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

bool ERRandomDeploying::IsNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	return ((double)rand() / RAND_MAX) < connectedProbability;
}

string ERRandomDeploying::ERRandomDeploying::GetDeployingName()
{
	return "Erdos_Renyi";
}

double ERRandomDeploying::GetPosX(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->xTerr;
}

double ERRandomDeploying::GetPosY(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->yTerr;
}

bool ERRandomDeploying::ObtainTopology(Network* network)
{
	Deploying::ObtainTopology(network);
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node(GetPosX(i), GetPosY(i)));
		network->AddNode(newNode);
	}
	return true;
}

}
