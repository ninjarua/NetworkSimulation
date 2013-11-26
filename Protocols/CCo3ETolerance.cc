/*
 * CCo3ETolerance.cc
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#include "CCo3ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCo3ETolerance::CCo3ETolerance() {
	// TODO Auto-generated constructor stub

}

CCo3ETolerance::~CCo3ETolerance() {
	// TODO Auto-generated destructor stub
}

void CCo3ETolerance::TolerateNode(LinkPtr messageLink)
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
	vector<LinkPtr> nodesInCo2 = vector<LinkPtr>();
	for (; it != messageLinkCommonNbs.end(); it++)
		CutLinkCoNEFromCoNMinus1(detector, (*it)->dest, infectedNode->id, nodesInCo2);

	it = nodesInCo2.begin();
	vector<LinkPtr> nodesInCo3 = vector<LinkPtr>();
	for (; it != nodesInCo2.end(); it++)
		CutLinkCoNEFromCoNMinus1(detector, (*it)->dest, infectedNode->id, nodesInCo3);
}

string CCo3ETolerance::GetToleranceName()
{
	return "CCo3E";
}

} /* namespace protocols */
