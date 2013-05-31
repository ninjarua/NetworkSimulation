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
#include <fstream>
#include "Network.h"
#include "ByzantineReport.h"

using namespace domain;

namespace protocols {
class NetworkProtocol {
public:
	NetworkProtocol();
	virtual ~NetworkProtocol();
	ByzantineReport* report;
	//typedef void (NetworkProtocol::*receivingMessage)(Node*, Node*, Message*);

	static void BroadcastMessage(Node* sender, MessageReaction receivingAction);//, object content);
	static void SendMessage(Node* sender, Node* receiver, MessageReaction receivingAction);//, string content);
	static void SendMessage(Node* sender, Node* receiver, MessageReaction receivingAction, Message* message);

	virtual void Initialize(Network* network);
	virtual void Reset(Network* network);

	virtual void RunNetwork(Network* network, void (*startAction)(Network*), bool (*networkCondition)(Network*));
	virtual void RunNetworkStep(Network* network);

protected:
	string logFile;
	string resultFile;
	void CreateReportString(Network* network);
};

} /* namespace protocols */
#endif /* NETWORKPROTOCOL_H_ */
