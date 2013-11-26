/*
 * KselfCCommon.h
 *
 *  Created on: Aug 29, 2013
 *      Author: thanhnd
 */

#ifndef KSELFCCOMMON_H_
#define KSELFCCOMMON_H_

#include "ToleranceBase.h"

namespace protocols {

class KSelfCCo1ETolerance: public ToleranceBase {
	static void CallbackReceiveCutLinkMessage(void *ptr, Message* message);
	void ReceiveCutLinkMessage(Message* message);
public:
	KSelfCCo1ETolerance();
	virtual ~KSelfCCo1ETolerance();

	virtual void TolerateNode(LinkPtr link);

	string GetToleranceName();
};

} /* namespace protocols */
#endif /* KSELFCCOMMON_H_ */
