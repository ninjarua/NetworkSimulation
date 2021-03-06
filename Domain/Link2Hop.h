/*
 * Link2Hop.h
 *
 *  Created on: Jun 18, 2013
 *      Author: thanhnd
 */

#ifndef LINK2HOP_H_
#define LINK2HOP_H_
#include "stdafx.h"

#include <vector>

namespace domain {
class Node;
class Link2Hop {
public:
	Node* dest;
	vector<int> mids;
	Link2Hop(Node* d, int mid_id);
	Link2Hop(const Link2Hop& copy);
	virtual ~Link2Hop();
};

} /* namespace domain */
#endif /* LINK2HOP_H_ */
