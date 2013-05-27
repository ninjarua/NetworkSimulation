/*
 * Network.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"
namespace domain {

Network::Network() {
	currentTimeSlot = 0;
	nodes = new vector<Node*>();
	messages = new vector<Message*>();
	newMessages = new vector<Message*>();
}

Network::~Network() {
	sequenceId = 0;
}

ostream& operator<<(ostream& os, const Network& network)
{
	os << network.nodes->size() << Constants::endline;
	for (int i = 0; i < network.nodes->size(); i++)
		os << network.nodes->at(i);
	return os;
}

void Network::CreateEmptyNodes(int n)
{
	delete []nodes;
	delete nodes;
	nodes = new vector<Node*>();
	for(int i = 0; i<n; i++)
	{
		nodes->push_back(new Node());
	}
}

istream& operator>>(istream& is, const Network& network)
{
//	ifstream fs = (istream)is;
	string line = "";
	getline(is, line);
	int n = atoi(line.c_str());

	while (!is.eof())
	{
		istream li = basic_istream(line);
		li >> network.nodes[0];
	}
	return is;
}

Node* Network::AddNode(Node* node)
{
	node->id = sequenceId++;
	nodes->push_back(node);
	node->OwnerNetwork = this;
	return node;
}

}
