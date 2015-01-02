/*
 * BlacklistingTolerance.cc
 *
 *  Created on: Jun 29, 2014
 *      Author: thanhnd
 */

#include "BlacklistingTolerance.h"
#include "NetworkTools.h"
#include "CutLinkMessage.h"

namespace protocols {

BlacklistingTolerance::BlacklistingTolerance() : ToleranceBase(){
	// TODO Auto-generated constructor stub

}

BlacklistingTolerance::~BlacklistingTolerance() {
	// TODO Auto-generated destructor stub
}

string BlacklistingTolerance::GetToleranceName()
{
	return "Blacklisting";
}

void BlacklistingTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	messageLink->state = Cut;	// cut link with the infected node
	//NodePtr node = messageLink->dest;
	CutLink(messageLink);
}

void BlacklistingTolerance::SendBlacklist(NodePtr detector, NodePtr infected)
{
	vector<LinkPtr>::iterator it = detector->links.begin();
	// Cut link like in CCo1ETolerance strategy
	for (; it != detector->links.end(); it++)
	{
		// Get reverselink of *it to cut
		// It is different than CCommon because the loop here on an item of the map of commonNeighbor
		// It means that it is already common neighbor between infected (messageLink->src) and detector (messageLink->dest)
		// (*it) will be cut in the next round after sending cuttingMessage
		LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(*it);
		srcLinkToCut->state = Cut;

		vector<LinkPtr>::iterator subit = (*it)->dest->links.begin();
		//LinkPtr linkToCut = NetworkTools::GetSrcLinkPtr(infected->srcLinks, (*it)->dest->id);
		for (; subit != (*it)->dest->links.begin(); subit++)
		{
			if ((*subit)->state != Cut)
			{
				SetToBeCut(*subit);
				CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, *subit, detector->ownerNetwork->currentTimeSlot);
				cuttingMessage->cutCarrierLink = true;
				SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
			}
		}
	}
}

} /* namespace protocols */
