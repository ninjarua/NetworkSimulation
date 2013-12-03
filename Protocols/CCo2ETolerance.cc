/*
 * COtherBridgesTolerance.cc
 *
 *  Created on: Aug 31, 2013
 *      Author: thanhnd
 */

#include "CCo2ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCo2ETolerance::CCo2ETolerance() : ToleranceBase() {

}

CCo2ETolerance::~CCo2ETolerance() {

}

void CCo2ETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infected = messageLink->src;
	CutLinkCo1(detector, infected);

	vector<LinkPtr> messageLinkCommonNbs = detector->commonNeighbors[infected->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	vector<LinkPtr> nodeInCo2 = vector<LinkPtr>();
	for (; it != messageLinkCommonNbs.end(); it++)
	{
		CutLinkCoNEFromCoNMinus1(detector, (*it)->dest, infected->id, nodeInCo2);
	}
}

string CCo2ETolerance::GetToleranceName()
{
	return "CCo2E";
}

} /* namespace protocols */
