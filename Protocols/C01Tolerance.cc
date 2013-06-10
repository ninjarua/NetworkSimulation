/*
 * C01Tolerance.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "C01Tolerance.h"

namespace generators {

C01Tolerance::C01Tolerance() : ToleranceBase() {

}

C01Tolerance::~C01Tolerance() {

}

string C01Tolerance::GetToleranceName()
{
	return "C1";
}

void C01Tolerance::TolerateNode(NodePtr node, NodePtr byzantine)
{
	ToleranceBase::TolerateNode(node, byzantine);
	node->ownerNetwork->info.numberOfInactiveNodes++;
	node->detectedByzantines.insert(byzantine);
	node->disconnectedNodes.insert(byzantine);
}

} /* namespace generators */
