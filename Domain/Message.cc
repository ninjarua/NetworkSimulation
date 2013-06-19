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

Message::Message(LinkPtr l, const int& t) {
	link = l;
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
	ofs << message.link->src->id << " to " << message.link->dest->id << "\n";
	return ofs;
}

ofstream& operator<<(ofstream& ofs, const Message& message)
{
	string logString = message.GetMessageName() + ": ";
	ofs <<  logString;
	ofs << message.link->src->id << " to " << message.link->dest->id << "\n";
	return ofs;
}

} /* namespace domain */
