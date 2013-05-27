/*
 * Message.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Node.h"

namespace domain {
enum MessageStatus { Created = 0, Sending = 1, Stopped = 2, Expired = 3 };
class Message {
public:
	int creationTime;
	Node* sender;
	Node* receiver;
	MessageStatus status;

	Message();
	Message(Node* sender, Node* receiver, int timeSlot);
	virtual ~Message();
	void (*receivingAction)(Node*, Node*, Message*);
};

} /* namespace domain */
#endif /* MESSAGE_H_ */
