/*
 * CxHopTolerance.h
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#ifndef CXHOPTOLERANCE_H_
#define CXHOPTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CxHopTolerance: public protocols::ToleranceBase {
	static void CallbackReceiveDeactivateMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message);
public:
	CxHopTolerance();
	virtual ~CxHopTolerance();
	virtual void TolerateNode(NodePtr node, NodePtr byzantine);
	string GetToleranceName();
	void ReceiveDeactivateMessage(NodePtr sender, NodePtr receiver, Message* message);
};

} /* namespace protocols */
#endif /* CXHOPTOLERANCE_H_ */
