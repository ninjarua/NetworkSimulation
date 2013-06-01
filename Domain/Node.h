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

namespace domain {
enum NodeState {Sane = 0, Infected = 1, Detector = 2, Inactive = 3};
class Network;
class Node {
public:
	int id;
	Network* ownerNetwork;
	double posX;
	double posY;
	NodeState state;
	list<Node*> neighbors;
	set<Node*> detectedByzantines;
	set<Node*> disconnectedNodes;
	int connectedAreaNumber;

	Node();
	Node(Network* network);
	Node(double posX, double posY);
	virtual ~Node();

	void Reset();

	bool static isConnectedAreaNumberZero(const Node& node);
	bool static isConnectedAreaNumberEqual(const Node& node, int number);
	bool static isNodeState(const Node& node, const NodeState& state);
	friend bool operator==(const Node& n1, const Node& n2);
	friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator>(const Node& n1, const Node& n2);
	friend ostream& operator<<(ostream& os, const Node& node);
	friend ofstream& operator<<(ofstream& os, const Node& node);
	friend istringstream& operator>>(istringstream& os, Node& node);
private:
	void CreateLists();
	void Initialize();
};

} /* namespace domain */
#endif /* NODE_H_ */
