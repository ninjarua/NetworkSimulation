/*
 * K01Tolerance.cc
 *
 *  Created on: Jun 7, 2013
 *      Author: thanhnd
 */

#include "KSelfTolerance.h"

namespace protocols {

KSelfTolerance::KSelfTolerance() : ToleranceBase() {

}

KSelfTolerance::~KSelfTolerance() {

}

string KSelfTolerance::GetToleranceName()
{
	return "K1";
}

void KSelfTolerance::TolerateNode(LinkPtr link)
{
	ToleranceBase::TolerateNode(link);
	link->dest->state = Inactive;
	link->dest->ownerNetwork->info.numberOfInactiveNodes++;
	//node->ownerNetwork->info.listDetectors.push_back(node);
}

} /* namespace generators */
