/*
 * CutLinkMessage.h
 *
 *  Created on: Jul 23, 2013
 *      Author: thanhnd
 */

#ifndef CUTLINKMESSAGE_H_
#define CUTLINKMESSAGE_H_

#include "Message.h"

namespace domain {

class CutLinkMessage : public Message {
public:
	LinkPtr linkToCut;
	CutLinkMessage(LinkPtr messageLink, LinkPtr cutLink, const int& timeSlot);
	virtual ~CutLinkMessage();
	bool cutCarrierLink;
};

} /* namespace domain */
#endif /* CUTLINKMESSAGE_H_ */
