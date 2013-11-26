/*
 * CCommonTolerance.cc
 *
 *  Created on: Aug 28, 2013
 *      Author: thanhnd
 */

#include "CCo1ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCo1ETolerance::CCo1ETolerance() : ToleranceBase() {

}

CCo1ETolerance::~CCo1ETolerance() {

}

void CCo1ETolerance::TolerateNode(LinkPtr messageLink)
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

		// check if (*it)->dest is also neighbor of messageLink->src
		// return link from messageLink->src to (*it)->dest if they are neighbors
		LinkPtr linkToCut = NetworkTools::GetLinkPtr(messageLink->src->links, (*it)->dest->id);
		if (linkToCut != NULL && linkToCut->state != Cut)
		{
			// looking for the link from that common neighbor (*it)->dest to current node
			// then cut that link
			LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(*it);	//	NetworkTools::GetSrcLinkPtr(node->srcLinks, (*it)->dest->id);
			srcLinkToCut->state = Cut;

			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, node->ownerNetwork->currentTimeSlot);
			cuttingMessage->cutCarrierLink = true;
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}
}

string CCo1ETolerance::GetToleranceName()
{
	return "CCommon";
}

void CCo1ETolerance::CallbackReceiveCutLinkMessage(void *ptr, Message* message)
{
	CCo1ETolerance* ptrCCommon = (CCo1ETolerance*)ptr;
	ptrCCommon->ReceiveCutLinkMessage(message);
}

void CCo1ETolerance::ReceiveCutLinkMessage(Message* message)
{
	CutLinkMessage* cuttingMessage = (CutLinkMessage*)message;
	if (cuttingMessage->cutCarrierLink)
		cuttingMessage->link->state = Cut;
	if (cuttingMessage->linkToCut->state == Cut)
	{
		cuttingMessage->status = Expired;
		return;
	}
	cuttingMessage->linkToCut->state = Cut;
	//cout << cuttingMessage->linkToCut->src->id << " to " << cuttingMessage->linkToCut->dest->id << endl;
	//cout << srcLinkToCut->src->id << " to " << srcLinkToCut->dest->id << endl;
	LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(cuttingMessage->linkToCut);
	srcLinkToCut->state = Cut;
	cuttingMessage->status = Expired;
}

} /* namespace protocols */
