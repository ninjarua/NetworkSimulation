/*
 * SmallworldDeploying.cc
 *
 *  Created on: Jul 26, 2013
 *      Author: thanhnd
 */

#include "SmallworldDeploying.h"
#include "NetworkTools.h"
#include <algorithm>

namespace deployment {

SmallworldDeploying::SmallworldDeploying() : FixedRangeRandomDeploying()
{
	topology->range = 1;
	numberOfLongEdge = 0;
	numberOfShortEdge = 0;
}

SmallworldDeploying::SmallworldDeploying(int numberNodes, int xTerr, int yTerr, int range, int noOfShortEdge, double noOfLongEdge)
	: FixedRangeRandomDeploying(numberNodes, xTerr, yTerr, range)
{
	numberOfLongEdge = noOfLongEdge;
	numberOfShortEdge = noOfShortEdge;
}

SmallworldDeploying::~SmallworldDeploying() {
	delete topology;
}

string SmallworldDeploying::getDeployingName()
{
	return "Smallworld";
}

bool SmallworldDeploying::isLongEdgeNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	double value = (double)rand() / RAND_MAX;
	double prob = (double)numberOfLongEdge / (network.size - numberOfShortEdge);
	return value <= prob; // Subtract to the degree of a node
}

void SmallworldDeploying::neighborInitialization(Network* network)
{
	map<unsigned long, vector<unsigned long> > towardList;
	map<unsigned long, vector<unsigned long> > backwardList;

	for (unsigned long i = 0; i < network->size; i++)
	{
		//for (unsigned int j = i + 1; j < networkSize; j++)
		for (unsigned long j = 0; j < network->size; j++)
		{
			NodePtr nodei = network->nodes[i];
			NodePtr nodej = network->nodes[j];
			if (i < j)
			{
				if (isNeighbors(*network, nodei, nodej)
					|| isLongEdgeNeighbors(*network, *nodei, *nodej))
				{
					towardList[i].push_back(j);
				}
			}
			else if (i > j)// if (isLongEdgeNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				if (!Tools::Contain(towardList[j], i)
						&& isLongEdgeNeighbors(*network, *nodei, *nodej))
				{
					backwardList[i].push_back(j);
				}
			}
		}
//		cout << i << endl;
	}
	for (unsigned long i = 0; i < network->size; i++)
	{
		vector<unsigned long>::iterator itToward = towardList[i].begin();
		vector<unsigned long>::iterator itBackward = backwardList[i].begin();
		for (; itBackward != backwardList[i].end(); itBackward++)
			network->makeNeighbors(*itBackward, i);
		for (; itToward != towardList[i].end(); itToward++)
			network->makeNeighbors(i, *itToward);
	}
}

} /* namespace domain */
