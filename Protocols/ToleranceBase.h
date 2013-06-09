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

enum TypeOfTolerance{ K01 = 0, K03 = 1, K04 = 2, K05 = 3, K07 = 4, K08 = 5, K11 = 6,
    C01 = 7, C03 = 8, C05 = 9, C09 = 10, C01K03 = 11, C01K05 = 12 };

class ToleranceBase : public NetworkProtocol {
public:
	ToleranceBase();
	virtual ~ToleranceBase();
	virtual void TolerateNode(NodePtr node, NodePtr byzantine);
	virtual string GetToleranceName();
//	static void CallbackReceiveDeactivateMessage(void* ptr, Node& sender, Node& receiver, Message& message);
	virtual void ReceiveDeactivateMessage(Node& sender, Node& receiver, Message& message);
};

} /* namespace protocols */
#endif /* TOLERANCEBASE_H_ */
