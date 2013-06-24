/*
 * DeactivateMessage.cc
 *
 *  Created on: Jun 9, 2013
 *      Author: thanh
 */

#include "DeactivateMessage.h"

namespace domain {

DeactivateMessage::DeactivateMessage() {
	// TODO Auto-generated constructor stub

}

DeactivateMessage::DeactivateMessage(LinkPtr link, const int& timeSlot)
	: Message(link, timeSlot)
{

}

DeactivateMessage::DeactivateMessage(LinkPtr link, Link2Hop* l2Hop, const int& timeSlot)
	: Message(link, timeSlot)
{
	link2Hop = l2Hop;
}

DeactivateMessage::~DeactivateMessage() {
	// TODO Auto-generated destructor stub
}

} /* namespace domain */
