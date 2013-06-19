/*
 * DeactivateMessage.h
 *
 *  Created on: Jun 9, 2013
 *      Author: thanh
 */

#ifndef DEACTIVATEMESSAGE_H_
#define DEACTIVATEMESSAGE_H_

#include "Message.h"

namespace domain {

class DeactivateMessage: public domain::Message {
public:
	int TTL;
	DeactivateMessage();
	DeactivateMessage(LinkPtr link, const int& timeSlot);
	virtual ~DeactivateMessage();
};

} /* namespace domain */
#endif /* DEACTIVATEMESSAGE_H_ */
