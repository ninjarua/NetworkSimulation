/*
 * K1Tolerance.h
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#ifndef K1TOLERANCE_H_
#define K1TOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class K03Tolerance : public ToleranceBase{
	static void CallbackReceiveDeactivateMessage(void* ptr, Message* message);
public:
	K03Tolerance();
	virtual ~K03Tolerance();
	string GetToleranceName();
	void TolerateNode(LinkPtr link);
	void ReceiveDeactivateMessage(Message* message);
};

}
#endif
