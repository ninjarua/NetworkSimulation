/*
 * K04Tolerance.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanhnd
 */

#include "K1HopTolerance.h"
#include "DeactivateMessage.h"

namespace protocols {

K1HopTolerance::K1HopTolerance() : ToleranceBase() {

}

K1HopTolerance::~K1HopTolerance() {

}

void K1HopTolerance::TolerateNode(LinkPtr link)
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

string K1HopTolerance::GetToleranceName()
{
	return "K1Hop";
}

void K1HopTolerance::ReceiveDeactivateMessage(Message* message)
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

void K1HopTolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	K1HopTolerance* ptrK4 = (K1HopTolerance*)ptr;
	ptrK4->ReceiveDeactivateMessage(message);
}
} /* namespace protocols */
