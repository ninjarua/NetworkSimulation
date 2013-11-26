/*
 * KCommonTolerance.cc
 *
 *  Created on: Aug 22, 2013
 *      Author: thanhnd
 */

#include "KCo1Tolerance.h"
#include "DeactivateMessage.h"
#include "NetworkTools.h"

namespace protocols {

KCo1Tolerance::KCo1Tolerance() : ToleranceBase() {

}

KCo1Tolerance::~KCo1Tolerance() {
}

void KCo1Tolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	//messageLink->state = Cut;
	NodePtr node = messageLink->dest;
	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->state == Cut || (*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
//		if ((*it)->dest == messageLink->src)
//			(*it)->state = Cut;

		LinkPtr linkToCut = NetworkTools::GetLinkPtr(messageLink->src->links, (*it)->dest->id);
		if (linkToCut != NULL && linkToCut->state != Cut)
		{
			DeactivateMessage* killingMessage = new DeactivateMessage(*it, node->ownerNetwork->currentTimeSlot);
			SendMessage(*it, CallbackReceiveKillingMessage, killingMessage);
		}
	}
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;
}

string KCo1Tolerance::GetToleranceName()
{
	return "KCommon";
}

void KCo1Tolerance::CallbackReceiveKillingMessage(void *ptr, Message* message)
{
	KCo1Tolerance* ptrCommon = (KCo1Tolerance*)ptr;
	ptrCommon->ReceiveKillingMessage(message);
}

void KCo1Tolerance::ReceiveKillingMessage(Message* message)
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
