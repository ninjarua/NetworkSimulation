/*
 * KCoInfyTolerance.cc
 *
 *  Created on: Dec 4, 2013
 *      Author: thanh
 */

#include "KCoInfyTolerance.h"
#include "DeactivateMessage.h"
#include "NetworkTools.h"

namespace protocols {

KCoInfyTolerance::KCoInfyTolerance() {
	// TODO Auto-generated constructor stub

}

KCoInfyTolerance::~KCoInfyTolerance() {
	// TODO Auto-generated destructor stub
}
void KCoInfyTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infected = messageLink->src;
	detector->state = Inactive;
	detector->ownerNetwork->info.numberOfInactiveNodes++;
	if (detector->commonNeighbors.find(infected->id) == detector->commonNeighbors.end())
		return;
	map<long, vector<LinkPtr> >::iterator mapIt = detector->commonNeighbors.begin();
	for (; mapIt != detector->commonNeighbors.end(); mapIt++)
	{
		LinkPtr link = NetworkTools::GetLinkPtr(detector->links, mapIt->first);
		if (mapIt->first == infected->id)
			continue;
		DeactivateMessage* message = new DeactivateMessage(link, detector->ownerNetwork->currentTimeSlot);
		message->TTL = 0;
		SendMessage(link, CallbackReceiveKillingMessage, message);
	}
}

string KCoInfyTolerance::GetToleranceName()
{
	return "KCoInfy1Hop";
}

void KCoInfyTolerance::CallbackReceiveKillingMessage(void *ptr, Message* message)
{
	KCoInfyTolerance* ptrCCommon = (KCoInfyTolerance*)ptr;
	ptrCCommon->ReceiveKillingMessage(message);
}

void KCoInfyTolerance::ReceiveKillingMessage(Message* message)
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

} /* namespace generators */
