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

class K03Tolerance : ToleranceBase{
	static void CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message);
public:
	K03Tolerance();
	virtual ~K03Tolerance();
	string GetToleranceName();
	void TolerateNode(NodePtr node, NodePtr byzantine);
	void ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message);
};

}
#endif
