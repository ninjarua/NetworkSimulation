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
	virtual void BroadcastMessage(NodePtr sender, MessageReaction receivingAction);//, object content);
	virtual void SendMessage(LinkPtr link, MessageReaction receivingAction);//, string content);
	virtual void SendMessage(LinkPtr link, MessageReaction receivingAction, Message* message);

	void Initialize(Network* network);
	virtual void Reset(Network* network);

	virtual void RunNetwork(Network* network, void (*startAction)(void* ptr, Network*), bool (*networkCondition)(const Network&));
	virtual void RunNetworkStep(Network* network);
	virtual string GetLogFilename();
protected:
	string logFile;
	string resultFile;
	void CreateReportString(Network& network);
	virtual void AddNewMessageToNetwork(Network*& network, Message*& message);
//	virtual void RemoveMessageFromNetwork(Network*& network, list<Message*>::iterator it);
};

} /* namespace protocols */
#endif /* NETWORKPROTOCOL_H_ */
