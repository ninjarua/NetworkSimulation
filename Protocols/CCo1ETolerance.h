/*
 * CCommonTolerance.h
 *
 *  Created on: Aug 28, 2013
 *      Author: thanhnd
 */

#ifndef CCOMMONTOLERANCE_H_
#define CCOMMONTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CCo1ETolerance: public ToleranceBase {
	static void CallbackReceiveCutLinkMessage(void *ptr, Message* message);
	void ReceiveCutLinkMessage(Message* message);
public:
	CCo1ETolerance();
	virtual ~CCo1ETolerance();

	virtual void TolerateNode(LinkPtr link);

	string GetToleranceName();
};

} /* namespace protocols */
#endif /* CCOMMONTOLERANCE_H_ */
