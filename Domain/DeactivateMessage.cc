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

DeactivateMessage::DeactivateMessage(NodePtr sender, NodePtr receiver, const int& timeSlot)
	: Message(sender, receiver, timeSlot)
{

}

DeactivateMessage::~DeactivateMessage() {
	// TODO Auto-generated destructor stub
}

} /* namespace domain */
