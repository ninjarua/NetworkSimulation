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

class CSelfTolerance: public protocols::ToleranceBase {
public:
	CSelfTolerance();
	virtual ~CSelfTolerance();

	virtual void TolerateNode(LinkPtr link);

	string GetToleranceName();
};

} /* namespace generators */
#endif /* C01TOLERANCE_H_ */
