/*
 * Deploying.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Deploying.h"

namespace deployment {
Deploying::Deploying() {
	topology = new Topology();
	using2HopInfo = false;
}

Deploying::~Deploying() {

}

bool Deploying::obtainTopology(Network* network)
{
	network->Reset();
	network->size = topology->numNodes;
	return true;
}

double Deploying::getPosX(int nodeSequenceId)
{
	return 0;
}

double Deploying::getPosY(int nodeSequenceId)
{
	return 0;
}

double Deploying::getCellLength()
{
	return 0;
}

string Deploying::getDeployingName()
{
	return "General";
}

bool Deploying::runDeploy(Network* network)
{
	if (obtainTopology(network))
	{
		neighborInitialization(network);
		if (using2HopInfo)
			network->createAdvancedInformation();
		return true;
	}
	return false;
}

void Deploying::neighborInitialization(Network* network)
{
//	map<long, NodePtr>::iterator iti = network->nodes.begin();
//	for (; iti != network->nodes.end(); iti++)
//	{
//		map<long, NodePtr>::iterator itj = iti++;
//		iti--;
//		if (itj == network->nodes.end())
//			continue;
//		for (; itj != network->nodes.end(); itj++)
//		{
//			if (isNeighbors(*network, iti->second, itj->second))
//			{
//				network->makeNeighbors(iti->second, itj->second);
//			}
//		}
//	}
	unsigned int nSize = network->nodes.size();
	for (unsigned int i = 0; i < nSize - 1; i++)
	{
		for (unsigned int j = i + 1; j < network->nodes.size(); j++)
		{
			if (isNeighbors(*network, network->nodes[i], network->nodes[j]))
			{
				network->makeNeighbors(i, j);
			}
		}
	}
}

bool Deploying::isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor)
{
	GeneratedNode* gnode = dynamic_cast<GeneratedNode*>(node);
	GeneratedNode* gnb = dynamic_cast<GeneratedNode*>(neighbor);
	double Xdist = gnode->posX - gnb->posX;
	double Ydist = gnode->posY - gnb->posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

}
/* namespace deployment */
