/*
 * COtherBridgesTolerance.cc
 *
 *  Created on: Aug 31, 2013
 *      Author: thanhnd
 */

#include "COtherBridgesTolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

COtherBridgesTolerance::COtherBridgesTolerance() : ToleranceBase() {

}

COtherBridgesTolerance::~COtherBridgesTolerance() {

}

void COtherBridgesTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	messageLink->state = Cut;
	NodePtr node = messageLink->dest;
	vector<LinkPtr> messageLinkCommonNbs = node->commonNeighbors[messageLink->src->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		// Get reverselink of *it to cut
		// It is different than CCommon because the loop here on an item of the map of commonNeighbor
		// It means that it is already common neighbor between infected (messageLink->src) and detector (messageLink->dest)
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

string COtherBridgesTolerance::GetToleranceName()
{
	return "CBridges";
}

void COtherBridgesTolerance::CallbackReceiveCutLinkMessage(void *ptr, Message* message)
{
	COtherBridgesTolerance* ptrCCommon = (COtherBridgesTolerance*)ptr;
	ptrCCommon->ReceiveCutLinkMessage(message);
}

void COtherBridgesTolerance::ReceiveCutLinkMessage(Message* message)
{
	CutLinkMessage* cuttingMessage = (CutLinkMessage*)message;
	if (cuttingMessage->cutCarrierLink)
		cuttingMessage->link->state = Cut;
	if (cuttingMessage->linkToCut->state == Cut)
	{
		cuttingMessage->status = Expired;
		return;
	}
	cuttingMessage->linkToCut->state = Cut;
	//cout << cuttingMessage->linkToCut->src->id << " to " << cuttingMessage->linkToCut->dest->id << endl;
	LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(cuttingMessage->linkToCut);
	//cout << srcLinkToCut->src->id << " to " << srcLinkToCut->dest->id << endl;
	srcLinkToCut->state = Cut;
	cuttingMessage->status = Expired;
}

} /* namespace protocols */
