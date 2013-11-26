/*
 * CCoAllETolerance.cc
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#include "CCoInfyETolerance.h"

namespace protocols {

CCoInfyETolerance::CCoInfyETolerance() {

}

CCoInfyETolerance::~CCoInfyETolerance() {

}

void CCoInfyETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr node = messageLink->dest;
	vector<LinkPtr> messageLinkCommonNbs = node->commonNeighbors[messageLink->src->id];
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
		LinkPtr linkToCut = NetworkTools::GetSrcLinkPtr(messageLink->src->srcLinks, (*it)->dest->id);
		if (linkToCut->state != Cut)
		{
			CutLinkMessage* cuttingMessage = new CutLinkMessage(*it, linkToCut, node->ownerNetwork->currentTimeSlot);
			cuttingMessage->cutCarrierLink = true;
			SendMessage(*it, CallbackReceiveCutLinkMessage, cuttingMessage);
		}
	}

	// for each neighbor having id = mapIt->first (called mapIt) of messageLink->dest (detector)
	// find neighbors that is common neighbor between detector and mapIt
	//	but is not neighbor of messageLink->src (infected node)
	map<int, vector<LinkPtr> >::iterator mapIt = node->commonNeighbors.begin();
	for (; mapIt != node->commonNeighbors.end(); mapIt++)
	{
		if (mapIt->first == messageLink->src->id)
			continue;
		vector<LinkPtr>::iterator nbIt = mapIt->second.begin();
		for (; nbIt != mapIt->second.end(); nbIt++)
		{
			// check if nbIt is neighbor of infected node or not
			if (!NetworkTools::ContainNode(node->commonNeighbors[messageLink->src->id], (*nbIt)->dest))
			{
				LinkPtr linkToCut = NetworkTools::GetLinkPtr((*nbIt)->dest->links, mapIt->first);
				CutLinkMessage* cuttingMessage = new CutLinkMessage(*nbIt, linkToCut, node->ownerNetwork->currentTimeSlot);
				cuttingMessage->cutCarrierLink = false;
				SendMessage(*nbIt, CallbackReceiveCutLinkMessage, cuttingMessage);
			}
		}
	}
}

string CCoInfyETolerance::GetToleranceName()
{
	return "CCoAllE";
}

} /* namespace protocols */
