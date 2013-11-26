/*
 * CCo3ETolerance.h
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#ifndef CCO3ETOLERANCE_H_
#define CCO3ETOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CCo3ETolerance : public ToleranceBase {
public:
	CCo3ETolerance();
	virtual ~CCo3ETolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* CCO3ETOLERANCE_H_ */
