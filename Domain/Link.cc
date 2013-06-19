/*
 * Link.cc
 *
 *  Created on: Jun 13, 2013
 *      Author: thanhnd
 */

#include "Link.h"

namespace domain {

Link::Link(Node* n1, Node* n2) {
//	if (n1->id >= n2->id)
//	{
		src = n1; dest = n2;
//	}
//	else
//	{
//		node1 = n2; node2 = n1;
//	}
	state = Active;
}

Link::~Link() {

}

} /* namespace domain */
