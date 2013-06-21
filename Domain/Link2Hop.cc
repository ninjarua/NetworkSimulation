/*
 * Link2Hop.cc
 *
 *  Created on: Jun 18, 2013
 *      Author: thanhnd
 */

#include "Link2Hop.h"

namespace domain {

Link2Hop::Link2Hop(Node* d, Node* mid) {
//	src = s;
	dest = d;
	mids = vector<Link2Hop*>();
	mids.push_back(mid);
}

Link2Hop::~Link2Hop() {
	// TODO Auto-generated destructor stub
}

} /* namespace domain */
