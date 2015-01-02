/*
 * CGreateTolerance.h
 *
 *  Created on: Oct 20, 2014
 *      Author: thanhnd
 */

#ifndef PROTOCOLS_CGREATERTOLERANCE_H_
#define PROTOCOLS_CGREATERTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CGreateTolerance: public ToleranceBase {
	static void CallbackReceiveDeactivateMessage(void* ptr, Message* message);
public:
	CGreateTolerance();
	virtual ~CGreateTolerance();

	virtual void TolerateNode(LinkPtr link);
	string GetToleranceName();
	void ReceiveDeactivateMessage(Message* message);
};

} /* namespace protocols */

#endif /* PROTOCOLS_CGREATERTOLERANCE_H_ */
