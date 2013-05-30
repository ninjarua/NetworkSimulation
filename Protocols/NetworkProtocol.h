/*
 * NetworkProtocol.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef NETWORKPROTOCOL_H_
#define NETWORKPROTOCOL_H_

#include "stdafx.h"
#include <string>
#include "Network.h"

using namespace domain;

namespace protocols {

class NetworkProtocol {
public:
	NetworkProtocol();
	virtual ~NetworkProtocol();
public:
	string reportString;
	//typedef void (NetworkProtocol::*receivingMessage)(Node*, Node*, Message*);

	static void BroadcastMessage(Node* sender, void (*receivingAction)(void*, Node*, Node*, Message*));//, object content);
	static void SendMessage(Node* sender, Node* receiver, void (*receivingAction)(void*, Node*, Node*, Message*));//, string content);
	static void SendMessage(Node* sender, Node* receiver, void (*receivingAction)(void*, Node*, Node*, Message*), Message* message);

	virtual void Initialize(Network* network);
	virtual void Reset(Network* network);

	virtual void RunNetwork(Network* network, void (*startAction)(Network*), bool (*networkCondition)(Network*));
	virtual void RunNetworkStep(Network* network);

protected:
	void CreateReportString(Network* network);
};

} /* namespace protocols */
#endif /* NETWORKPROTOCOL_H_ */
