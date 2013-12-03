/*
 * CCo3ETolerance.cc
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#include "CCo3ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCo3ETolerance::CCo3ETolerance() {
	// TODO Auto-generated constructor stub

}

CCo3ETolerance::~CCo3ETolerance() {
	// TODO Auto-generated destructor stub
}

void CCo3ETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	CutLink(messageLink);

	NodePtr detector = messageLink->dest;
	NodePtr infected = messageLink->src;
	CutLinkCo1(detector, infected);

	vector<LinkPtr> messageLinkCommonNbs = detector->commonNeighbors[infected->id];
	vector<LinkPtr>::iterator it = messageLinkCommonNbs.begin();
	vector<LinkPtr> nodesInCo2 = vector<LinkPtr>();
	for (; it != messageLinkCommonNbs.end(); it++)
		CutLinkCoNEFromCoNMinus1(detector, (*it)->dest, infected->id, nodesInCo2);

	it = nodesInCo2.begin();
	vector<LinkPtr> nodesInCo3 = vector<LinkPtr>();
	for (; it != nodesInCo2.end(); it++)
		CutLinkCoNEFromCoNMinus1(detector, (*it)->dest, infected->id, nodesInCo3);
}

string CCo3ETolerance::GetToleranceName()
{
	return "CCo3E";
}

} /* namespace protocols */
