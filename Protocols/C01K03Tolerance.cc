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
	// TODO Auto-generated constructor stub

}

C01K03Tolerance::~C01K03Tolerance() {
	// TODO Auto-generated destructor stub
}

string C01K03Tolerance::GetToleranceName()
{
	return "C1K03";
}

void C01K03Tolerance::TolerateNode(NodePtr node, NodePtr byzantine)
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

void C01K03Tolerance::ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message)
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

void C01K03Tolerance::CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message)
{
	C01K03Tolerance* ptrC1K3 = (C01K03Tolerance*)ptr;
	ptrC1K3->ReceiveDeactivateMessage(sender, receiver, message);
}
} /* namespace protocols */
