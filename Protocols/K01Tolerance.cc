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

void K01Tolerance::TolerateNode(NodePtr node, NodePtr byzantine)
{
	ToleranceBase::TolerateNode(node, byzantine);
	node->state = Inactive;
	node->ownerNetwork->info.numberOfInactiveNodes++;
	//node->ownerNetwork->info.listDetectors.push_back(node);
}

} /* namespace generators */
