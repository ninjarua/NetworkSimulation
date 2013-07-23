/*
 * C01Tolerance.h
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#ifndef C01TOLERANCE_H_
#define C01TOLERANCE_H_

#include "ToleranceBase.h"

namespace generators {

class C01Tolerance: public protocols::ToleranceBase {
	static void CallbackReceiveCutLinkMessage(void *ptr, Message* message);
	void ReceiveCutLinkMessage(Message* message);
public:
	C01Tolerance();
	virtual ~C01Tolerance();

	virtual void TolerateNode(LinkPtr link);

	string GetToleranceName();
};

} /* namespace generators */
#endif /* C01TOLERANCE_H_ */
