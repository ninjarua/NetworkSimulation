/*
 * Link2Hop.cc
 *
 *  Created on: Jun 18, 2013
 *      Author: thanhnd
 */

#include "Link2Hop.h"

namespace domain {

Link2Hop::Link2Hop(Node* d, int mid_id) {
//	src = s;
	dest = d;
	mids = vector<int>();
	mids.push_back(mid_id);
}

Link2Hop::Link2Hop(const Link2Hop& copy)
{
	dest = copy.dest;
	mids = copy.mids;
}

Link2Hop::~Link2Hop() {
	mids.clear();
}

} /* namespace domain */
