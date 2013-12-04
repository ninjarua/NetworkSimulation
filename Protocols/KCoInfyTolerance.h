/*
 * KCoInfyTolerance.h
 *
 *  Created on: Dec 4, 2013
 *      Author: thanh
 */

#ifndef KCOINFYTOLERANCE_H_
#define KCOINFYTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class KCoInfyTolerance : public ToleranceBase {
	static void CallbackReceiveKillingMessage(void *ptr, Message* message);
	void ReceiveKillingMessage(Message* message);
public:
	KCoInfyTolerance();
	virtual ~KCoInfyTolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace generators */
#endif /* KCOINFYTOLERANCE_H_ */
