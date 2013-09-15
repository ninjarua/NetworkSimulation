/*
 * KOtherBridgesTolerance.cc
 *
 *  Created on: Sep 8, 2013
 *      Author: thanhnd
 */

#include "KOtherBridgesTolerance.h"
#include "NetworkTools.h"
#include "DeactivateMessage.h"

namespace protocols {

KOtherBridgesTolerance::KOtherBridgesTolerance() : ToleranceBase() {

}

KOtherBridgesTolerance::~KOtherBridgesTolerance() {

}

void KOtherBridgesTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr node = messageLink->dest;
	vector<LinkPtr> messageLinkCommonNbs = node->commonNeighbors[messageLink->src->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	// Cut link like in CCommonTolerance strategy
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		DeactivateMessage* killingMessage = new DeactivateMessage(*it, node->ownerNetwork->currentTimeSlot);
		SendMessage(*it, CallbackReceiveKillingMessage, killingMessage);
	}

	// for each neighbor having id = mapIt->first (called mapIt) of messageLink->dest (detector)
	// find neighbors that is common neighbor between detector and mapIt
	// but is not neighbor of messageLink->src (infected node)
	map<int, vector<LinkPtr> >::iterator mapIt = node->commonNeighbors.begin();
	for (; mapIt != node->commonNeighbors.end(); mapIt++)
	{
		if (mapIt->first == messageLink->src->id)
			continue;
		vector<LinkPtr>::iterator nbIt = mapIt->second.begin();
		for (; nbIt != mapIt->second.end(); nbIt++)
		{
			// check if nbIt is neighbor of infected node or not
			if (!NetworkTools::ContainNode(node->commonNeighbors[messageLink->src->id], (*nbIt)->dest))
			// if not
			{
				DeactivateMessage* killingMessage = new DeactivateMessage(*nbIt, node->ownerNetwork->currentTimeSlot);
				SendMessage(*nbIt, CallbackReceiveKillingMessage, killingMessage);
			}
		}
	}
}

string KOtherBridgesTolerance::GetToleranceName()
{
	return "KBridges";
}

void KOtherBridgesTolerance::CallbackReceiveKillingMessage(void *ptr, Message* message)
{
	KOtherBridgesTolerance* ptrCCommon = (KOtherBridgesTolerance*)ptr;
	ptrCCommon->ReceiveKillingMessage(message);
}

void KOtherBridgesTolerance::ReceiveKillingMessage(Message* message)
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
