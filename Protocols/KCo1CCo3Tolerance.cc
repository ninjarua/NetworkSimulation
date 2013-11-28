/*
 * KCo1CCo3Tolerance.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: thanhnd
 */

#include <KCo1CCo3Tolerance.h>
#include "DeactivateMessage.h"

namespace protocols {

KCo1CCo3Tolerance::KCo1CCo3Tolerance() : ToleranceBase() {

}

KCo1CCo3Tolerance::~KCo1CCo3Tolerance() {

}

void KCo1CCo3Tolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infected = messageLink->src;
	vector<LinkPtr> messageLinkCommonNbs = detector->commonNeighbors[infected->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	// Cut link like in CCommonTolerance strategy
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		if ((*it)->state == Cut || (*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		(*it)->dest->state = ToBeKilled;
		DeactivateMessage* killingMessage = new DeactivateMessage(*it, detector->ownerNetwork->currentTimeSlot);
		SendMessage(*it, CallbackReceiveKillingMessage, killingMessage);
	}

	it = messageLinkCommonNbs.begin();
	vector<LinkPtr> nodesInCo2 = vector<LinkPtr>();
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		vector<LinkPtr> lstCoN = detector->commonNeighbors[(*it)->dest->id];
		vector<LinkPtr>::iterator itCoN = lstCoN.begin();
		for (; itCoN != lstCoN.end(); itCoN++)
		{
			NodeState nodeState = (*itCoN)->dest->state;
			if ((*itCoN)->state == Cut || nodeState == Infected || nodeState == Inactive || nodeState == ToBeKilled)
				continue;
			(*itCoN)->dest->state = ToBeKilled;
			DeactivateMessage* killingMessage = new DeactivateMessage(*itCoN, detector->ownerNetwork->currentTimeSlot);
			SendMessage(*itCoN, CallbackReceiveKillingMessage, killingMessage);

			nodesInCo2.push_back(*itCoN);
		}
	}

	it = nodesInCo2.begin();
	vector<LinkPtr> nodesInCo3 = vector<LinkPtr>();
	for (; it != nodesInCo2.end(); it++)
		CutLinkCoNELast(detector, (*it)->dest, infected->id, nodesInCo3);
}

string KCo1CCo3Tolerance::GetToleranceName()
{
	return "KCo1CCo3";
}

void KCo1CCo3Tolerance::CallbackReceiveKillingMessage(void *ptr, Message* message)
{
	KCo1CCo3Tolerance* ptrCommon = (KCo1CCo3Tolerance*)ptr;
	ptrCommon->ReceiveKillingMessage(message);
}

void KCo1CCo3Tolerance::ReceiveKillingMessage(Message* message)
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
