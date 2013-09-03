/*
 * K04Tolerance.h
 *
 *  Created on: Jun 10, 2013
 *      Author: thanhnd
 */

#ifndef K04TOLERANCE_H_
#define K04TOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class K1HopTolerance: public ToleranceBase {
	static void CallbackReceiveDeactivateMessage(void* ptr, Message* message);
public:
	K1HopTolerance();
	virtual ~K1HopTolerance();
	void TolerateNode(LinkPtr link);
	void ReceiveDeactivateMessage(Message* message);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* K04TOLERANCE_H_ */
