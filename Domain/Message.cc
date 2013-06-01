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

Message::Message(Node* s, Node* r, const int& t) {
	sender = s;
	receiver = r;
	creationTime = t;
	status = Sending;
	//receivingAction = NULL;
}

Message::~Message() {

}

bool Message::isMessageExpired(const Message& m)
{
	return m.status == Expired;
}

string Message::GetMessageName() const
{
	return "General message";
}
ostream& operator<<(ostream& ofs, const Message& message)
{
	string logString = message.GetMessageName() + ": ";
	ofs <<  logString;
	ofs << message.sender->id << " to " << message.receiver->id << "\n";
	return ofs;
}

ofstream& operator<<(ofstream& ofs, const Message& message)
{
	string logString = message.GetMessageName() + ": ";
	ofs <<  logString;
	ofs << message.sender->id << " to " << message.receiver->id << "\n";
	return ofs;
}

} /* namespace domain */
