/*
 * Link.h
 *
 *  Created on: Jun 13, 2013
 *      Author: thanhnd
 */

#ifndef LINK_H_
#define LINK_H_

namespace domain {

enum LinkState { Active = 0, Cut = 1, SetToCut = -1 };
class Node;
class Link {
public:
	Node* src;
	Node* dest;
	LinkState state;
	Link(Node* n1, Node* n2);
	virtual ~Link();
};
typedef Link* LinkPtr;

} /* namespace domain */
#endif /* LINK_H_ */
