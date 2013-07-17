/*
 * Network.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"
#include "NetworkTools.h"
#include "Link.h"
#include <math.h>
#include <stdint.h>
#include <mpi.h>

namespace domain {

Network::Network() {
	sequenceId = 0;
	currentTimeSlot = 0;
	messageCount = 0;
	newMessageCount = 0;
	info = NetworkInfo();
	nodes = vector<NodePtr>();
	messages = list<Message*>();
	hasTopology = false;
	has2HopInfo = false;
}

Network::~Network() {

}

void Network::Reset()
{
	messageCount = 0;
	newMessageCount = 0;
	Tools::EraseAll(nodes);
	Tools::EraseAll(messages);
	diameter = 0;
	sequenceId = 0;
	vector<vector<int> >::iterator it = distance.begin();
	for(; it != distance.end(); it++)
		(*it).clear();
	distance.clear();
	has2HopInfo = false;
}

void Network::createEmptyNodes(int n)
{
	Reset();
	for (int i=0; i<n; i++)
	{
		NodePtr newNode(new Node());
		addNode(newNode);
	}
}

void Network::createMatrixDistance()
{
	for(int i = 0; i < size; i++)
	{
		vector<int> distance_i(size);
		for (int j = 0; j < size; j++)
			distance_i[j] = 0x7fff;
		distance_i[i] = 0;
		distance.push_back(distance_i);
	}
}

void Network::updateMatrixDistanceFromNeighbors()
{
	vector<NodePtr>::iterator it = nodes.begin();
	for(; it != nodes.end(); it++)
	{
		vector<LinkPtr>::iterator itnb = (*it)->links.begin();
		for(; itnb != (*it)->links.end(); itnb++)
			distance[(*it)->id][(*itnb)->dest->id] = 1;
	}
}

void Network::runFloyd()
{
//	int cpu_size;
//	int cpu_rank;
//	MPI_Comm_size(MPI_COMM_WORLD, &cpu_size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &cpu_rank);

//	int cpu_width = sqrt(cpu_size);
//	int local_i = cpu_rank / cpu_width;
//	int local_j = cpu_rank % cpu_width;

	for (int k = 0; k < size; k++)
		for (int i = 0; i < size; i++)
			for (int j = i + 1; j < size; j++)
			{
				int d_ik = distance[i][k];
				int d_kj = distance[k][j];
				if (d_ik + d_kj < distance[i][j])
				{
					distance[i][j] = d_ik + d_kj;
					distance[j][i] = distance[i][j];
				}
			}
	diameter = 0;
	int sumDiameter = 0;
	for(int i = 0; i < size; i++)
	{
		nodes[i]->diameter = 0;
		for (int j = i + 1; j < size; j++)
		{
			int d_ij = distance[i][j];
			if (d_ij != 0x7fff && d_ij > nodes[i]->diameter)
				nodes[i]->diameter = d_ij;
		}
		if (nodes[i]->diameter > diameter)
			diameter = nodes[i]->diameter;
		sumDiameter += nodes[i]->diameter;
	}
	avgDiameter = (double)sumDiameter / size;
}

void Network::makeNeighbors(int id1, int id2)
{
	//Link* link = new Link(nodes[id1], nodes[id2]);
	nodes[id1]->addNeighbor(new Link(nodes[id1], nodes[id2]));
	nodes[id2]->addNeighbor(new Link(nodes[id2], nodes[id1]));
}

ofstream& operator<<(ofstream& os, const Network& network)
{
	os << network.nodes.size() << Constants::tab << network.diameter << Constants::tab << network.avgDiameter << Constants::endline;
	if (network.has2HopInfo)
		os << Constants::has2Hop << Constants::endline;
	vector<NodePtr>::const_iterator it = network.nodes.begin();
	for (; it != network.nodes.end(); it++)
		os << *(*it);
	return os;
}

// Input operator which is used to read a Network from a file.
istream& operator>>(istream& is, Network& network)
{
	string line("");
	getline(is, line);
	istringstream firstline(line);
	firstline >> network.size >> network.diameter >> network.avgDiameter;
	network.createEmptyNodes(network.size);

	getline(is, line);
	if (line == Constants::has2Hop)
	{
		network.has2HopInfo = true;
		getline(is, line);
	}
	else
	{
		network.has2HopInfo = false;
	}
	vector<NodePtr>::const_iterator it = network.nodes.begin();
	while (!is.eof())
	{
		istringstream iss(line);
		iss >> *(*it);
		getline(is, line);

		if (network.has2HopInfo)
		{
			while (line.find(Constants::begin2HopList) == 0)
			{
				(*it)->Get2HopInformation(line.substr(3));
				getline(is, line);
			}
		}
		it++;
	}
	network.createAdvancedInformation();
	return is;
}

void Network::createAdvancedInformation()
{
//	createMatrixDistance();
//	updateMatrixDistanceFromNeighbors();
//	runFloyd();
	if (!has2HopInfo)
		collect2HopInformation();
}

void Network::collect2HopInformation()
{
	vector<NodePtr>::iterator it = nodes.begin();
	for (; it != nodes.end(); it++)
	{
		(*it)->Collect2HopInformation();
	}
	it = nodes.begin();
	for (; it != nodes.end(); it++)
		(*it)->ChangeListToVector();
	has2HopInfo = true;
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

// Looking for nodes which are dest in list of links being satisfied the condition to put into stack
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
	return n1->connectedAreaNumber != number && NetworkTools::GetLinkPtr(n2->links, n1->id)->state != Cut
			&& NetworkTools::GetLinkPtr(n1->links, n2->id)->state != Cut;
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
