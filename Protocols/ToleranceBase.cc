/*
 * ToleranceBase.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ToleranceBase.h"
#include "NetworkTools.h"

namespace protocols {

ToleranceBase::ToleranceBase() {

}

ToleranceBase::~ToleranceBase() {

}

string ToleranceBase::GetToleranceName()
{
	return "Base";
}

void ToleranceBase::TolerateNode(LinkPtr link)
{
}

void ToleranceBase::CutLink(LinkPtr linkToCut)
{
	linkToCut->state = Cut;
	// Find reverseLink to cut
	LinkPtr srcLinkToCut = NetworkTools::GetReverseLink(linkToCut);
	srcLinkToCut->state = Cut;
}

} /* namespace protocols */
