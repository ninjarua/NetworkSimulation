/*
 * K11Tolerance.cc
 *
 *  Created on: Jun 9, 2013
 *      Author: thanh
 */

#include "K11Tolerance.h"
#include "DeactivateMessage.h"

using namespace domain;

namespace protocols {

K11Tolerance::K11Tolerance() : ToleranceBase() {

}

K11Tolerance::~K11Tolerance() {

}

void K11Tolerance::TolerateNode(NodePtr node, NodePtr byzantine)
{
	ToleranceBase::TolerateNode(node, byzantine);
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;

	list<NodePtr>::iterator it = node->neighbors.begin();
	for (; it != node->neighbors.end(); it++)
	{
		if ((*it)->state == Infected || (*it)->state == Inactive)
			continue;
		DeactivateMessage* message = new DeactivateMessage(node, (*it), (*it)->ownerNetwork->currentTimeSlot);
		message->creationTime = 1;
		SendMessage(node, (*it), CallbackReceiveDeactivateMessage, message);
	}
}

void K11Tolerance::ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message)
{
	if (receiver->state == Infected)
		return;
	if (receiver->state == Sane)
	{
		receiver->state = Inactive;
		receiver->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;

	DeactivateMessage* deactivateMessage = (DeactivateMessage*)message;
	if (deactivateMessage->TTL == 0)
		return;

	list<NodePtr>::iterator it = receiver->neighbors.begin();
	for (; it != receiver->neighbors.end(); it++)
	{
		if ((*it)->state == Infected || (*it)->state == Inactive || (*it) == sender)
			continue;
		DeactivateMessage* newMessage = new DeactivateMessage(receiver, (*it), (*it)->ownerNetwork->currentTimeSlot);
		newMessage->TTL = deactivateMessage->TTL - 1;
		SendMessage(receiver, *it, CallbackReceiveDeactivateMessage, newMessage);
	}
}

void K11Tolerance::CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message)
{
	K11Tolerance* ptrK11 = (K11Tolerance*)ptr;
	ptrK11->ReceiveDeactivateMessage(sender, receiver, message);
}
}
