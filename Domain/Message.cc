/*
 * Message.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Message.h"

namespace domain {

Message::Message() {
	// TODO Auto-generated constructor stub

}

Message::Message(Node* s, Node* r, int t) {
	sender = s;
	receiver = r;
	creationTime = t;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

} /* namespace domain */
