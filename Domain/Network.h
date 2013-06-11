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
#include <vector>
#include "Message.h"
#include "NetworkInfo.h"
#include "NetworkStatistic.h"
#include "Logger.h"

namespace domain {

class Network {
public:
    float transRange;
    int sequenceId;
    int currentTimeSlot;

    vector<Node*> nodes;
    list<Message*> messages;
    // is used to overcome the size() function of list
    int messageCount;
    list<Message*> newMessages;
    bool hasTopology;
	NetworkInfo info;

	Network();
	virtual ~Network();

	friend ofstream& operator<<(ofstream& os, const Network& network);
	friend istream& operator>>(istream& os, Network& network);

	void addNode(NodePtr node);
	void createEmptyNodes(int n);
	static bool noNewMessageInNetwork(const Network& network);
	static int FindMaximumConnectedArea(Network* network, bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state);

private:
	static int ConnectedAreaSpreading(NodePtr seed, int spreadingValue,
			bool (*nodeCondition)(const Node&, const NodeState&), const NodeState& state);
	static stack<NodePtr> LookingForNode(const list<NodePtr>& listInput, bool (*nodeCondition)(const Node&, const NodeState&),
			const NodeState& state, int settingNumber);
	static void AddingNewNodesWithFilter(stack<NodePtr>& stack, NodePtr consideringNode, bool (*nodeCondition)(const Node&, const NodeState&),
    		const NodeState& state, int number, bool (*filter)(NodePtr, NodePtr, int));
	static bool FilterDisconnectedNodeAndDifferentConnectedAreaNumber(NodePtr n1, NodePtr n2, int number);
	static string DebugString(const Node& node, string original);
	static bool HasOverlappedNeighbors(const NodePtr n1, const NodePtr n2);
};

}
#endif
