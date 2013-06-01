/*
 * K1Tolerance.h
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#ifndef K1TOLERANCE_H_
#define K1TOLERANCE_H_

#include "stdafx.h"
#include "ToleranceBase.h"

namespace protocols {

class K03Tolerance : ToleranceBase{
public:
	K03Tolerance();
	virtual ~K03Tolerance();
	string GetToleranceName();
};

} /* namespace domain */
#endif /* K1TOLERANCE_H_ */
