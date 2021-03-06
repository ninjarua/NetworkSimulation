/*
 * KselfCCommon.cc
 *
 *  Created on: Aug 29, 2013
 *      Author: thanhnd
 */

#include "KSelfCCo1ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

KSelfCCo1ETolerance::KSelfCCo1ETolerance() : ToleranceBase() {

}

KSelfCCo1ETolerance::~KSelfCCo1ETolerance() {

}

void KSelfCCo1ETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
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
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, node->ownerNetwork->currentTimeSlot);
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;
}

string KSelfCCo1ETolerance::GetToleranceName()
{
	return "KSelfCCommon";
}

void KSelfCCo1ETolerance::CallbackReceiveCutLinkMessage(void *ptr, Message* message)
{
	KSelfCCo1ETolerance* ptrC01 = (KSelfCCo1ETolerance*)ptr;
	ptrC01->ReceiveCutLinkMessage(message);
}

void KSelfCCo1ETolerance::ReceiveCutLinkMessage(Message* message)
{
	CutLinkMessage* cuttingMessage = (CutLinkMessage*)message;
	if (cuttingMessage->linkToCut->state == Cut)
	{
		cuttingMessage->status = Expired;
		return;
	}
	cuttingMessage->linkToCut->state = Cut;
	//cout << cuttingMessage->linkToCut->src->id << " to " << cuttingMessage->linkToCut->dest->id << endl;
	LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(cuttingMessage->linkToCut);
	//cout << srcLinkToCut->src->id << " to " << srcLinkToCut->dest->id << endl;
	srcLinkToCut->state = Cut;
	cuttingMessage->status = Expired;
}

} /* namespace protocols */
