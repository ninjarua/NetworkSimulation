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

void Node::ClearToDelete()
{
	srcLinks.clear();
	Tools::EraseAll(links);
	Tools::EraseAll(links2Hop);
}

Node::~Node() {
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
	srcLinks = vector<LinkPtr>();
	links2Hop = vector<Link2Hop*>();
	tempLinks2Hop = list<Link2Hop*>();
	commonNeighbors = map<int, vector<LinkPtr> >();
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
	srcLinks.push_back(srcLink);
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
//		vector<Link2Hop*>::const_iterator v2it = node.links2Hop.begin();
//		for(; v2it != node.links2Hop.end(); v2it++)
//		{
//			os << Constants::begin2HopList << Constants::tab << (*v2it)->dest->id;
//			vector<int>::const_iterator midIt = (*v2it)->mids.begin();
//			for(; midIt != (*v2it)->mids.end(); midIt++)
//			{
//				os << Constants::tab << (*midIt);
//			}
//			os << Constants::endline;
//		}
		map<int, vector<LinkPtr> >::const_iterator commonIt = node.commonNeighbors.begin();
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
//		vector<Link2Hop*>::const_iterator v2it = node.links2Hop.begin();
//		for(; v2it != node.links2Hop.end(); v2it++)
//		{
//			os << Constants::begin2HopList << Constants::tab << (*v2it)->dest->id;
//			vector<int>::const_iterator midIt = (*v2it)->mids.begin();
//			for(; midIt != (*v2it)->mids.end(); midIt++)
//			{
//				os << Constants::tab << (*midIt);
//			}
//			os << Constants::endline;
//		}
		map<int, vector<LinkPtr> >::const_iterator commonIt = node.commonNeighbors.begin();
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
		LinkPtr srcLink = NULL;
		LinkPtr link1 = NULL;
		if (node.id <= id)
		{
			srcLink = new Link(node.ownerNetwork->nodes[id], &node);
			link1 = new Link(&node, node.ownerNetwork->nodes[id]);
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

void Node::getMidNodesOfNeighborsIn2Hop(string lst2HopLine)
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

void Node::getCommonNeighbors(string commonNeighborsLine)
{
	istringstream is(commonNeighborsLine);
	int destId;
	int common;
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

void Node::collect2HopNeighbors()
{
	int neighborSize = links.size();
	for (int i = 0; i < neighborSize - 1; i++)
	{
		for (int j = i + 1; j < neighborSize; j++)
		{
			NodePtr nbi = links[i]->dest;
			NodePtr nbj = links[j]->dest;
			// If node nbj is not contained in list links of node nbi.
			// Add 2-hop information of these node.
			if (!NetworkTools::ContainNode(nbi->links, nbj))
			{
				// Need to check if nbj is contained in list 2 hop of nbi
				// it2Hop will point to the Link2hop between nbi -> nbj
				list<Link2Hop*>::iterator it2Hop;// = nbi->tempLinks2Hop.begin();
				bool isContained = NetworkTools::ContainNodeIn2Hop(nbi->tempLinks2Hop, nbj, it2Hop);
				if (!isContained || (*it2Hop)->dest->id > nbj->id)
				// if there is not link2hop between nbi and nbj,
				// create a new link2hop and add into list link2hop of both nbi and nbj
				// mid of link2hop between nbi and nbj is this->id
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

void Node::changeListToVector()
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
