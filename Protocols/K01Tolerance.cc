/*
 * K01Tolerance.cc
 *
 *  Created on: Jun 7, 2013
 *      Author: thanhnd
 */

#include "K01Tolerance.h"

namespace protocols {

K01Tolerance::K01Tolerance() : ToleranceBase() {
	// TODO Auto-generated constructor stub

}

K01Tolerance::~K01Tolerance() {
	// TODO Auto-generated destructor stub
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
	node->detectedByzantines.insert(byzantine);
	node->disconnectedNodes.insert(byzantine);
}

} /* namespace generators */
