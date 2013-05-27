/*
 * Node.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Node.h"

namespace domain {
Node::Node() {
    // Constructor
	Initialize();
    posX = 0;
    posY = 0;
    CreateLists();
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

void Node::CreateLists()
{
	neighbors = new list<Node*>();
	detectedByzantines = new set<Node*>();
	disconnectedNodes = new set<Node*>();
}

void Reset(Node& node)
{
	node.neighbors->clear();
	node.detectedByzantines->clear();
	node.disconnectedNodes->clear();
}

ostream& operator<<(ostream& os, const Node& node)
{
	//os << node.id << Constants::tab << node.posX
	//			<< Constants::tab << node.posY << Constants::tab;
	list<Node*>::iterator it = node.neighbors->begin();
	while (it != node.neighbors->end())
	{
		//os << it->id << Constants::tab;
	}
	os << Constants::endline;
	return os;
}

istringstream& operator>>(istringstream& is, Node& node)
{
	//Node n = Node();
	Reset(node);
	is >> node.id;
	is >> node.posX;
	is >> node.posY;
	int id;
	while (is >> id)
	{
		//node.neighbors->push_back(node.OwnerNetwork->nodes->at(id));
	}
	return is;
}

} /* namespace domain */
