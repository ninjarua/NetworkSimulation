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
	info = new NetworkInfo();
	nodes = new vector<Node*>();
	messages = new vector<Message*>();
	newMessages = new vector<Message*>();
}

Network::~Network() {
	sequenceId = 0;
}

bool Network::noNewMessageInNetwork(Network* network)
{
	return network->newMessages->size() == 0;
}

void Network::CreateEmptyNodes(int n)
{
	if (nodes->size() > 0)
		nodes->erase(nodes->begin(), nodes->end());
	//nodes = new vector<Node*>();
	sequenceId = 0;
	for (int i=0; i<n; i++)
		AddNode(new Node(this));
}

ofstream& operator<<(ofstream& os, const Network& network)
{
	os << network.nodes->size();
	os << Constants::endline;
	for (unsigned int i = 0; i < network.nodes->size(); i++)
		os << (*network.nodes->at(i));
	return os;
}

istream& operator>>(istream& is, Network& network)
{
	string line("");
	getline(is, line);
	network.CreateEmptyNodes(atoi(line.c_str()));

	int i = 0;
	while (!getline(is, line).eof())
	{
		istringstream iss(line);
		iss >> *network.nodes->at(i);
		i++;
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
