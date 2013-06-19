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
	return "C1K03";
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
		if ((*it)->dest->state == Infected || (*it)->dest->state == Inactive)
			continue;
		if ((*it)->dest == link->src)
			(*it)->state = Cut;
		list<LinkPtr> commonNeighbors = GetCommonNeighborsExcept((*it)->dest, link->src, node);
		if (commonNeighbors.begin() != commonNeighbors.end())
		{
//			DeactivateMessage* message = new DeactivateMessage((*it), node->ownerNetwork->currentTimeSlot);
//			message->TTL = 0;
//			SendMessage((*it), CallbackReceiveDeactivateMessage, message);
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
		node->state = Inactive;
		node->ownerNetwork->info.numberOfInactiveNodes++;
	}
	message->status = Expired;
}

void CxHopTolerance::CallbackReceiveDeactivateMessage(void* ptr, Message* message)
{
	CxHopTolerance* ptrC1K3 = (CxHopTolerance*)ptr;
	ptrC1K3->ReceiveDeactivateMessage(message);
}

list<LinkPtr> CxHopTolerance::GetCommonNeighborsExcept(NodePtr n1, NodePtr n2, NodePtr exception)
{
	list<LinkPtr> commonNodes = list<LinkPtr>();
	vector<LinkPtr>::iterator it = n1->links.begin();
	// for each neighbor of n1, check if it is in list neighbors of n2
	for (; it != n1->links.end(); it++)
		if ((*it)->dest->id != exception->id && ContainNode(n2->links, (*it)->dest))
		{
			commonNodes.push_back(*it);
		}
	return commonNodes;
}

bool CxHopTolerance::ContainNode(vector<LinkPtr> links, NodePtr node)
{
	int size = links.size();
	int left = 0;
	int right = size - 1;
	int mid;
	while (left <= right)
	{
		mid = (left + right)/2;
		LinkPtr linkMid = links[mid];
		if (node->id > linkMid->dest->id)
			left = mid + 1;
		else if(node->id < linkMid->dest->id)
			right = mid - 1;
		else
			return true;
	}
	return false;
}

} /* namespace protocols */
