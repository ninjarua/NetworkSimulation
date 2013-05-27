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
	NetworkInfo info;

	Network();
	virtual ~Network();
	Node* AddNode(Node* node);
	void CreateEmptyNodes(int n);

	friend ostream& operator<<(ostream& os, const Network& network);
	friend istream& operator>>(istream& os, const Network& network);
};

} /* namespace domain */
#endif /* NETWORK_H_ */
