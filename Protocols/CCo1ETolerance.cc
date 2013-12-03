/*
 * CCommonTolerance.cc
 *
 *  Created on: Aug 28, 2013
 *      Author: thanhnd
 */

#include "CCo1ETolerance.h"
#include "CutLinkMessage.h"
#include "NetworkTools.h"

namespace protocols {

CCo1ETolerance::CCo1ETolerance() : ToleranceBase() {

}

CCo1ETolerance::~CCo1ETolerance() {

}

void CCo1ETolerance::TolerateNode(LinkPtr messageLink)
{
	ToleranceBase::TolerateNode(messageLink);
	messageLink->state = Cut;

	CutLinkCo1(messageLink->dest, messageLink->src);

}

string CCo1ETolerance::GetToleranceName()
{
	return "CCo1E";
}
} /* namespace protocols */
