/*
 * Node.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"

namespace domain {
Node::Node() {
    // Constructor
	Initialize();
    posX = 0;
    posY = 0;
    CreateLists();
}

Node::Node(Network* network) {
    // Constructor
	Initialize();
    posX = 0;
    posY = 0;
    CreateLists();
    OwnerNetwork = network;
}

Node::~Node() {
}

void Node::Initialize()
{
    id = 0;
    state = Sane;
    connectedAreaNumber = 0;
}

Node::Node(double x, double y)
{
	Initialize();
    posX = x;
    posY = y;
    CreateLists();
}

bool Node::isConnectedAreaNumberZero(Node* node)
{
	return node->connectedAreaNumber == 0;
}

bool Node::isConnectedAreaNumberEqual(Node* node, int number)
{
	return node->connectedAreaNumber == number;
}

bool Node::isNodeState(Node* node, NodeState state)
{
	return node->state == state;
}

void Node::CreateLists()
{
	neighbors = new list<Node*>();
	detectedByzantines = new set<Node*>();
	disconnectedNodes = new set<Node*>();
}

void Node::Reset()
{
	neighbors->clear();
	detectedByzantines->clear();
	disconnectedNodes->clear();
}

ofstream& operator<<(ofstream& os, const Node& node)
{
	os << node.id << Constants::tab << node.posX
				<< Constants::tab << node.posY;
	list<Node*>::iterator it = node.neighbors->begin();
	while (it != node.neighbors->end())
	{
		os << Constants::tab << (*it)->id;
		it++;
	}
	os << Constants::endline;
	return os;
}

istringstream& operator>>(istringstream& is, Node& node)
{
	node.Reset();
	is >> node.id >> node.posX >> node.posY;
	int id;
	while (is >> id)
	{
		node.neighbors->push_back(node.OwnerNetwork->nodes->at(id));
	}
	return is;
}

} /* namespace domain */
