/*
 * CCoAllETolerance.h
 *
 *  Created on: Nov 26, 2013
 *      Author: thanhnd
 */

#ifndef CCOALLETOLERANCE_H_
#define CCOALLETOLERANCE_H_

#include "ToleranceBase.h"

namespace protocols {

class CCoInfyETolerance : public ToleranceBase {
public:
	CCoInfyETolerance();
	virtual ~CCoInfyETolerance();

	virtual void TolerateNode(LinkPtr messageLink);
	string GetToleranceName();
};

} /* namespace protocols */
#endif /* CCOALLETOLERANCE_H_ */
