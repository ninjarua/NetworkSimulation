/*
 * ByzantineMessage.cc
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#include "ByzantineMessage.h"

namespace domain {

ByzantineMessage::ByzantineMessage(NodePtr sender, NodePtr receiver, const int& timeSlot, double byzantinePb, double nothingPb)
	: Message(sender, receiver, timeSlot)
{
	byzantineProb = byzantinePb;
	nothingProb = nothingPb;
}

ByzantineMessage::~ByzantineMessage() {
	// TODO Auto-generated destructor stub
}

string ByzantineMessage::GetMessageName() const
{
	return "Byzantine message";
}

} /* namespace domain */
