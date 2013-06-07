/*
 * FixedRangeRandomDeploying.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "FixedRangeRandomDeploying.h"

namespace deployment {

FixedRangeRandomDeploying::FixedRangeRandomDeploying()
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
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node(GetPosX(i), GetPosY(i)));
		network->AddNode(newNode);
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
