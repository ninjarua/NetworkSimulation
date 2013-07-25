/*
 * CutLinkMessage.cc
 *
 *  Created on: Jul 23, 2013
 *      Author: thanhnd
 */

#include "CutLinkMessage.h"

namespace domain {

CutLinkMessage::CutLinkMessage(LinkPtr messageLink, LinkPtr cutLink, const int& timeSlot)
	: Message(messageLink, timeSlot) {
	linkToCut = cutLink;
}

CutLinkMessage::~CutLinkMessage() {
}

} /* namespace domain */
