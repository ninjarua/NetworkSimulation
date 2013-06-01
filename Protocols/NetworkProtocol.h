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
#include "Logger.h"

using namespace domain;

namespace protocols {
class NetworkProtocol {
public:
	ByzantineReport* report;

	NetworkProtocol();
	virtual ~NetworkProtocol();
	//typedef void (NetworkProtocol::*receivingMessage)(Node*, Node*, Message*);
	virtual void BroadcastMessage(Node* sender, MessageReaction receivingAction);//, object content);
	virtual void SendMessage(Node* sender, Node* receiver, MessageReaction receivingAction);//, string content);
	virtual void SendMessage(Node* sender, Node* receiver, MessageReaction receivingAction, Message* message);

	virtual void Initialize(Network* network);
	virtual void Reset(Network* network);

	virtual void RunNetwork(Network* network, void (*startAction)(void* ptr, Network*), bool (*networkCondition)(const Network&));
	virtual void RunNetworkStep(Network* network);
	virtual string GetLogFilename();

protected:
	string logFile;
	string resultFile;
	void CreateReportString(Network& network);
};

} /* namespace protocols */
#endif /* NETWORKPROTOCOL_H_ */
