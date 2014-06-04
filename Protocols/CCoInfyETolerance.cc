/*
 * CCoAllETolerance.cc
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#include "CCoInfyETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCoInfyETolerance::CCoInfyETolerance() {

}

CCoInfyETolerance::~CCoInfyETolerance() {

}

void CCoInfyETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infected = messageLink->src;
	CutLinkCo1(detector, infected);

	if (detector->commonNeighbors.find(infected->id) == detector->commonNeighbors.end())
		return;
	map<long, vector<LinkPtr> >::iterator mapIt = detector->commonNeighbors.begin();
	for (; mapIt != detector->commonNeighbors.end(); mapIt++)
	{
		if (mapIt->first == infected->id)
			continue;
		vector<LinkPtr>::iterator nbIt = mapIt->second.begin();
		for (; nbIt != mapIt->second.end(); nbIt++)
		{
			if ((*nbIt)->state==Cut)
				continue;
			// Get reverse link of carrier link to cut
			LinkPtr srcnbIt = NetworkTools::GetReverseLink(*nbIt);
			srcnbIt->state = Cut;

			LinkPtr linkToCut = NetworkTools::GetLinkPtr((*nbIt)->dest->links, mapIt->first);
			if (linkToCut->state == Cut)
				continue;
			SetToBeCut(linkToCut);
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*nbIt, linkToCut, detector->ownerNetwork->currentTimeSlot);
			cuttingMessage->cutCarrierLink = true;
			SendMessage(*nbIt, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}
}

string CCoInfyETolerance::GetToleranceName()
{
	return "CCoAllE";
}

} /* namespace protocols */
