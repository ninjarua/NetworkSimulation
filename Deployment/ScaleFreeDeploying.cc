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
	delete topology;
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
		network->makeNeighbors(i, newSize - 1);
	}
}

bool insertToSortedList(list<int>& lstInt, const int& number)
{
	list<int>::iterator right = lstInt.end();
	right--;
	while (right != lstInt.begin() && number < (*right))
	{
		right--;
	}
	if (number == (*right))
		return false;
	else if (right == lstInt.begin() && number < (*lstInt.begin()))
	{
		lstInt.insert(right, number);
	}
	else
	{
		right++;
		lstInt.insert(right, number);
	}
	return true;
}

void ScaleFreeDeploying::attachNewNode(Network* network, int index, unsigned long& totalDegree)
{
	list<int> connectId = list<int>();
	//int count = 0;
	for(int i = 0; i < mEdge; i++)
	{
		int j;
		bool result = false;
		while(!result)
		{
			double p0 = (double)rand() / RAND_MAX;
			double p = 0;
			j = 0;
			for (; p < p0 && j < index; j++)
			{
				p += (double)network->nodes[j]->D / totalDegree;
			}
			if (j <= index)
				result = insertToSortedList(connectId, j - 1);
			else
				result = false;
		}
		//count++;
	}
	list<int>::iterator it = connectId.begin();
	for (; it != connectId.end(); it++)
	{
		network->makeNeighbors(*it, index);
	}
	totalDegree += 2 * mEdge;
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
