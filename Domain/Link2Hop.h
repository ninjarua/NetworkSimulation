/*
 * Link2Hop.h
 *
 *  Created on: Jun 18, 2013
 *      Author: thanhnd
 */

#ifndef LINK2HOP_H_
#define LINK2HOP_H_
#include "stdafx.h"

#include <list>

namespace domain {
class Node;
class Link2Hop {
public:
//	Node* src;
	Node* dest;
	vector<Node*> mids;
	Link2Hop(Node* d, Node* mid);
	virtual ~Link2Hop();
};

} /* namespace domain */
#endif /* LINK2HOP_H_ */
