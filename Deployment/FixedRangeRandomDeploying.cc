/*
 * FixedRangeRandomDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "FixedRangeRandomDeploying.h"

namespace deployment {

FixedRangeRandomDeploying::FixedRangeRandomDeploying() : Deploying() {
	// TODO Auto-generated constructor stub

}

FixedRangeRandomDeploying::~FixedRangeRandomDeploying() {
	// TODO Auto-generated destructor stub
}

bool FixedRangeRandomDeploying::ObtainTopology(Network* network)
{
	Deploying::ObtainTopology(network);
	if ((networkTopology->XTerr < 0) | (networkTopology->YTerr < 0))
	{
		string errorMessage = "Error: values of TERRAIN_DIMENSIONS must be positive";
		//Logger.GetInstance().Debug(errorMessage);
		throw nsException(errorMessage);
	}
	// 1.4 (below) is an arbitrary number chosen to decrease the probability
	// that nodes get closer than D0 to one another.
	if (GetCellLength() < (networkTopology->D0 * 1.4))
	{
		string errorMessage = "Error: on RANDOM topology, density is too high, increase physical terrain";
		//Logger.GetInstance().Debug(errorMessage);
		throw nsException(errorMessage);
	}
	// Node 0 is the sink node that is located in the center of the network
	network->AddNode(new Node(networkTopology->XTerr / 2, networkTopology->YTerr / 2));
	for (int i = 1; i < networkTopology->NumNodes; i++)
	{
		Node* newNode = new Node(GetPosX(i), GetPosY(i));
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
	return (double)rand()/RAND_MAX * networkTopology->XTerr;
}

double FixedRangeRandomDeploying::GetPosY(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * networkTopology->YTerr;
}

double FixedRangeRandomDeploying::GetCellLength()
{
	return sqrt(networkTopology->Area() / networkTopology->NumNodes);
}

} /* namespace protocols */
