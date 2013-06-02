/*
 * Deploying.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Deploying.h"

namespace deployment {
Deploying::Deploying() {
	//networkTopology = new Topology();
}

Deploying::~Deploying() {

}

bool Deploying::ObtainTopology(Network* network)
{
	network->sequenceId = 0;
	network->nodes.clear();
	return true;
}

double Deploying::GetPosX(int nodeSequenceId)
{
	return 0;
}

double Deploying::GetPosY(int nodeSequenceId)
{
	return 0;
}

double Deploying::GetCellLength()
{
	return 0;
}

bool Deploying::IsValidDistance(const Node& node, const Node& neighbor)
{
	double Xdist, Ydist, dist;
	Xdist = node.posX - neighbor.posX;
	Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	dist = pow((Xdist * Xdist + Ydist * Ydist), 0.5);
	return (dist >= networkTopology.D0);
}

bool Deploying::IsAllDistanceValid(const Network& network, const Node& node)
{
	int size = network.nodes.size();
	for (int j = 0; j < size - 1; j = j + 1)
	{
		if (!IsValidDistance(node, *network.nodes.at(j)))
		{
			return false;
		}
	}
	return true;
}

string Deploying::GetDeployingName()
{
	return "General";
}

bool Deploying::RunDeploy(Network* network)
{
	if (ObtainTopology(network))
	{
		NeighborInitialization(network);
		return true;
	}
	return false;
}

void Deploying::NeighborInitialization(Network* network)
{
	for (int i = 0; i < (int)(network->nodes.size() - 1); i++)
	{
		for (unsigned int j = i + 1; j < network->nodes.size(); j++)
		{
			if (IsNeighbors(*network, *network->nodes[i], *network->nodes[j]))
			{
				(network->nodes[i])->neighbors.push_back(network->nodes[j]);
				(network->nodes[j])->neighbors.push_back(network->nodes[i]);
			}
		}
	}
	CreateInformationOfGraph(network);
}

void Deploying::CreateInformationOfGraph(Network* network)
{

}

bool Deploying::IsNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	// test for commit
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

}
/* namespace deployment */
