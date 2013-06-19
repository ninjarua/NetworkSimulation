/*
 * Network.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"
#include "Link.h"
namespace domain {

Network::Network() {
	sequenceId = 0;
	currentTimeSlot = 0;
	messageCount = 0;
	info = NetworkInfo();
	nodes = vector<NodePtr>();
	hasTopology = false;
	messages = list<Message*>();
}

Network::~Network() {
}

void Network::createEmptyNodes(int n)
{
	messageCount = 0;
	Tools::EraseAll(nodes);
	Tools::EraseAll(messages);
	sequenceId = 0;
	for (int i=0; i<n; i++)
	{
		NodePtr newNode(new Node());
		addNode(newNode);
	}
}

void Network::makeNeighbors(int id1, int id2)
{
	//Link* link = new Link(nodes[id1], nodes[id2]);
	nodes[id1]->addNeighbor(new Link(nodes[id1], nodes[id2]));
	nodes[id2]->addNeighbor(new Link(nodes[id2], nodes[id1]));
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
	network.createEmptyNodes(atoi(line.c_str()));

	vector<NodePtr>::const_iterator it = network.nodes.begin();
	while (!getline(is, line).eof())
	{
		istringstream iss(line);
		iss >> *(*it);
		it++;
	}
	return is;
}

void Network::addNode(NodePtr node)
{
	node->id = sequenceId++;
	node->ownerNetwork = this;
	nodes.push_back(node);
	//return node;
}

bool Network::noNewMessageInNetwork(const Network& network)
{
	return (network.messageCount == 0);
}

stack<NodePtr> Network::LookingForNode(const vector<LinkPtr>& links, bool (*nodeCondition)(const Node&, const NodeState&),
				const NodeState& state, int settingNumber)
{
	stack<NodePtr> results = stack<NodePtr>();
	vector<LinkPtr>::const_iterator it = links.begin();
	for (; it != links.end(); it++)
	{
		if (nodeCondition(*(*it)->dest, state))
		{
			results.push((*it)->dest);
			(*it)->dest->connectedAreaNumber = settingNumber;
		}
	}
	return results;
}

void Network::AddingNewNodesWithFilter(stack<NodePtr>& stack, NodePtr consideringNode, bool (*nodeCondition)(const Node&, const NodeState&),
				const NodeState& state, int number, bool (*filter)(NodePtr, NodePtr, int))
{
	vector<LinkPtr>::const_iterator it = consideringNode->links.begin();
	string prefix = "Next according to: ";
	for(; it != consideringNode->links.end(); it++)
	{
		bool isSameState = nodeCondition(*(*it)->dest, state);
		// Check to take neighbors which has same state, connectedAreaNumber=0
		// and is not disconnected node with considering node
		if (isSameState && filter((*it)->dest, consideringNode, number))
		{
//			Logger::Write(*(*it), &DebugString, prefix, "debug.out", ofstream::out|ofstream::app);
			stack.push((*it)->dest);
			(*it)->dest->connectedAreaNumber = number; // Adding value for the new node in stack so that we don't add again.
		}
	}
}

bool Network::FilterDisconnectedNodeAndDifferentConnectedAreaNumber(NodePtr n1, NodePtr n2, int number)
{
	return n1->connectedAreaNumber != number;// && n2->links[n1->id]->state != Cut
			//&& n1->links[n2->id]->state != Cut;
}

string Network::DebugString(const Node& node, string original)
{
	string out(Node::printNodeWithConnectedAreaNumber(node));
	out = original + out + "\n";
	return out;
}

// Spread a connected value via neighbors list in every node to find the connected area with a given node
// Put into stack the neighbors of seed.
// For each node in stack find all neighbors that have connectedNumberArea = 0 and not in detect list of that node.
int Network::ConnectedAreaSpreading(NodePtr seed, int spreadingValue,
		bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	int count = 0;
	seed->connectedAreaNumber = spreadingValue;
	stack<NodePtr> stackNodes = LookingForNode(seed->links, nodeCondition, state, spreadingValue);
	int size = stackNodes.size();
	while (size > 0)
	{
		NodePtr node = stackNodes.top();
		stackNodes.pop();
		count++;
//		Logger::Write(*node, &DebugString, "Seed spread: ", "debug.out", ofstream::out|ofstream::app);
		AddingNewNodesWithFilter(stackNodes, node, nodeCondition, state, spreadingValue,
				&FilterDisconnectedNodeAndDifferentConnectedAreaNumber);
		size = stackNodes.size();
	}
	return count;
}

int Network::FindMaximumConnectedArea(Network* network, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state)
{
	int spreadingValue = 0;
	int max = 0;
	vector<NodePtr>::iterator it = network->nodes.begin();
	while (it != network->nodes.end())
	{
		spreadingValue++; // increase spreadingValue to a new value for another connected area
		int count = ConnectedAreaSpreading(*it, spreadingValue, (*nodeCondition), state);
		//int count = Tools::DetachWithPredicate(spreadingNodes, &Node::isConnectedAreaNumberEqual, spreadingValue);
		if (count > max)
			max = count;
		while (it != network->nodes.end() &&
				((*it)->state != state || (*it)->connectedAreaNumber != 0))
			it++;
	}
	return max;
}

}
