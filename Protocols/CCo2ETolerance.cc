/*
 * COtherBridgesTolerance.cc
 *
 *  Created on: Aug 31, 2013
 *      Author: thanhnd
 */

#include "CCo2ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCo2ETolerance::CCo2ETolerance() : ToleranceBase() {

}

CCo2ETolerance::~CCo2ETolerance() {

}

void CCo2ETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infectedNode = messageLink->src;
	vector<LinkPtr> messageLinkCommonNbs = detector->commonNeighbors[infectedNode->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	// Cut link like in CCo1ETolerance strategy
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		// Get reverselink of *it to cut
		// It is different than CCommon because the loop here on an item of the map of commonNeighbor
		// It means that it is already common neighbor between infected (messageLink->src) and detector (messageLink->dest)
		// (*it) will be cut in the next round after sending cuttingMessage
		LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(*it);
		srcLinkToCut->state = Cut;

		// get link from (*it)->dest to infectedNode to cut
		LinkPtr linkToCut = NetworkTools::GetSrcLinkPtr(infectedNode->srcLinks, (*it)->dest->id);
		if (linkToCut->state != Cut)
		{
			SetToBeCut(linkToCut);
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, detector->ownerNetwork->currentTimeSlot);
			cuttingMessage->cutCarrierLink = true;
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}

	it = messageLinkCommonNbs.begin();
	vector<LinkPtr> nodeInCo2 = vector<LinkPtr>();
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		CutLinkCoNELast(detector, (*it)->dest, infectedNode->id, nodeInCo2);
	}
}

string CCo2ETolerance::GetToleranceName()
{
	return "CCo2E";
}

} /* namespace protocols */
