/*
 * Node.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"
#include "NetworkTools.h"
#include "Tools.h"

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
	Tools::EraseAll(links2Hop);
	//neighbors.clear();
}

void Node::Initialize()
{
    id = 0;
    state = Sane;
    connectedAreaNumber = 0;
    D = 0;
    diameter = 0;
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
	links2Hop = vector<Link2Hop*>();
	tempLinks2Hop = list<Link2Hop*>();
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
	if (node.ownerNetwork->has2HopInfo)
	{
		os << Constants::tab << node.diameter;
	}
	vector<LinkPtr>::const_iterator it = node.links.begin();
	while (it != node.links.end())
	{
		os << Constants::tab << (*it)->dest->id;
		it++;
	}
	os << Constants::endline;
	if (node.ownerNetwork->has2HopInfo)
	{
		vector<Link2Hop*>::const_iterator v2it = node.links2Hop.begin();
		for(; v2it != node.links2Hop.end(); v2it++)
		{
			os << Constants::begin2HopList << Constants::tab << (*v2it)->dest->id;
			vector<int>::const_iterator midIt = (*v2it)->mids.begin();
			for(; midIt != (*v2it)->mids.end(); midIt++)
			{
				os << Constants::tab << (*midIt);
			}
			os << Constants::endline;
		}
	}
	return os;
}

ostream& operator<<(ostream& os, const Node& node)
{
	os << node.id << Constants::tab << node.posX
				<< Constants::tab << node.posY;
	if (node.ownerNetwork->has2HopInfo)
	{
		os << Constants::tab << node.diameter;
	}
	vector<LinkPtr>::const_iterator it = node.links.begin();
	while (it != node.links.end())
	{
		os << Constants::tab << (*it)->dest->id;
		it++;
	}
	os << Constants::endline;
	if (node.ownerNetwork->has2HopInfo)
	{
		vector<Link2Hop*>::const_iterator v2it = node.links2Hop.begin();
		for(; v2it != node.links2Hop.end(); v2it++)
		{
			os << Constants::begin2HopList << Constants::tab << (*v2it)->dest->id;
			vector<int>::const_iterator midIt = (*v2it)->mids.begin();
			for(; midIt != (*v2it)->mids.end(); midIt++)
			{
				os << Constants::tab << (*midIt);
			}
			os << Constants::endline;
		}
	}
	return os;
}

istringstream& operator>>(istringstream& is, Node& node)
{
	node.Reset();
	is >> node.id >> node.posX >> node.posY;
	if (node.ownerNetwork->has2HopInfo)
	{
		is >> node.diameter;
	}

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

void Node::Get2HopInformation(string lst2HopLine)
{
	istringstream is(lst2HopLine);
	int destId;
	int mid;
	is >> destId >> mid;
	Link2Hop* link = new Link2Hop(ownerNetwork->nodes[destId], ownerNetwork->nodes[mid]->id);

	while (is >> mid)
	{
		link->mids.push_back(ownerNetwork->nodes[mid]->id);
	}
	links2Hop.push_back(link);
}

void Node::Collect2HopInformation()
{
	int neighborSize = links.size();
	for (int i = 0; i < neighborSize - 1; i++)
	{
		for (int j = i + 1; j < neighborSize; j++)
		{
			NodePtr nbi = links[i]->dest;
			NodePtr nbj = links[j]->dest;
			// If node links[j] is not contained in list links of node links[i].
			// Add 2-hop information of these node.
			if (!NetworkTools::ContainNode(nbi->links, nbj))
			{
				// Need to check if node is contained in list 2 hop
				list<Link2Hop*>::iterator it2Hop;// = nbi->tempLinks2Hop.begin();
				bool isContained = NetworkTools::ContainNodeIn2Hop(nbi->tempLinks2Hop, nbj, it2Hop);
				if (!isContained || (*it2Hop)->dest->id > nbj->id)
				{
					Link2Hop* link2hop = new Link2Hop(nbj, this->id);
					NetworkTools::InsertIntoSortedLinks2Hop(nbi->tempLinks2Hop, link2hop);

					Link2Hop* link2hopReverse = new Link2Hop(nbi, this->id);
					NetworkTools::InsertIntoSortedLinks2Hop(nbj->tempLinks2Hop, link2hopReverse);
				}
				else
				{
					(*it2Hop)->mids.push_back(this->id);
					list<Link2Hop*>::iterator itj2Hop = nbj->tempLinks2Hop.begin();
					while ((*itj2Hop)->dest->id < nbi->id && itj2Hop != nbj->tempLinks2Hop.end())
						itj2Hop++;
					if (itj2Hop != nbj->tempLinks2Hop.end())
						(*itj2Hop)->mids.push_back(this->id);
				}
			}
		}
	}
}

void Node::ChangeListToVector()
{
	NetworkTools::MoveToVector(tempLinks2Hop, links2Hop);
}

string Node::printNodeWithConnectedAreaNumber(const Node& node)
{
	char number[18];
	sprintf(number, "%d: can = %d", node.id, node.connectedAreaNumber);
	string out(number);
	return number;
}

} /* namespace domain */
