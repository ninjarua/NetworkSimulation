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
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include "Link.h"
#include "Link2Hop.h"

namespace domain {
class Node;
typedef Node* NodePtr;

enum NodeState {Sane = 0, Infected = 1, Inactive = 2};
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
	void Collect2HopInformation();
	void ChangeListToVector();
	void Get2HopInformation(string lst2Hop);
	static string printNodeWithConnectedAreaNumber(const Node& node);
private:
	void CreateLists();
	void Initialize();
};

} /* namespace domain */
#endif /* NODE_H_ */
