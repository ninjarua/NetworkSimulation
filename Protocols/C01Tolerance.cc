/*
 * C01Tolerance.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "C01Tolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace generators {

C01Tolerance::C01Tolerance() : ToleranceBase() {

}

C01Tolerance::~C01Tolerance() {

}

string C01Tolerance::GetToleranceName()
{
	return "C1";
}

void C01Tolerance::TolerateNode(LinkPtr messageLink)
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
		if (linkToCut != NULL)
		{
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, node->ownerNetwork->currentTimeSlot);
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}
}
void C01Tolerance::CallbackReceiveCutLinkMessage(void *ptr, Message* message)
{
	C01Tolerance* ptrC01 = (C01Tolerance*)ptr;
	ptrC01->ReceiveCutLinkMessage(message);
}

void C01Tolerance::ReceiveCutLinkMessage(Message* message)
{
	CutLinkMessage* cuttingMessage = (CutLinkMessage*)message;
	cuttingMessage->linkToCut->state = Cut;
	LinkPtr srcLinkToCut = NetworkTools::GetSrcLinkPtr(cuttingMessage->linkToCut->src->srcLinks,
									cuttingMessage->linkToCut->dest->id);
	srcLinkToCut->state = Cut;
}

} /* namespace generators */
