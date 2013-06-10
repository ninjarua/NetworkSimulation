/*
 * K04Tolerance.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanhnd
 */

#include "K04Tolerance.h"
#include "DeactivateMessage.h"

namespace protocols {

K04Tolerance::K04Tolerance() : ToleranceBase() {
	// TODO Auto-generated constructor stub

}

K04Tolerance::~K04Tolerance() {
	// TODO Auto-generated destructor stub
}

void K04Tolerance::TolerateNode(NodePtr node, NodePtr byzantine)
{
	ToleranceBase::TolerateNode(node, byzantine);
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;
	node->detectedByzantines.insert(byzantine);
	node->disconnectedNodes.insert(byzantine);

	list<NodePtr>::iterator it = node->neighbors.begin();
	for (; it != node->neighbors.end(); it++)
	{
		if ((*it)->state == Infected || (*it)->state == Inactive)
			continue;
		DeactivateMessage* message = new DeactivateMessage(node, (*it), (*it)->ownerNetwork->currentTimeSlot);
		message->TTL = 0;
		SendMessage(node, (*it), CallbackReceiveDeactivateMessage, message);
	}
}

void K04Tolerance::ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message)
{
	if (receiver->state == Infected)
		return;
	if (receiver->state == Sane)
	{
		receiver->state = Inactive;
		receiver->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;
}

void K04Tolerance::CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message)
{
	K04Tolerance* ptrK4 = (K04Tolerance*)ptr;
	ptrK4->ReceiveDeactivateMessage(sender, receiver, message);
}
} /* namespace protocols */
