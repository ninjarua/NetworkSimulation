/*
 * KOtherBridgesTolerance.h
 *
 *  Created on: Sep 8, 2013
 *      Author: thanhnd
 */

#ifndef KOTHERBRIDGESTOLERANCE_H_
#define KOTHERBRIDGESTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class KOtherBridgesTolerance : public ToleranceBase {
	static void CallbackReceiveKillingMessage(void *ptr, Message* message);
	void ReceiveKillingMessage(Message* message);
public:
	KOtherBridgesTolerance();
	virtual ~KOtherBridgesTolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* KOTHERBRIDGESTOLERANCE_H_ */
