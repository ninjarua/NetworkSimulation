/*
 * ScaleFreeDeploying.cc
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#include "ScaleFreeDeploying.h"
#include "nsException.h"

namespace deployment {

ScaleFreeDeploying::ScaleFreeDeploying() : Deploying(){
	// TODO Auto-generated constructor stub

}

ScaleFreeDeploying::ScaleFreeDeploying(int m0, int m, int N)
{
	topology->numNodes = N;
	topology->range = 1;
	topology->xTerr = 100;
	topology->yTerr = 100;
	size0 = m0;
	mEdge = m;
	size = N;
}

ScaleFreeDeploying::~ScaleFreeDeploying() {
	// TODO Auto-generated destructor stub
}

string ScaleFreeDeploying::getDeployingName()
{
	return "ScaleFree";
}

bool ScaleFreeDeploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
	return true;
}

void ScaleFreeDeploying::increaseClique(Network* network, int newSize)
{
	if (newSize == 0)
		return;
	for(int i=0; i < newSize - 1; i++)
	{
		(network->nodes[i])->addNeighbor(network->nodes[newSize - 1]); // neighbors.push_back(network->nodes[newSize]);
		(network->nodes[newSize - 1])->addNeighbor(network->nodes[i]);
	}
}

void ScaleFreeDeploying::attachNewNode(Network* network, int index, unsigned long& totalDegree)
{
	vector<int> connectId = vector<int>();
	for(int i = 0; i < mEdge; i++)
	{
		double p0 = (double)rand() / RAND_MAX;
		double p = 0;
		int j = 0;
		for (; p < p0 && j < index; j++)
		{
			p += (double)network->nodes[j]->D / totalDegree;
		}
		if (j < index)
			connectId.push_back(j);
	}
	int addingSize = connectId.size();
	for (int i = 0; i < addingSize; i++)
	{
		network->nodes[connectId[i]]->addNeighbor(network->nodes[index]);
		network->nodes[index]->addNeighbor(network->nodes[connectId[i]]);
	}
	totalDegree += 2 * addingSize;
	connectId.clear();
}

void ScaleFreeDeploying::neighborInitialization(Network* network)
{
	for (int i = 1; i <= size0; i++)
		increaseClique(network, i);
	unsigned long totalDegree = size0 * (size0 - 1);
	for (int i = size0; i < size; i++)
	{
		attachNewNode(network, i, totalDegree);
	}
}

double ScaleFreeDeploying::getPosX(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->xTerr;
}

double ScaleFreeDeploying::getPosY(int nodeSequenceId)
{
	return (double)rand()/RAND_MAX * topology->yTerr;
}

bool ScaleFreeDeploying::obtainTopology(Network* network)
{
	Deploying::obtainTopology(network);
	for (int i = 0; i < topology->numNodes; i++)
	{
		NodePtr newNode(new Node(getPosX(i), getPosY(i)));
		network->addNode(newNode);
	}
	return true;
}
} /* namespace deployment */
