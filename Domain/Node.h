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
	int id;
	Network* ownerNetwork;
	double posX;
	double posY;
	NodeState state;
	int D;
	int diameter;
	//list<NodePtr> neighbors;
	vector<LinkPtr> links;
	vector<LinkPtr> srcLinks;
	list<Link2Hop*> tempLinks2Hop;
	vector<Link2Hop*> links2Hop;
	map<int, vector<LinkPtr> > commonNeighbors;	// this map saves common neighbors of current node with neighbor having id in int variable
	//vector<LinkPtr> noCommonNeighbors2Hop;
//	set<NodePtr> disconnectedNodes;
	int connectedAreaNumber;

	Node();
	Node(Network* network);
	Node(double posX, double posY);
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
	friend ostream& operator<<(ostream& os, const Node& node);
	friend ofstream& operator<<(ofstream& os, const Node& node);
	friend istringstream& operator>>(istringstream& os, Node& node);
	void collect2HopInformation();
	void collect2HopNeighbors();
	void changeListToVector();
	void getMidNodesOfNeighborsIn2Hop(string lst2Hop);
	void getCommonNeighbors(string commonNeighborsLine);
	static string printNodeWithConnectedAreaNumber(const Node& node);
private:
	void CreateLists();
	void Initialize();
};

} /* namespace domain */
#endif /* NODE_H_ */
