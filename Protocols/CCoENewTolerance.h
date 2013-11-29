/*
 * CCoAllETolerance.h
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#ifndef CCOENEWTOLERANCE_H_
#define CCOENEWTOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CCoENewTolerance : public ToleranceBase {
public:
	CCoENewTolerance();
	virtual ~CCoENewTolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* CCOALLETOLERANCE_H_ */
