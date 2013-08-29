/*
 * C01Tolerance.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "CSelfTolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace generators {

CSelfTolerance::CSelfTolerance() : ToleranceBase() {

}

CSelfTolerance::~CSelfTolerance() {

}

string CSelfTolerance::GetToleranceName()
{
	return "C1";
}

void CSelfTolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	messageLink->state = Cut;	// cut link with the infected node
	NodePtr node = messageLink->dest;
	LinkPtr linkToCut = NetworkTools::GetLinkPtr(node->links, messageLink->src->id);
	linkToCut->state = Cut;
}

} /* namespace generators */
