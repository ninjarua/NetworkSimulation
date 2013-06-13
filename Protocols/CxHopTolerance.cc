/*
 * CxHopTolerance.cc
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#include "CxHopTolerance.h"
#include "NetworkTools.h"
#include "DeactivateMessage.h"

namespace protocols {

CxHopTolerance::CxHopTolerance() {

}

CxHopTolerance::~CxHopTolerance() {

}

string CxHopTolerance::GetToleranceName()
{
	return "C1K03";
}

void CxHopTolerance::TolerateNode(NodePtr node, NodePtr byzantine)
{
	ToleranceBase::TolerateNode(node, byzantine);
	node->disconnectedNodes.insert(byzantine);

	list<NodePtr>::iterator it = node->neighbors.begin();
	for (; it != node->neighbors.end(); it++)
	{
		if ((*it)->state == Infected || (*it)->state == Inactive)
			continue;
		if (NetworkTools::HasCommonNeighborsExcept(*it, byzantine, node))
		{
			DeactivateMessage* message = new DeactivateMessage(node, *it, (*it)->ownerNetwork->currentTimeSlot);
			message->TTL = 0;
			SendMessage(node, (*it), CallbackReceiveDeactivateMessage, message);
		}
	}
}

void CxHopTolerance::ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message)
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

void CxHopTolerance::CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message)
{
	CxHopTolerance* ptrC1K3 = (CxHopTolerance*)ptr;
	ptrC1K3->ReceiveDeactivateMessage(sender, receiver, message);
}

} /* namespace protocols */
