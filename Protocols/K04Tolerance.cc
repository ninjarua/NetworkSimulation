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

}

K04Tolerance::~K04Tolerance() {

}

void K04Tolerance::TolerateNode(LinkPtr link)
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
		message->TTL = 0;
		SendMessage((*it), CallbackReceiveDeactivateMessage, message);
	}
}

string K04Tolerance::GetToleranceName()
{
	return "K4";
}

void K04Tolerance::ReceiveDeactivateMessage(Message* message)
{
	NodePtr node = message->link->dest;
	if (node->state == Infected || node->state == Inactive)
		return;
	if (node->state == Sane)
	{
		node->state = Inactive;
		node->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;
}

void K04Tolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	K04Tolerance* ptrK4 = (K04Tolerance*)ptr;
	ptrK4->ReceiveDeactivateMessage(message);
}
} /* namespace protocols */
