/*
 * K1Tolerance.cc
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#include "K03Tolerance.h"
#include "NetworkTools.h"
#include "DeactivateMessage.h"

namespace protocols {

K03Tolerance::K03Tolerance() {

}

K03Tolerance::~K03Tolerance() {

}

string K03Tolerance::GetToleranceName()
{
	return "K3";
}

void K03Tolerance::TolerateNode(LinkPtr link)
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
		if (NetworkTools::HasCommonNeighborsExcept((*it)->dest, link->src, node))
		{
			DeactivateMessage* message = new DeactivateMessage((*it), node->ownerNetwork->currentTimeSlot);
			message->TTL = 0;
			SendMessage((*it), CallbackReceiveDeactivateMessage, message);
		}
	}
}

void K03Tolerance::ReceiveDeactivateMessage(Message* message)
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

void K03Tolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	K03Tolerance* ptrK3 = (K03Tolerance*)ptr;
	ptrK3->ReceiveDeactivateMessage(message);
}

} /* namespace domain */
