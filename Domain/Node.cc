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
    CreateLists();
}

Node::Node(Network* network) {
    // Constructor
    CreateLists();
    ownerNetwork = network;
}

void Node::ClearToDelete()
{
	Tools::EraseAll(links);
	Tools::EraseAll(links2Hop);
}

Node::~Node() {
	//neighbors.clear();
}

//void Node::Initialize()
//{
//    id = 0;
//    state = Sane;
//    connectedAreaNumber = 0;
//}

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
	commonNeighbors = map<long, vector<LinkPtr> >();
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

int Node::addNeighbor(LinkPtr link, LinkPtr srcLink)
{
	links.push_back(link);
	return 1;
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

istringstream& operator>>(istringstream& is, Node& node)
{
	node.Reset();
	int tempX, tempY;
	is >> node.id >> tempX >> tempY; //node.posX >> node.posY;
	cout << node.id << endl;
	if (node.ownerNetwork->has2HopInfo)
	{
		is >> tempX; //node.diameter;
	}

	long id;
	while (is >> id)
	{
		//node.ownerNetwork->makeNeighbors(node.id, id);
		//new Link(&node, node.ownerNetwork->nodes[id]);
		LinkPtr srcLink = NULL;
		LinkPtr link1 = NULL;
		if (node.id <= id)
		{
			srcLink = new Link(node.ownerNetwork->nodes[id], &node);
			link1 = new Link(&node, node.ownerNetwork->nodes[id]);
			srcLink->reverseLink = link1;
			link1->reverseLink = srcLink;
		}
		else
		{
			srcLink = NetworkTools::GetLinkPtr(node.ownerNetwork->nodes[id]->links, node.id);
			link1 = NetworkTools::GetReverseLink(srcLink);
			//link1 = NetworkTools::GetSrcLinkPtr(node.ownerNetwork->nodes[id]->srcLinks, node.id);
		}
		node.addNeighbor(link1, srcLink);
		//node.neighbors.push_back(node.ownerNetwork->nodes.at(id));
	}
	return is;
}

ostream& operator<<(ostream& os, const Node& node)
{
	os << node.id;
	vector<LinkPtr>::const_iterator it = node.links.begin();
	while (it != node.links.end())
	{
		os << Constants::tab << (*it)->dest->id;
		it++;
	}
	os << Constants::endline;
	if (node.ownerNetwork->has2HopInfo)
	{
		map<long, vector<LinkPtr> >::const_iterator commonIt = node.commonNeighbors.begin();
		for(; commonIt != node.commonNeighbors.end(); commonIt++)
		{
			os << Constants::begin2HopList << Constants::tab << commonIt->first;
			vector<LinkPtr>::const_iterator itLink = commonIt->second.begin();
			for(; itLink != commonIt->second.end(); itLink++)
			{
				os << Constants::tab << (*itLink)->dest->id;
			}
			os << Constants::endline;
		}
	}
	return os;
}

void Node::getMidNodesOfNeighborsIn2Hop(string lst2HopLine)
{
	istringstream is(lst2HopLine);
	long destId;
	long mid;
	is >> destId >> mid;
	Link2Hop* link = new Link2Hop(ownerNetwork->nodes[destId], ownerNetwork->nodes[mid]->id);

	while (is >> mid)
	{
		link->mids.push_back(ownerNetwork->nodes[mid]->id);
	}
	links2Hop.push_back(link);
}

void Node::getCommonNeighbors(string commonNeighborsLine)
{
	istringstream is(commonNeighborsLine);
	long destId;
	long common;
	is >> destId >> common;
	commonNeighbors[destId].push_back(NetworkTools::GetLinkPtr(links, common));

	while (is >> common)
	{
		commonNeighbors[destId].push_back(NetworkTools::GetLinkPtr(links, common));
	}
}

void Node::collect2HopInformation()
{
	int neighborSize = links.size();
	for (int i=0; i<neighborSize; i++)
	// for each neighbors
	{
		NodePtr dest_i = links[i]->dest; // dest_i is the ith neighbor of current node
		vector<LinkPtr>::iterator it_i = dest_i->links.begin();	// get all links of that neighbor
		for (; it_i != dest_i->links.end(); it_i++)
		// for each neighbor (it_i->dest) of dest_i, check if it is neighbor of current node
		{
			LinkPtr commonLink = NetworkTools::GetLinkPtr(links, (*it_i)->dest->id);
			// get link from links of current node with id from neighbor of dest_i (mean ith neighbor of current node)
			if (commonLink != NULL)
			// if neighbor (it_i->dest) of dest_i is also neighbor of current node
			// -> add to commonNeighbors map of current node
				commonNeighbors[dest_i->id].push_back(commonLink);
		}
	}
}

string Node::printNodeWithConnectedAreaNumber(const Node& node)
{
	char number[18];
	sprintf(number, "%ld: can = %ld", node.id, node.connectedAreaNumber);
	string out(number);
	return number;
}

} /* namespace domain */
