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
	// TODO Auto-generated constructor stub

}

K03Tolerance::~K03Tolerance() {
	// TODO Auto-generated destructor stub
}

string K03Tolerance::GetToleranceName()
{
	return "K3";
}

void K03Tolerance::TolerateNode(NodePtr node, NodePtr byzantine)
{
	ToleranceBase::TolerateNode(node, byzantine);
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;

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

void K03Tolerance::ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message)
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

void K03Tolerance::CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message)
{
	K03Tolerance* ptrK3 = (K03Tolerance*)ptr;
	ptrK3->ReceiveDeactivateMessage(sender, receiver, message);
}

} /* namespace domain */
