/*
 * Network.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"
namespace domain {

Network::Network() {
	sequenceId = 0;
	currentTimeSlot = 0;
	info = NetworkInfo();
	nodes = vector<Node*>();
	messages = vector<Message*>();
	newMessages = vector<Message*>();
}

Network::~Network() {
}

void Network::CreateEmptyNodes(int n)
{
	info.listDetectors.clear();
	info.listInfectedNodes.clear();
	nodes.erase(nodes.begin(), nodes.end());
	messages.erase(messages.begin(), messages.end());
	newMessages.erase(newMessages.begin(), newMessages.end());
	//nodes = new vector<Node*>();
	sequenceId = 0;
	for (int i=0; i<n; i++)
	{
		//Node newNode = Node();
		AddNode(new Node());
	}
}

ofstream& operator<<(ofstream& os, const Network& network)
{
	os << network.nodes.size();
	os << Constants::endline;
	for (unsigned int i = 0; i < network.nodes.size(); i++)
		os << network.nodes.at(i);
	return os;
}

istream& operator>>(istream& is, Network& network)
{
	string line("");
	getline(is, line);
	network.CreateEmptyNodes(atoi(line.c_str()));

	int i = 0;
	//int size = network.nodes.size();
	while (!getline(is, line).eof())
	{
		istringstream iss(line);
		iss >> *network.nodes.at(i);
		i++;
	}
	return is;
}

void Network::AddNode(Node* node)
{
	node->id = sequenceId++;
	node->ownerNetwork = this;
	nodes.push_back(node);
	//return node;
}

bool Network::noNewMessageInNetwork(const Network& network)
{
	return network.newMessages.size() == 0;
}

stack<Node*> Network::LookingForNode(const list<Node*>& listInput, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	stack<Node*> results = stack<Node*>();
	list<Node*>::const_iterator it = listInput.begin();
	for (; it != listInput.end(); it++)
	{
		if (nodeCondition(*(*it), state))
		{
			results.push(*it);
		}
	}
	return results;
}

void Network::AddingNewNodesWithFilter(stack<Node*>& stack, Node* consideringNode, bool (*nodeCondition)(const Node&, const NodeState&),
				const NodeState& state, int number, bool (*filter)(Node* n1, Node* n2, int number))
{
	list<Node*>::const_iterator it = consideringNode->neighbors.begin();
	for(; it != consideringNode->neighbors.end(); it++)
	{
		if (nodeCondition(*(*it), state) && filter(*it, consideringNode, number))
		{
			stack.push(*it);
		}
	}
}


bool Network::FilterDisconnectedNodeAndDifferentConnectedAreaNumber(Node* n1, Node* n2, int number)
{
	return n1->connectedAreaNumber != number && n2->disconnectedNodes.find(n1) != n2->disconnectedNodes.end()
			&& n1->disconnectedNodes.find(n2) != n1->disconnectedNodes.end();
}

void Network::ConnectedAreaSpreading(Node* seed, int spreadingValue, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	seed->connectedAreaNumber = spreadingValue;
	stack<Node*> stackNodes = LookingForNode(seed->neighbors, nodeCondition, state);
	while (stackNodes.size() != 0)
	{
		Node* node = stackNodes.top();
		stackNodes.pop();
		node->connectedAreaNumber = spreadingValue;
		AddingNewNodesWithFilter(stackNodes, node, nodeCondition, state, spreadingValue, &FilterDisconnectedNodeAndDifferentConnectedAreaNumber);
	}
}

int Network::FindMaximumConnectedArea(Network* network, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	vector<Node*> checkNodes;
	vector<Node*> spreadingNodes;
	Tools::FindAllToVector(network->nodes, checkNodes, (*nodeCondition), state);
	int checkCount = checkNodes.size();
	Tools::FindAllToVector(checkNodes, spreadingNodes, &Node::isConnectedAreaNumberZero);
	int spreadCount = spreadingNodes.size();
	int spreadingValue = 0;
	int max = 0;
	while (spreadingNodes.size() > 0)
	{
		spreadingValue++;
		Node* begin = *spreadingNodes.begin();
		ConnectedAreaSpreading(begin, spreadingValue, (*nodeCondition), state);
		int count = Tools::DetachWithPredicate(spreadingNodes, &Node::isConnectedAreaNumberEqual, spreadingValue);
		if (count > max)
			max = count;
	}
//	checkNodes.clear();
//	delete checkNodes;
//	spreadingNodes.clear();
//	delete spreadingNodes;
	return max;
}

}
