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

class CCommonTolerance: public ToleranceBase {

	static void CallbackReceiveCutLinkMessage(void *ptr, Message* message);
	void ReceiveCutLinkMessage(Message* message);
public:
	CCommonTolerance();
	virtual ~CCommonTolerance();

	virtual void TolerateNode(LinkPtr link);

	string GetToleranceName();
};

} /* namespace protocols */
#endif /* CCOMMONTOLERANCE_H_ */
