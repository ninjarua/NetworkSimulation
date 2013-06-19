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

void K11Tolerance::TolerateNode(LinkPtr link)
{
	ToleranceBase::TolerateNode(link);
	NodePtr node = link->dest;
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;

	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		DeactivateMessage* message = new DeactivateMessage((*it), node->ownerNetwork->currentTimeSlot);
		message->creationTime = 1;
		SendMessage((*it), CallbackReceiveDeactivateMessage, message);
	}
}

void K11Tolerance::ReceiveDeactivateMessage(Message* message)
{
	NodePtr node = message->link->dest;
	if (node->state == Infected)
		return;
	if (node->state == Sane)
	{
		node->state = Inactive;
		node->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;

	DeactivateMessage* deactivateMessage = (DeactivateMessage*)message;
	if (deactivateMessage->TTL == 0)
		return;

	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->dest->state == Infected || (*it)->dest->state == Inactive
				|| (*it)->dest == message->link->src)
			continue;
		DeactivateMessage* newMessage = new DeactivateMessage((*it), node->ownerNetwork->currentTimeSlot);
		newMessage->TTL = deactivateMessage->TTL - 1;
		SendMessage(*it, CallbackReceiveDeactivateMessage, newMessage);
	}
}

void K11Tolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	K11Tolerance* ptrK11 = (K11Tolerance*)ptr;
	ptrK11->ReceiveDeactivateMessage(message);
}
}
