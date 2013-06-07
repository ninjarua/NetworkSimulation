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
    ownerNetwork = network;
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

bool Node::isConnectedAreaNumberZero(const Node& node)
{
	return node.connectedAreaNumber == 0;
}

bool Node::isConnectedAreaNumberEqual(const Node& node, int number)
{
	return node.connectedAreaNumber == number;
}

bool Node::isNodeState(const Node& node, const NodeState& state)
{
	return node.state == state;
}

void Node::CreateLists()
{
	neighbors = list<NodePtr>();
	detectedByzantines = set<NodePtr>();
	disconnectedNodes = set<NodePtr>();
}

void Node::Reset()
{
//	neighbors.clear();
//	detectedByzantines.clear();
//	disconnectedNodes.clear();
}

bool operator==(const Node& n1, const Node& n2)
{
	return n1.id == n2.id;
}

bool operator<(const Node& n1, const Node& n2)
{
	return n1.id < n2.id;
}

bool operator>(const Node& n1, const Node& n2)
{
	return n1.id > n2.id;
}

ofstream& operator<<(ofstream& os, const Node& node)
{
	os << node.id << Constants::tab << node.posX
				<< Constants::tab << node.posY;
	list<NodePtr>::const_iterator it = node.neighbors.begin();
	while (it != node.neighbors.end())
	{
		os << Constants::tab << (*it)->id;
		it++;
	}
	os << Constants::endline;
	return os;
}

ostream& operator<<(ostream& os, const Node& node)
{
	os << node.id << Constants::tab << node.posX
				<< Constants::tab << node.posY;
	list<NodePtr>::const_iterator it = node.neighbors.begin();
	while (it != node.neighbors.end())
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
		node.neighbors.push_back(node.ownerNetwork->nodes.at(id));
	}
	return is;
}

string Node::printNodeWithConnectedAreaNumber(const Node& node)
{
	char number[18];
	sprintf(number, "%d: can = %d", node.id, node.connectedAreaNumber);
	string out(number);
	return number;
}

} /* namespace domain */
