/*
 * K01Tolerance.h
 *
 *  Created on: Jun 7, 2013
 *      Author: thanhnd
 */

#ifndef K01TOLERANCE_H_
#define K01TOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class KSelfTolerance : public ToleranceBase {
public:
	KSelfTolerance();
	virtual ~KSelfTolerance();

	virtual void TolerateNode(LinkPtr link);

	string GetToleranceName();
};

} /* namespace generators */
#endif /* K01TOLERANCE_H_ */
