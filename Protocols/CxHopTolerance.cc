/*
 * CxHopTolerance.cc
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#include "CxHopTolerance.h"
#include "NetworkTools.h"
#include "DeactivateMessage.h"

namespace protocols {

CxHopTolerance::CxHopTolerance() {

}

CxHopTolerance::~CxHopTolerance() {

}

string CxHopTolerance::GetToleranceName()
{
	return "CxHop";
}

void CxHopTolerance::TolerateNode(LinkPtr link)
{
	ToleranceBase::TolerateNode(link);
	link->state = Cut;
	//node->disconnectedNodes.insert(byzantine);
	NodePtr node = link->dest;
	vector<LinkPtr>::iterator it = node->links.begin();
	for (; it != node->links.end(); it++)
	{
		if ((*it)->state == Cut || (*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		if ((*it)->dest == link->src)
			(*it)->state = Cut;
		Link2Hop* link2Hop = GetCommonNeighborsExcept((*it)->dest, link->src, node);
		if (link2Hop != NULL)
		{
			DeactivateMessage* message = new DeactivateMessage((*it), link2Hop, node->ownerNetwork->currentTimeSlot);
			message->TTL = 1; // is not used yet, because the receiver of deactivate message does not forward message.
			SendMessage((*it), CallbackReceiveDeactivateMessage, message);
		}
	}
}

void CxHopTolerance::ReceiveDeactivateMessage(Message* message)
{
	NodePtr node = message->link->dest;
	if (node->state == Infected)
		return;
	if (node->state == Sane)
	{
		DeactivateMessage* deactivateMessage = (DeactivateMessage*)message;
		Link2Hop* link2 = deactivateMessage->link2Hop;
		int size = link2->mids.size();
		for(int i = 0; i < size; i++)
		{
			int mid_i = deactivateMessage->link2Hop->mids[i];
			if (mid_i != deactivateMessage->link->src->id)
			{
				NetworkTools::GetLinkPtr(node->links, mid_i)->state = Cut;
			}
		}
	}
	message->status = Expired;
}

void CxHopTolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	CxHopTolerance* ptrC1K3 = (CxHopTolerance*)ptr;
	ptrC1K3->ReceiveDeactivateMessage(message);
}

Link2Hop* CxHopTolerance::GetCommonNeighborsExcept(NodePtr n1, NodePtr n2, NodePtr exception)
{
	Link2Hop* link2Hop = LookingForLink2Hop(n1->links2Hop, n2);
	if (link2Hop != NULL && link2Hop->mids.size() > 1)
	{
		return link2Hop;//vector<NodePtr>::iterator it = link2Hop->mids;
	}
	return NULL;
}

Link2Hop* CxHopTolerance::LookingForLink2Hop(vector<Link2Hop*> links2Hop, NodePtr node)
{
	int size = links2Hop.size();
	int left = 0;
	int right = size - 1;
	int mid;
	while (left <= right)
	{
		mid = (left + right)/2;
		Link2Hop* linkMid = links2Hop[mid];
		if (node->id > linkMid->dest->id)
			left = mid + 1;
		else if(node->id < linkMid->dest->id)
			right = mid - 1;
		else
			return linkMid;
	}
	return NULL;
}

} /* namespace protocols */
