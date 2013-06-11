/*
 * C01K03Tolerance.h
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#ifndef C01K03TOLERANCE_H_
#define C01K03TOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class C01K03Tolerance: public ToleranceBase {
	static void CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message);
public:
	C01K03Tolerance();
	virtual ~C01K03Tolerance();
	virtual void TolerateNode(NodePtr node, NodePtr byzantine);
	string GetToleranceName();
	void ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message);
};

} /* namespace protocols */
#endif /* C01K03TOLERANCE_H_ */
