/*
 * KCommonTolerance.cc
 *
 *  Created on: Aug 22, 2013
 *      Author: thanhnd
 */

#include "KCommonTolerance.h"
#include "DeactivateMessage.h"
#include "NetworkTools.h";

namespace protocols {

KCommonTolerance::KCommonTolerance() {
	// TODO Auto-generated constructor stub

}

KCommonTolerance::~KCommonTolerance() {
	// TODO Auto-generated destructor stub
}

void KCommonTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	messageLink->state = Cut;
	NodePtr node = messageLink->dest;
	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->state == Cut || (*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		if ((*it)->dest == messageLink->src)
			(*it)->state = Cut;

		LinkPtr linkToCut = NetworkTools::GetLinkPtr(messageLink->src->links, (*it)->dest->id);
		if (linkToCut != NULL && linkToCut->state != Cut)
		{
			DeactivateMessage* cuttingMessage = new DeactivateMessage(*it, node->ownerNetwork->currentTimeSlot);
			SendMessage(*it, CallbackReceiveKillingMessage, cuttingMessage);
		}
	}
}

string KCommonTolerance::GetToleranceName()
{
	return "KCommon";
}

void KCommonTolerance::CallbackReceiveKillingMessage(void *ptr, Message* message)
{
	KCommonTolerance* ptrC01 = (KCommonTolerance*)ptr;
	ptrC01->ReceiveKillingMessage(message);
}

void KCommonTolerance::ReceiveKillingMessage(Message* message)
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

} /* namespace protocols */
