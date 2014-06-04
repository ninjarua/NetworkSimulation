/*
 * CCoAllETolerance.cc
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#include "CCoENewTolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCoENewTolerance::CCoENewTolerance() {

}

CCoENewTolerance::~CCoENewTolerance() {

}

void CCoENewTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infected = messageLink->src;
	CutLinkCo1(detector, infected);

	// for each neighbor having id = mapIt->first (called mapIt) of messageLink->dest (detector)
	// find neighbors that is common neighbor between detector and mapIt
	//	but is not neighbor of messageLink->src (infected node)
	vector<LinkPtr> newLinks = vector<LinkPtr>();
	map<long, vector<LinkPtr> >::iterator mapIt = detector->commonNeighbors.begin();
	for (; mapIt != detector->commonNeighbors.end(); mapIt++)
	{
		if (mapIt->first == infected->id)
			continue;
		bool have = false;
		vector<LinkPtr>::iterator nbIt = mapIt->second.begin();
		for (; nbIt != mapIt->second.end(); nbIt++)
		{
			// check if nbIt is neighbor of infected node or not
			if (NetworkTools::ContainNode(detector->commonNeighbors[infected->id], (*nbIt)->dest))
			{
				LinkPtr linkToCut = NetworkTools::GetLinkPtr((*nbIt)->dest->links, mapIt->first);
				SetToBeCut(linkToCut);
				CutLinkMessage* cuttingMessage = new CutLinkMessage(*nbIt, linkToCut, detector->ownerNetwork->currentTimeSlot);
				cuttingMessage->cutCarrierLink = true;
				SendMessage(*nbIt, CallbackReceiveCutLinkMessage, cuttingMessage);
				have = true;
			}
		}
		if (have == true)
		{
			LinkPtr newLink = NetworkTools::GetLinkPtr(detector->links, mapIt->first);
			newLinks.push_back(newLink);
		}
	}

	vector<LinkPtr> new2Links = vector<LinkPtr>();
	for (vector<LinkPtr>::iterator it = newLinks.begin(); it != newLinks.end(); it++)
	{
		CutLinkCoNEFromCoNMinus1(detector, (*it)->dest, infected->id, new2Links);
	}
}

string CCoENewTolerance::GetToleranceName()
{
	return "CCoENew";
}

} /* namespace protocols */
