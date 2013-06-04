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
	nodes = vector<NodePtr>();
	messages = list<Message*>();
	newMessages = list<Message*>();
}

Network::~Network() {
}

void Network::CreateEmptyNodes(int n)
{
	info.listDetectors.clear();
	info.listInfectedNodes.clear();
	Tools::EraseAll(nodes);
	Tools::EraseAll(messages);
	Tools::EraseAll(newMessages);
	//nodes = new vector<Node*>();
	sequenceId = 0;
	for (int i=0; i<n; i++)
	{
		NodePtr newNode(new Node());
		AddNode(newNode);
	}
}

ofstream& operator<<(ofstream& os, const Network& network)
{
	os << network.nodes.size();
	os << Constants::endline;
	vector<NodePtr>::const_iterator it = network.nodes.begin();
	for (; it != network.nodes.end(); it++)
		os << *(*it);
	return os;
}

istream& operator>>(istream& is, Network& network)
{
	string line("");
	getline(is, line);
	network.CreateEmptyNodes(atoi(line.c_str()));

	vector<NodePtr>::const_iterator it = network.nodes.begin();
	while (!getline(is, line).eof())
	{
		istringstream iss(line);
		iss >> *(*it);
		it++;
	}
	return is;
}

void Network::AddNode(NodePtr node)
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

stack<NodePtr> Network::LookingForNode(const list<NodePtr>& listInput, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	stack<NodePtr> results = stack<NodePtr>();
	list<NodePtr>::const_iterator it = listInput.begin();
	for (; it != listInput.end(); it++)
	{
		if (nodeCondition(*(*it), state))
		{
			results.push(*it);
		}
	}
	return results;
}

void Network::AddingNewNodesWithFilter(stack<NodePtr>& stack, NodePtr consideringNode, bool (*nodeCondition)(const Node&, const NodeState&),
				const NodeState& state, int number, bool (*filter)(NodePtr n1, NodePtr n2, int number))
{
	list<NodePtr>::const_iterator it = consideringNode->neighbors.begin();
	string prefix = "Next according to: ";
	for(; it != consideringNode->neighbors.end(); it++)
	{
		bool isSameState = nodeCondition(*(*it), state);
		if (isSameState && filter(*it, consideringNode, number))
		{
//			Logger::Write(*(*it), &DebugString, prefix, "debug.out", ofstream::out|ofstream::app);
			stack.push(*it);
		}
	}
}

bool Network::FilterDisconnectedNodeAndDifferentConnectedAreaNumber(NodePtr n1, NodePtr n2, int number)
{
	return n1->connectedAreaNumber != number && n2->disconnectedNodes.find(n1) == n2->disconnectedNodes.end()
			&& n1->disconnectedNodes.find(n2) == n1->disconnectedNodes.end();
}

string Network::DebugString(const Node& node, string original)
{
	string out(Node::printNodeWithConnectedAreaNumber(node));
	out = original + out + "\n";
	return out;
}

void Network::ConnectedAreaSpreading(NodePtr seed, int spreadingValue, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	seed->connectedAreaNumber = spreadingValue;
	stack<NodePtr> stackNodes = LookingForNode(seed->neighbors, nodeCondition, state);
	int size = stackNodes.size();
	while (size > 0)
	{
		NodePtr node = stackNodes.top();
		stackNodes.pop();
		node->connectedAreaNumber = spreadingValue;
//		Logger::Write(*node, &DebugString, "Seed spread: ", "debug.out", ofstream::out|ofstream::app);
		AddingNewNodesWithFilter(stackNodes, node, nodeCondition, state, spreadingValue, &FilterDisconnectedNodeAndDifferentConnectedAreaNumber);
		size = stackNodes.size();
	}
}

int Network::FindMaximumConnectedArea(Network* network, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	list<NodePtr> checkNodes;
	list<NodePtr> spreadingNodes;
	Tools::FindAllToVector(network->nodes, checkNodes, (*nodeCondition), state);
	Tools::FindAllToVector(checkNodes, spreadingNodes, &Node::isConnectedAreaNumberZero);
	int spreadingValue = 0;
	int max = 0;
	while (spreadingNodes.size() > 0)
	{
		spreadingValue++;
		NodePtr begin(*spreadingNodes.begin());
		ConnectedAreaSpreading(begin, spreadingValue, (*nodeCondition), state);
		int count = Tools::DetachWithPredicate(spreadingNodes, &Node::isConnectedAreaNumberEqual, spreadingValue);
		if (count > max)
			max = count;
	}
	return max;
}

}
