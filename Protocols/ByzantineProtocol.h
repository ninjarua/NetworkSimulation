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
	ByzantineProtocol();
	ByzantineProtocol(double byzantineProb, double detectingProb);
	virtual ~ByzantineProtocol();
	//static ByzantineProtocol* GetInstance(double byzantineProb, double dectectingProb);

	static NetworkInfo* GetNetworkInfo(Network* network);
	void Initialize(Network* network, double byzantineProb, double nothingProb);
	void Refresh(Network* network);
	void Reset(Network* network);
	void RandomByzantine(Network* network);
	void ReceiveByzantineMessage(Node* sender, Node* receiver, Message* message);
	static void CallbackReceiveByzantineMessage(void* ptr, Node* sender, Node* receiver, Message* message);
	bool RunStepCheckFinish(Network* network, bool (*stopCondition)(Network*));
	void Finalize(Network* network);
	void RunNetwork(Network* network, void (*startAction)(Network*), bool (*stopCondition)(Network*));
	void RunFault(Network* network);
private:
	static void PropagateFault(Network* network);
};

} /* namespace protocols */
#endif /* INFECTIONPROTOCOL_H_ */
