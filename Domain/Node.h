/*
 * Node.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef NODE_H_
#define NODE_H_

#include "stdafx.h"
#include <set>

namespace domain {
enum NodeState {Sane = 0, Infected = 1, Detector = 2, Inactive = 3};
class Network;
class Node {
public:
	Node();
	Node(double posX, double posY);
	virtual ~Node();
	int id;
	Network* OwnerNetwork;
public:
	double posX;
	double posY;
	Network* ownerNetwork;
	NodeState state;
	list<Node*>* neighbors;
	set<Node*>* detectedByzantines;
	set<Node*>* disconnectedNodes;
	int connectedAreaNumber;
private:
	void CreateLists();
	void Initialize();
};

} /* namespace domain */
#endif /* NODE_H_ */
