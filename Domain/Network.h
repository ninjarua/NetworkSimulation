/*
 * Network.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <list>
#include "Message.h"
#include "NetworkInfo.h"
#include "NetworkStatistic.h"

namespace domain {

class Network {
public:
    float transRange;
    int sequenceId;
    int currentTimeSlot;

    vector<Node*> nodes;
    vector<Message*> messages;
    vector<Message*> newMessages;
	NetworkInfo info;

	Network();
	virtual ~Network();

	friend ofstream& operator<<(ofstream& os, const Network& network);
	friend istream& operator>>(istream& os, Network& network);

	void AddNode(Node* node);
	void CreateEmptyNodes(int n);
	static bool noNewMessageInNetwork(const Network& network);
	static int FindMaximumConnectedArea(Network* network, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state);

private:
	static void ConnectedAreaSpreading(Node* seed, int spreadingValue, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state);
	static stack<Node*> LookingForNode(const list<Node*>& listInput, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state);
	static void AddingNewNodesWithFilter(stack<Node*>& stack, Node* consideringNode, bool (*nodeCondition)(const Node&, const NodeState&),
    		const NodeState& state, int number, bool (*filter)(Node* n1, Node* n2, int number));
	static bool FilterDisconnectedNodeAndDifferentConnectedAreaNumber(Node* n1, Node* n2, int number);
};

} /* namespace domain */
#endif /* NETWORK_H_ */
