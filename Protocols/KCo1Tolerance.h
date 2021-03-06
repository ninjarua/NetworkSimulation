/*
 * KCommonTolerance.h
 *
 *  Created on: Aug 22, 2013
 *      Author: thanhnd
 */

#ifndef KCOMMONTOLERANCE_H_
#define KCOMMONTOLERANCE_H_

#include "ToleranceBase.h"

using namespace domain;

namespace protocols {

class KCo1Tolerance: public ToleranceBase {
	static void CallbackReceiveKillingMessage(void *ptr, Message* message);
	void ReceiveKillingMessage(Message* message);

public:
	KCo1Tolerance();
	virtual ~KCo1Tolerance();

	virtual void TolerateNode(LinkPtr link);
	string GetToleranceName();

};

} /* namespace protocols */
#endif /* KCOMMONTOLERANCE_H_ */
