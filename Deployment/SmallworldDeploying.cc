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

SmallworldDeploying::SmallworldDeploying(int numberNodes, int xTerr, int yTerr, int range, int noOfShortEdge, int noOfLongEdge)
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

bool SmallworldDeploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	// test for commit
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	bool result = pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
	return result;
}

bool SmallworldDeploying::isLongEdgeNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	double value = (double)rand() / RAND_MAX;
	double prob = (double)numberOfLongEdge / (network.size - numberOfShortEdge);
	return value <= prob; // Subtract to the degree of a node
}

void SmallworldDeploying::neighborInitialization(Network* network)
{
	//unsigned int networkSize = network->nodes.size();
	//vector<vector<unsigned int> > matrix;//(network->size)

//	for (unsigned int i=0; i < network->size; i++)
//	{
//		vector<unsigned int> v_i(network->size);
//		for (unsigned int j=0; j < network->size; j++)
//			v_i[j] = 0;
//		matrix.push_back(v_i);
//	}
	map<unsigned int, vector<unsigned int> > towardList;
	map<unsigned int, vector<unsigned int> > backwardList;

	for (unsigned int i = 0; i < network->size; i++)
	{
		//for (unsigned int j = i + 1; j < networkSize; j++)
		for (unsigned int j = 0; j < network->size; j++)
		{
			NodePtr nodei = network->nodes[i];
			NodePtr nodej = network->nodes[j];
			if (i < j)
			{
				if (isNeighbors(*network, *nodei, *nodej)
					|| isLongEdgeNeighbors(*network, *nodei, *nodej))
				{
					//network->makeNeighbors(i, j);
					//matrix[i][j] = 1;
					towardList[i].push_back(j);
				}
			}
			else if (i > j)// if (isLongEdgeNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				//LinkPtr linkPtr = NetworkTools::GetLinkPtr(network->nodes[i]->links, network->nodes[j]->id);
				if (!Tools::Contain(towardList[j], i)
//						&& !binary_search(backwardList[i].begin(), backwardList[i].end(), j)
						&& isLongEdgeNeighbors(*network, *nodei, *nodej))
				{
					backwardList[i].push_back(j);
				}
			}
		}
	}
	for (unsigned int i = 0; i < network->size; i++)
	{
		vector<unsigned int>::iterator itToward = towardList[i].begin();
		vector<unsigned int>::iterator itBackward = backwardList[i].begin();
		while (itToward != towardList[i].end() && itBackward != backwardList[i].end())
		{
			if ((*itToward) < (*itBackward))
			{
				network->makeNeighbors(i, *itToward);
				itToward++;
			}
			else
			{
				network->makeNeighbors(i, *itBackward);
				itBackward++;
			}
		}
		for (; itToward != towardList[i].end(); itToward++)
			network->makeNeighbors(i, *itToward);
		for (; itBackward != backwardList[i].end(); itBackward++)
			network->makeNeighbors(*itBackward, i);
	}
}

} /* namespace domain */
