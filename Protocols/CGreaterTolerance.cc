/*
 * CGreateTolerance.cc
 *
 *  Created on: Oct 20, 2014
 *      Author: thanhnd
 */

#include <CGreaterTolerance.h>
#include "DeactivateMessage.h"

namespace protocols {

CGreateTolerance::CGreateTolerance() {
	// TODO Auto-generated constructor stub

}

CGreateTolerance::~CGreateTolerance() {
	// TODO Auto-generated destructor stub
}

string CGreateTolerance::GetToleranceName()
{
	return "CGter";
}

void CGreateTolerance::TolerateNode(LinkPtr link)
{
	ToleranceBase::TolerateNode(link);
	link->state = Cut;

	int infectedDegree = link->src->links.size();

	NodePtr node = link->dest;
	if (node->links.size() < infectedDegree)
		node->state = Inactive;
	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->state == Cut || (*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		if ((*it)->dest == link->src)
			(*it)->state = Cut;
		else if ( (*it)->dest->links.size() < infectedDegree )
		{
			node->state = Inactive;
			node->ownerNetwork->info.numberOfInactiveNodes++;
			DeactivateMessage* message = new DeactivateMessage((*it), link->src->ownerNetwork->currentTimeSlot);
			message->TTL = 0;
			SendMessage((*it), CallbackReceiveDeactivateMessage, message);
		}
	}
}

void CGreateTolerance::ReceiveDeactivateMessage(Message* message)
{
	NodeState destState = message->link->dest->state;
	if (destState == Infected || destState == Inactive)
		return;
	if (destState == Sane)
	{
		message->link->dest->state = Inactive;
		message->link->dest->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;
}

void CGreateTolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	CGreateTolerance* ptrCGt = (CGreateTolerance*)ptr;
	ptrCGt->ReceiveDeactivateMessage(message);
}

}
