/*
 * Message.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "stdafx.h"
#include "Node.h"
#include <fstream>
#include <iostream>

namespace domain {
enum MessageStatus { Created = 0, Sending = 1, Stopped = 2, Expired = 3 };
class Message;
typedef void (*MessageReaction)(void*, Node*, Node*, Message*);
class Message {
public:
	int creationTime;
	Node* sender;
	Node* receiver;
	MessageStatus status;

	Message();
	Message(Node* sender, Node* receiver, const int& timeSlot);
	virtual ~Message();
	bool static isMessageExpired(const Message& m);
	MessageReaction receivingAction;
	virtual string GetMessageName() const;
	friend ofstream& operator<<(ofstream& ofs, const Message& message);
	friend ostream& operator<<(ostream& ofs, const Message& message);
	//void (*receivingAction)(Node*, Node*, Message*);
};

} /* namespace domain */
#endif /* MESSAGE_H_ */
