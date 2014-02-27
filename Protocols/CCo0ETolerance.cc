/*
 * C01Tolerance.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "CCo0ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace generators {

CCo0ETolerance::CCo0ETolerance() : ToleranceBase() {

}

CCo0ETolerance::~CCo0ETolerance() {

}

string CCo0ETolerance::GetToleranceName()
{
	return "CCo0E";
}

void CCo0ETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	messageLink->state = Cut;	// cut link with the infected node
	NodePtr node = messageLink->dest;
	CutLink(messageLink);
}

} /* namespace generators */
