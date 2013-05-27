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
	os << network.nodes->size();
	for (int i = 0; i < network.nodes->size(); i++)
		os << network.nodes->at(i);
	return os;
}

istream& operator>>(istream& is, const Network& network)
{
	is >> network;
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
