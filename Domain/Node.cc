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
    D = 0;
}

Node::Node(Network* network) {
    // Constructor
	Initialize();
    posX = 0;
    posY = 0;
    CreateLists();
    ownerNetwork = network;
    D = 0;
}

Node::~Node() {
	Tools::EraseAll(links);
	//neighbors.clear();
}

void Node::Initialize()
{
    id = 0;
    state = Sane;
    connectedAreaNumber = 0;
    D = 0;
}

Node::Node(double x, double y)
{
	Initialize();
    posX = x;
    posY = y;
    CreateLists();
    D = 0;
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
	//neighbors = list<NodePtr>();
	links = vector<LinkPtr>();
	//detectedByzantines = set<NodePtr>();
	//disconnectedNodes = set<NodePtr>();
}

void Node::Reset()
{
    state = Sane;
    connectedAreaNumber = 0;
    vector<LinkPtr>::iterator it = links.begin();
    for(; it != links.end(); it++)
    	(*it)->state = Active;
}

int Node::addNeighbor(LinkPtr link)
{
	//neighbors.push_back(node);
	links.push_back(link);
	D++;
	return D;
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
	vector<LinkPtr>::const_iterator it = node.links.begin();
	while (it != node.links.end())
	{
		os << Constants::tab << (*it)->dest->id;
		it++;
	}
	os << Constants::endline;
	return os;
}

ostream& operator<<(ostream& os, const Node& node)
{
	os << node.id << Constants::tab << node.posX
				<< Constants::tab << node.posY;
	vector<LinkPtr>::const_iterator it = node.links.begin();
	while (it != node.links.end())
	{
		os << Constants::tab << (*it)->dest->id;
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
		//node.ownerNetwork->makeNeighbors(node.id, id);
		//new Link(&node, node.ownerNetwork->nodes[id]);
		node.addNeighbor(new Link(&node, node.ownerNetwork->nodes[id]));
		//node.neighbors.push_back(node.ownerNetwork->nodes.at(id));
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
