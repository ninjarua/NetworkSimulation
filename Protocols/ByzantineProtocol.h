/*
 * InfectionProtocol.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef INFECTIONPROTOCOL_H_
#define INFECTIONPROTOCOL_H_

#include "stdafx.h"
#include "Network.h"
#include "NetworkInfo.h"
#include "ToleranceBase.h"
#include "Logger.h"

#include "ByzantineMessage.h"
#include "Network.h"
#include "NetworkProtocol.h"

using namespace domain;

namespace protocols {

class ByzantineProtocol : public NetworkProtocol {
private:
	//static ByzantineProtocol* _fault;
public:
	ToleranceBase* tolerance;
	double byzantineProb;
	double nothingProb;
	NetworkStatistic* statisticInfo;
	ByzantineProtocol();
	ByzantineProtocol(double byzantineProb, double detectingProb);
	virtual ~ByzantineProtocol();
	//static ByzantineProtocol* GetInstance(double byzantineProb, double dectectingProb);
	string GetLogFilename();
	void BroadcastMessage(Node* sender, MessageReaction receivingAction);//, object content);
	void SendMessage(Node* sender, Node* receiver, MessageReaction receivingAction);//, string content);
	void Reset(Network* network);
	void RunNetwork(Network* network, void (*startAction)(void* ptr, Network*), bool (*networkCondition)(const Network&));

	static NetworkInfo* GetNetworkInfo(Network* network);
	void Initialize(Network* network, double byzantineProb, double nothingProb);
	void Refresh(Network* network);
	void RandomByzantine(Network* network);
	void ReceiveByzantineMessage(Node* sender, Node* receiver, Message* message);
	static void CallbackReceiveByzantineMessage(void* ptr, Node* sender, Node* receiver, Message* message);
	bool RunStepCheckFinish(Network* network, bool (*stopCondition)(const Network&));
	void Finalize(Network* network);
	void RunFault(Network* network);
	string GetReportFilename();
private:
	static void CallbackPropagateFault(void* ptr, Network* network);
	void PropagateFault(Network* network);
};

} /* namespace protocols */
#endif /* INFECTIONPROTOCOL_H_ */
