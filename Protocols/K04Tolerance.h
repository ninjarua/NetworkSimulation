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

class K04Tolerance: public ToleranceBase {
	static void CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message);
public:
	K04Tolerance();
	virtual ~K04Tolerance();
	void TolerateNode(NodePtr node, NodePtr byzantine);
	void ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message);
};

} /* namespace protocols */
#endif /* K04TOLERANCE_H_ */
