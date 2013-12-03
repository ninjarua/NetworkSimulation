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

	// for each neighbor having id = mapIt->first (called mapIt) of messageLink->dest (detector)
	// find neighbors that is common neighbor between detector and mapIt
	//	but is not neighbor of messageLink->src (infected node)
	if (detector->commonNeighbors.find(infected->id) == detector->commonNeighbors.end())
		return;
	map<int, vector<LinkPtr> >::iterator mapIt = detector->commonNeighbors.begin();
	for (; mapIt != detector->commonNeighbors.end(); mapIt++)
	{
		if (mapIt->first == infected->id)
			continue;
		vector<LinkPtr>::iterator nbIt = mapIt->second.begin();
		for (; nbIt != mapIt->second.end(); nbIt++)
		{
			// check if nbIt is neighbor of infected node or not
			//if (!NetworkTools::ContainNode(detector->commonNeighbors[infected->id], (*nbIt)->dest))
			// if it check having ! --> not have infected as neighbor --> !S1 --> no cut node in S1 --> CCoInfy
			// if it check no having ! --> have infected as neighbor --> S1 --> cut links with node in S1 --> CCo2
			//{
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
			//}
		}
	}
}

string CCoInfyETolerance::GetToleranceName()
{
	return "CCoAllE";
}

} /* namespace protocols */
