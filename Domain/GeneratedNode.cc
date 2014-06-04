/*
 * RandomNode.cc
 *
 *  Created on: May 31, 2014
 *      Author: thanh
 */

#include "Network.h"

namespace domain {

GeneratedNode::GeneratedNode() : Node() {
    posX = 0;
    posY = 0;
	Initialize();
}

GeneratedNode::GeneratedNode(Network* network) : Node(network) {
    posX = 0;
    posY = 0;
	Initialize();
}

GeneratedNode::GeneratedNode(double x, double y) : Node() {
    posX = x;
    posY = y;
	Initialize();
}

GeneratedNode::~GeneratedNode() {
	// TODO Auto-generated destructor stub
}

void GeneratedNode::Initialize()
{
    id = 0;
    state = Sane;
    connectedAreaNumber = 0;
    D = 0;
    diameter = 0;
}

ostream& operator<<(ostream& os, const GeneratedNode& node)
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

} /* namespace protocols */
