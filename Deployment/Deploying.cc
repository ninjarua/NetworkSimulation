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
	network->nodes->clear();
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

bool Deploying::IsValidDistance(Node node, Node neighbor)
{
	double Xdist, Ydist, dist;
	Xdist = node.posX - neighbor.posX;
	Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	dist = pow((Xdist * Xdist + Ydist * Ydist), 0.5);
	return (dist >= networkTopology->D0);
}

bool Deploying::IsAllDistanceValid(Network network, Node node)
{
	int size = network.nodes->size();
	for (int j = 0; j < size - 1; j = j + 1)
	{
		if (!IsValidDistance(node, *network.nodes->at(j)))
		{
			return false;
		}
	}
	return true;
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
	for (unsigned int i = 0; i < network->nodes->size() - 1; i++)
	{
		for (unsigned int j = i + 1; j < network->nodes->size(); j++)
		{
			if (IsNeighbors(*network, *(*network->nodes)[i], *(*network->nodes)[j]))
			{
				(*network->nodes)[i]->neighbors->push_back((*network->nodes)[j]);
				(*network->nodes)[j]->neighbors->push_back((*network->nodes)[i]);
			}
		}
	}
	CreateInformationOfGraph(network);
}

void Deploying::CreateInformationOfGraph(Network* network)
{
}

bool Deploying::IsNeighbors(Network network, Node node, Node neighbor)
{
	// test for commit
	double Xdist = node.posX - neighbor.posX;
	double Ydist = node.posY - neighbor.posY;
	// distance between a given pair of nodes
	return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

bool isConnectedAreaNumberZero(Node* node)
{
	return node->connectedAreaNumber == 0;
}

bool isConnectedAreaNumberEqual(Node* node, int number)
{
	return node->connectedAreaNumber == number;
}

int Deploying::FindMaximumConnectedArea(Network* network, bool (*pCondition)(Node*))
{
	vector<Node*> checkNodes = Tools::FindAllToVector(*network->nodes, (*pCondition));
	vector<Node*> spreadingNodes = Tools::FindAllToVector(checkNodes, &isConnectedAreaNumberZero);
	int spreadingValue = 0;
	int max = 0;
	while (spreadingNodes.size() > 0)
	{
		spreadingValue++;
		Node* begin = *spreadingNodes.begin();
		ConnectedAreaSpreading(begin, spreadingValue, (*pCondition));
		int count = Tools::RemoveWithBinaryPredicate(spreadingNodes, isConnectedAreaNumberEqual, spreadingValue);
		if (count > max)
			max = count;
	}
	return max;
}



stack<Node*>* Deploying::LookingForNode(list<Node*>* listInput, pCondition nodeCondition)
{
	stack<Node*>* results = new stack<Node*>();
	list<Node*>::iterator it = listInput->begin();
	while(it != listInput->end())
	{
		if (nodeCondition(*it))
		{
			results->push(*it);
		}
	}
	return results;
}

void Deploying::AddingNewNodesWithFilter(stack<Node*>* stack, Node* consideringNode, pCondition nodeCondition, int number,
				bool (*filter)(Node* n1, Node* n2, int number))
{
	list<Node*>::iterator it = consideringNode->neighbors->begin();
	while(it != consideringNode->neighbors->end())
	{
		Node* node = *it;
		if (nodeCondition(node) && filter(node, consideringNode, number))
		{
			stack->push(node);
		}
	}
}


bool Deploying::FilterDisconnectedNodeAndDifferentConnectedAreaNumber(Node* n1, Node* n2, int number)
{
	return n1->connectedAreaNumber != number && n2->disconnectedNodes->find(n1) != n2->disconnectedNodes->end()
			&& n1->disconnectedNodes->find(n2) != n1->disconnectedNodes->end();
}

void Deploying::ConnectedAreaSpreading(Node* seed, int spreadingValue, pCondition nodeCondition)
{
	seed->connectedAreaNumber = spreadingValue;
	stack<Node*>* stackNodes = LookingForNode(seed->neighbors, nodeCondition);
	while (stackNodes->size() != 0)
	{
		Node* node = stackNodes->top();
		stackNodes->pop();
		node->connectedAreaNumber = spreadingValue;
		AddingNewNodesWithFilter(stackNodes, node, nodeCondition, spreadingValue, &FilterDisconnectedNodeAndDifferentConnectedAreaNumber);
	}
}
} /* namespace deployment */
