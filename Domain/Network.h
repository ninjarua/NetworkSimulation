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
#include "Message.h"
#include "NetworkInfo.h"

namespace domain {

class Network {
public:
    float transRange;
    int sequenceId;
    int currentTimeSlot;

    vector<Node*>* nodes;
    vector<Message*>* messages;
    vector<Message*>* newMessages;
	NetworkInfo* info;

	Network();
	virtual ~Network();
	Node* AddNode(Node* node);
	void CreateEmptyNodes(int n);
	bool static noNewMessageInNetwork(Network* network);

	friend ofstream& operator<<(ofstream& os, const Network& network);
	friend istream& operator>>(istream& os, Network& network);
};

} /* namespace domain */
#endif /* NETWORK_H_ */
