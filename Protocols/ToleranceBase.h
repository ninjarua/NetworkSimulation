/*
 * ToleranceBase.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef TOLERANCEBASE_H_
#define TOLERANCEBASE_H_

#include "Network.h"
#include "NetworkProtocol.h"

using namespace domain;

namespace protocols {

enum TypeOfTolerance{ KSelf = 0, K03 = 1, K1Hop = 2, K05 = 3, K07 = 4, K08 = 5, KxHop = 6,
    CSelf = 7, C03 = 8, C05 = 9, C09 = 10, C01K03 = 11, C01K05 = 12, CxHop = 13, KCommon = 14, CCommon = 15 };

class ToleranceBase : public NetworkProtocol {
public:
	ToleranceBase();
	virtual ~ToleranceBase();
	virtual void TolerateNode(LinkPtr link);
	virtual string GetToleranceName();
};

} /* namespace protocols */
#endif /* TOLERANCEBASE_H_ */
