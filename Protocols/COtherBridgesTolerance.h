/*
 * COtherBridgesTolerance.h
 *
 *  Created on: Aug 31, 2013
 *      Author: thanhnd
 */

#ifndef COTHERBRIDGESTOLERANCE_H_
#define COTHERBRIDGESTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class COtherBridgesTolerance : public ToleranceBase {
	static void CallbackReceiveCutLinkMessage(void *ptr, Message* message);
	void ReceiveCutLinkMessage(Message* message);
public:
	COtherBridgesTolerance();
	virtual ~COtherBridgesTolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* COTHERBRIDGESTOLERANCE_H_ */
