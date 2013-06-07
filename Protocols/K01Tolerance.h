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

class K01Tolerance : public ToleranceBase {
public:
	K01Tolerance();
	virtual ~K01Tolerance();

	virtual void TolerateNode(NodePtr node, NodePtr byzantine);

	string GetToleranceName();
};

} /* namespace generators */
#endif /* K01TOLERANCE_H_ */
