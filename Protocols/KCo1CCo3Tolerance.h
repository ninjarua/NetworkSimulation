/*
 * KCo1CCo3Tolerance.h
 *
 *  Created on: Nov 27, 2013
 *      Author: thanhnd
 */

#ifndef KCO1CCO3TOLERANCE_H_
#define KCO1CCO3TOLERANCE_H_

#include <ToleranceBase.h>

namespace protocols {

class KCo1CCo3Tolerance: public ToleranceBase {
	static void CallbackReceiveKillingMessage(void *ptr, Message* message);
	void ReceiveKillingMessage(Message* message);
public:
	KCo1CCo3Tolerance();
	virtual ~KCo1CCo3Tolerance();

	virtual void TolerateNode(LinkPtr link);
	string GetToleranceName();
};

} /* namespace protocols */

#endif /* KCO1CCO3TOLERANCE_H_ */
