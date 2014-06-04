/*
 * Node.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef NODE_H_
#define NODE_H_

#include "stdafx.h"
#include "Constants.h"
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <map>
#include "Link.h"
#include "Link2Hop.h"

namespace domain {
class Node;
typedef Node* NodePtr;

enum NodeState {Sane = 0, Infected = 1, Inactive = 2, ToBeKilled = 3 };
class Network;
class Node {
public:
	long id;
	Network* ownerNetwork;
	NodeState state;
	vector<LinkPtr> links;
	vector<Link2Hop*> links2Hop;
	map<long, vector<LinkPtr> > commonNeighbors;	// this map saves common neighbors of current node with neighbor having id in int variable
	long connectedAreaNumber;

	Node();
	Node(Network* network);
	virtual ~Node();
	void ClearToDelete();

	void Reset();
	int addNeighbor(LinkPtr link, LinkPtr srcLink);

	bool static isConnectedAreaNumberZero(const Node& node);
	bool static isConnectedAreaNumberEqual(const Node& node, int number);
	bool static isNodeState(const Node& node, const NodeState& state);
	friend bool operator==(const Node& n1, const Node& n2);
	friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator>(const Node& n1, const Node& n2);
	friend istringstream& operator>>(istringstream& os, Node& node);
	friend ostream& operator<<(ostream& os, const Node& node);
	void collect2HopInformation();
	void getMidNodesOfNeighborsIn2Hop(string lst2Hop);
	void getCommonNeighbors(string commonNeighborsLine);
	static string printNodeWithConnectedAreaNumber(const Node& node);
private:
	void CreateLists();
};

} /* namespace domain */
#endif /* NODE_H_ */
