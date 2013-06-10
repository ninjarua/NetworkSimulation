/*
 * C01Tolerance.h
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#ifndef C01TOLERANCE_H_
#define C01TOLERANCE_H_

#include "ToleranceBase.h"

namespace generators {

class C01Tolerance: public protocols::ToleranceBase {
public:
	C01Tolerance();
	virtual ~C01Tolerance();

	virtual void TolerateNode(NodePtr node, NodePtr byzantine);

	string GetToleranceName();
};

} /* namespace generators */
#endif /* C01TOLERANCE_H_ */
