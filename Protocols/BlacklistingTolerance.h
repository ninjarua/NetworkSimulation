/*
 * BlacklistingTolerance.h
 *
 *  Created on: Jun 29, 2014
 *      Author: thanhnd
 */

#ifndef BLACKLISTINGTOLERANCE_H_
#define BLACKLISTINGTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class BlacklistingTolerance: public ToleranceBase {
public:
	BlacklistingTolerance();
	virtual ~BlacklistingTolerance();

	virtual void TolerateNode(LinkPtr link);
	string GetToleranceName();
	void SendBlacklist(NodePtr detector, NodePtr infected);
};

} /* namespace protocols */

#endif /* BLACKLISTINGTOLERANCE_H_ */
