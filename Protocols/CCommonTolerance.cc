/*
 * CCommonTolerance.cc
 *
 *  Created on: Aug 28, 2013
 *      Author: thanhnd
 */

#include "CCommonTolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCommonTolerance::CCommonTolerance() : ToleranceBase() {

}

CCommonTolerance::~CCommonTolerance() {

}

void CCommonTolerance::TolerateNode(LinkPtr messageLink)
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
			LinkPtr srcLinkToCut = NetworkTools::GetSrcLinkPtr(node->srcLinks, (*it)->dest->id);
			srcLinkToCut->state = Cut;

			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, node->ownerNetwork->currentTimeSlot);
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}
}

string CCommonTolerance::GetToleranceName()
{
	return "CCommon";
}

void CCommonTolerance::CallbackReceiveCutLinkMessage(void *ptr, Message* message)
{
	CCommonTolerance* ptrC01 = (CCommonTolerance*)ptr;
	ptrC01->ReceiveCutLinkMessage(message);
}

void CCommonTolerance::ReceiveCutLinkMessage(Message* message)
{
	message->link->state = Cut;
	CutLinkMessage* cuttingMessage = (CutLinkMessage*)message;
	if (cuttingMessage->linkToCut->state == Cut)
	{
		cuttingMessage->status = Expired;
		return;
	}
	cuttingMessage->linkToCut->state = Cut;
	//cout << cuttingMessage->linkToCut->src->id << " to " << cuttingMessage->linkToCut->dest->id << endl;
	LinkPtr srcLinkToCut = NetworkTools::GetSrcLinkPtr(cuttingMessage->linkToCut->src->srcLinks,
									cuttingMessage->linkToCut->dest->id);
	//cout << srcLinkToCut->src->id << " to " << srcLinkToCut->dest->id << endl;
	srcLinkToCut->state = Cut;
	cuttingMessage->status = Expired;
}

} /* namespace protocols */
