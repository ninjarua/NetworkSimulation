/*
 * C01K03Tolerance.cc
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#include "C01K03Tolerance.h"
#include "NetworkTools.h"
#include "DeactivateMessage.h"

using namespace domain;

namespace protocols {

C01K03Tolerance::C01K03Tolerance() {

}

C01K03Tolerance::~C01K03Tolerance() {

}

string C01K03Tolerance::GetToleranceName()
{
	return "C1K03";
}

void C01K03Tolerance::TolerateNode(LinkPtr link)
{
	ToleranceBase::TolerateNode(link);
	link->state = Cut;
	//node->disconnectedNodes.insert(byzantine);

	NodePtr node = link->dest;
	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		if ((*it)->dest == link->src)
		{
			(*it)->state = Cut;
		}
		else if (NetworkTools::HasCommonNeighborsExcept((*it)->dest, link->src, node))
		{
			DeactivateMessage* message = new DeactivateMessage((*it), link->src->ownerNetwork->currentTimeSlot);
			message->TTL = 0;
			SendMessage((*it), CallbackReceiveDeactivateMessage, message);
		}
	}
}

void C01K03Tolerance::ReceiveDeactivateMessage(Message* message)
{
	NodeState destState = message->link->dest->state;
	if (destState == Infected)
		return;
	if (destState == Sane)
	{
		message->link->dest->state = Inactive;
		message->link->dest->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;
}

void C01K03Tolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	C01K03Tolerance* ptrC1K3 = (C01K03Tolerance*)ptr;
	ptrC1K3->ReceiveDeactivateMessage(message);
}
} /* namespace protocols */
