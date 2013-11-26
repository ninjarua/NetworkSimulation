/*
 * COtherBridgesTolerance.h
 *
 *  Created on: Aug 31, 2013
 *      Author: thanhnd
 */

#ifndef COTHERBRIDGESTOLERANCE_H_
#define COTHERBRIDGESTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CCo2ETolerance : public ToleranceBase {
public:
	CCo2ETolerance();
	virtual ~CCo2ETolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* COTHERBRIDGESTOLERANCE_H_ */
