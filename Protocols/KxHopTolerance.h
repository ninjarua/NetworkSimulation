/*
 * K11Tolerance.h
 *
 *  Created on: Jun 9, 2013
 *      Author: thanh
 */

#ifndef K11TOLERANCE_H_
#define K11TOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class KxHopTolerance: public ToleranceBase {
	int hopToKill;
	static void CallbackReceiveDeactivateMessage(void* ptr, Message* message);
public:
	KxHopTolerance(int hopKilled);
	virtual ~KxHopTolerance();
	void TolerateNode(LinkPtr link);
	void ReceiveDeactivateMessage(Message* message);
};

} /* namespace protocols */
#endif /* K11TOLERANCE_H_ */
