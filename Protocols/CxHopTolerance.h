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
	static void CallbackReceiveCutLink2HopMessage(void* ptr, Message* message);
//	static void CallbackReceiveCutLinkMessage(void *ptr, Message* message);
public:
	CxHopTolerance();
	virtual ~CxHopTolerance();
	virtual void TolerateNode(LinkPtr link);
	string GetToleranceName();
	void ReceiveCutLink2HopMessage(Message* message);
//	void ReceiveCutLinkMessage(Message* message);
	Link2Hop* GetCommonNeighborsExcept(NodePtr n1, NodePtr n2, NodePtr exception);
	Link2Hop* LookingForLink2Hop(vector<Link2Hop*> links, NodePtr node);
};

} /* namespace protocols */
#endif /* CXHOPTOLERANCE_H_ */
