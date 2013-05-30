/*
 * ByzantineMessage.h
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#ifndef BYZANTINEMESSAGE_H_
#define BYZANTINEMESSAGE_H_

#include "Message.h"

namespace domain {

class ByzantineMessage: public domain::Message {
public:
	ByzantineMessage(Node* sender, Node* receiver, int timeSlot, double byzantineProb, double nothingProb);
	virtual ~ByzantineMessage();

	double byzantineProb;
	double nothingProb;
};

} /* namespace domain */
#endif /* BYZANTINEMESSAGE_H_ */
