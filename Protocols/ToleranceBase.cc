/*
 * ToleranceBase.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ToleranceBase.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

ToleranceBase::ToleranceBase() {

}

ToleranceBase::~ToleranceBase() {

}

string ToleranceBase::GetToleranceName()
{
	return "Base";
}

void ToleranceBase::TolerateNode(LinkPtr link)
{
}

void ToleranceBase::CutLink(LinkPtr linkToCut)
{
	linkToCut->state = Cut;
	// Find reverseLink to cut
	LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(linkToCut);
	srcLinkToCut->state = Cut;
}

void ToleranceBase::SetToBeCut(LinkPtr linkToCut)
{
	linkToCut->state = SetToCut;
	// Find reverseLink to cut
	LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(linkToCut);
	srcLinkToCut->state = SetToCut;
}

void ToleranceBase::CallbackReceiveCutLinkMessage(void *ptr, Message* message)
{
	ToleranceBase* ptrCCommon = (ToleranceBase*)ptr;
	ptrCCommon->ReceiveCutLinkMessage(message);
}

void ToleranceBase::ReceiveCutLinkMessage(Message* message)
{
	CutLinkMessage* cuttingMessage = (CutLinkMessage*)message;
	if (cuttingMessage->cutCarrierLink)
		cuttingMessage->link->state = Cut;
	if (cuttingMessage->linkToCut->state == Cut)
	{
		cuttingMessage->status = Expired;
		return;
	}
	CutLink(cuttingMessage->linkToCut);
	cuttingMessage->status = Expired;
}

void ToleranceBase::CutLinkCoNEFromCoNMinus1(NodePtr detector, NodePtr nodeInCoNMinus1, int infectedId, vector<LinkPtr>& nodesInCoN)
{
	vector<LinkPtr> lstCoN = detector->commonNeighbors[nodeInCoNMinus1->id];
	vector<LinkPtr>::iterator itCoN = lstCoN.begin();
	//itCo2 is link from detector to commonNeighbor with it->dest.
	for (; itCoN != lstCoN.end(); itCoN++)
	{
		if ((*itCoN)->dest->id == infectedId)
			continue;
		// Get link from (*itCo2)->dest to (*it)->dest;
		LinkPtr linkCoNEToCut = NetworkTools::GetLinkPtr((*itCoN)->dest->links, nodeInCoNMinus1->id);
		if (linkCoNEToCut->state != Active) // if this link is SetToCut or Cut.
			continue;
		SetToBeCut(linkCoNEToCut);
		CutLinkMessage* cuttingCoN = new CutLinkMessage(*itCoN, linkCoNEToCut, detector->ownerNetwork->currentTimeSlot);
		cuttingCoN->cutCarrierLink = false;
		SendMessage(*itCoN, CallbackReceiveCutLinkMessage, cuttingCoN);
		nodesInCoN.push_back(*itCoN);
	}
}

} /* namespace protocols */
