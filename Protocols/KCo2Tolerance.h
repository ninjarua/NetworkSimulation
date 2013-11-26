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

class KCo2Tolerance : public ToleranceBase {
	static void CallbackReceiveKillingMessage(void *ptr, Message* message);
	void ReceiveKillingMessage(Message* message);
public:
	KCo2Tolerance();
	virtual ~KCo2Tolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* KOTHERBRIDGESTOLERANCE_H_ */
