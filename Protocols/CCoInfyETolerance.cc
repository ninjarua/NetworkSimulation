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
	vector<LinkPtr> messageLinkCommonNbs = detector->commonNeighbors[infected->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	// Cut link like in CCommonTolerance strategy
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		// Get reverselink of *it to cut
		// It is different than CCommon because the loop here on an item of the map of commonNeighbor
		// It means that it is already common neighbor between infected (messageLink->src) and detector (messageLink->dest)
		// (*it) will be cut when sending cuttingMessage
		LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(*it);
		srcLinkToCut->state = Cut;

		// get link from (*it)->dest to messageLink->src to cut
		LinkPtr linkToCut = NetworkTools::GetSrcLinkPtr(infected->srcLinks, (*it)->dest->id);
		if (linkToCut->state != Cut)
		{
			SetToBeCut(linkToCut);
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, detector->ownerNetwork->currentTimeSlot);
			cuttingMessage->cutCarrierLink = true;
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}

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
			if ((*nbIt)->dest->id==infected->id)
				continue;
			LinkPtr linkToCut = NetworkTools::GetLinkPtr((*nbIt)->dest->links, mapIt->first);
			if (linkToCut->state != Active)
				continue;
			SetToBeCut(linkToCut);
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*nbIt, linkToCut, detector->ownerNetwork->currentTimeSlot);
			cuttingMessage->cutCarrierLink = true;

			// Get reverse link of carrier link to cut
			LinkPtr srcnbIt = NetworkTools::GetReverseLink(*nbIt);
			srcnbIt->state = Cut;
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
