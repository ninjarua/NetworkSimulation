/*
 * SmallworldDeploying.cc
 *
 *  Created on: Jul 26, 2013
 *      Author: thanhnd
 */

#include "SmallworldDeploying.h"
#include "NetworkTools.h"

namespace deployment {

SmallworldDeploying::SmallworldDeploying() : FixedRangeRandomDeploying()
{
	topology->range = 1;
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
	vector<vector<unsigned int> > matrix;//(network->size)

	for (unsigned int i=0; i < network->size; i++)
	{
		vector<unsigned int> v_i(network->size);
		for (unsigned int j=0; j < network->size; j++)
			v_i[j] = 0;
		matrix.push_back(v_i);
	}
	for (unsigned int i=0; i < network->size; i++)
	{
		//for (unsigned int j = i + 1; j < networkSize; j++)
		for (unsigned int j = 0; j < network->size; j++)
		{
			if (isNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				if (i < j)
				{
					//network->makeNeighbors(i, j);
					matrix[i][j] = 1;
				}
			}
			else// if (isLongEdgeNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				//LinkPtr linkPtr = NetworkTools::GetLinkPtr(network->nodes[i]->links, network->nodes[j]->id);
				if (matrix[i][j] == 0 && matrix[j][i] == 0 &&
					isLongEdgeNeighbors(*network, *network->nodes[i], *network->nodes[j]))
				{
					//network->makeNeighbors(i, j);
					if (i < j)
						matrix[i][j] = 1;
					else
						matrix[j][i] = 1;
				}
			}
		}
	}
	for (unsigned int i = 0; i < network->size; i++)
	{
		for (unsigned int j = i + 1; j < network->size; j++)
			if (matrix[i][j] == 1)
				network->makeNeighbors(i, j);
//		list<unsigned int>::iterator ijIt = ijEdges[i].begin();
//		list<unsigned int>::iterator jiIt = jiEdges[i].begin();
//		while (ijIt != ijEdges[i].end() || jiIt != jiEdges[i].end())
//		{
//			if (jiIt == jiEdges[i].end() || *ijIt < *jiIt)
//			{
//				network->makeNeighbors(i, *ijIt);
//				ijIt++;
//			}
//			else if (ijIt == ijEdges[i].end() || *ijIt > *jiIt)
//			{
//				network->makeNeighbors(i, *jiIt);
//				jiIt++;
//			}
//		}
	}
}

} /* namespace domain */
