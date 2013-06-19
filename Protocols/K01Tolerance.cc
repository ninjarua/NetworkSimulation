/*
 * K01Tolerance.cc
 *
 *  Created on: Jun 7, 2013
 *      Author: thanhnd
 */

#include "K01Tolerance.h"

namespace protocols {

K01Tolerance::K01Tolerance() : ToleranceBase() {

}

K01Tolerance::~K01Tolerance() {

}

string K01Tolerance::GetToleranceName()
{
	return "K1";
}

void K01Tolerance::TolerateNode(LinkPtr link)
{
	ToleranceBase::TolerateNode(link);
	link->dest->state = Inactive;
	link->dest->ownerNetwork->info.numberOfInactiveNodes++;
	//node->ownerNetwork->info.listDetectors.push_back(node);
}

} /* namespace generators */
