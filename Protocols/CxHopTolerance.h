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
	static void CallbackReceiveDeactivateMessage(void* ptr, Message* message);
public:
	CxHopTolerance();
	virtual ~CxHopTolerance();
	virtual void TolerateNode(LinkPtr link);
	string GetToleranceName();
	void ReceiveDeactivateMessage(Message* message);
	list<LinkPtr> GetCommonNeighborsExcept(NodePtr n1, NodePtr n2, NodePtr exception);
	bool ContainNode(vector<LinkPtr> links, NodePtr node);
};

} /* namespace protocols */
#endif /* CXHOPTOLERANCE_H_ */
