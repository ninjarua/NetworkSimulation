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
#include "Message.h"
#include "NetworkInfo.h"

namespace domain {

class Network {
public:
	vector<Node*>* nodes;
    vector<Message*>* messages;
    vector<Message*>* newMessages;
	NetworkInfo info;

	Network();
	virtual ~Network();
	Node* AddNode(Node* node);

    float transRange;
    int sequenceId;
    int currentTimeSlot;
};

} /* namespace domain */
#endif /* NETWORK_H_ */
