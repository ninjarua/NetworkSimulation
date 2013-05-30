/*
 * Message.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Message.h"

namespace domain {

Message::Message() {
	//receivingAction = NULL;
}

Message::Message(Node* s, Node* r, int t) {
	sender = s;
	receiver = r;
	creationTime = t;
	//receivingAction = NULL;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

bool Message::isMessageExpired(Message* m)
{
	return m->status == Expired;
}

} /* namespace domain */
