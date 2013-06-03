/*
 * FixedRangeRandomDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "FixedRangeRandomDeploying.h"

namespace deployment {

FixedRangeRandomDeploying::FixedRangeRandomDeploying(int numberNodes, int xTerr, int yTerr, int range) : Deploying() {
	topology->numNodes = numberNodes;
	topology->xTerr = xTerr;
	topology->yTerr = yTerr;
	topology->range = range;
	topology->d0 = 1;
}

FixedRangeRandomDeploying::~FixedRangeRandomDeploying() {
	// TODO Auto-generated destructor stub
}

string FixedRangeRandomDeploying::GetDeployingName()
{
	return "FixedRange";
}

bool FixedRangeRandomDeploying::ObtainTopology(Network* network)
{
	Deploying::ObtainTopology(network);
	if ((topology->xTerr < 0) | (topology->yTerr < 0))
	{
		string errorMessage = "Error: values of TERRAIN_DIMENSIONS must be positive";
		//Logger.GetInstance().Debug(errorMessage);
		throw nsException(errorMessage);
	}
	// 1.4 (below) is an arbitrary number chosen to decrease the probability
	// that nodes get closer than D0 to one another.
	if (GetCellLength() < (topology->d0 * 1.4))
	{
		string errorMessage = "Error: on RANDOM topology, density is too high, increase physical terrain";
		//Logger.GetInstance().Debug(errorMessage);
		throw nsException(errorMessage);
	}
	// Node 0 is the sink node that is located in the center of the network
	//Node node = Node(networkTopology.XTerr / 2, networkTopology.YTerr / 2);
	NodePtr firstNode(new Node(topology->xTerr / 2, topology->yTerr / 2));
	network->AddNode(firstNode);
	for (int i = 1; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node(GetPosX(i), GetPosY(i)));
		network->AddNode(newNode);
		while (!IsAllDistanceValid(*network, *newNode))
		{
			newNode->posX = GetPosX(i);
			newNode->posY = GetPosY(i);
		}
	}
	return true;
}

double FixedRangeRandomDeploying::GetPosX(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->xTerr;
}

double FixedRangeRandomDeploying::GetPosY(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->yTerr;
}

double FixedRangeRandomDeploying::GetCellLength()
{
	return sqrt(topology->Area() / topology->numNodes);
}

} /* namespace protocols */
