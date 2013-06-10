/*
 * ToleranceBase.cc
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ToleranceBase.h"

namespace protocols {

ToleranceBase::ToleranceBase() {

}

ToleranceBase::~ToleranceBase() {

}

string ToleranceBase::GetToleranceName()
{
	return "Base";
}

//ToleranceBase ToleranceBase::GetBase()
//{
//    if (_instance == NULL)
//        _instance = new ToleranceBase();
//    return _instance;
//}

void ToleranceBase::TolerateNode(NodePtr node, NodePtr byzantine)
{
//	node->detectedByzantines.insert(byzantine);
}
//
//void ToleranceBase::CallbackReceiveDeactivateMessage(void* ptr, Node& sender, Node& receiver, Message& message)
//{
//	ToleranceBase* basePtr = (ToleranceBase*)ptr;
//	basePtr->ReceiveDeactivateMessage(sender, receiver, message);
//}

void ToleranceBase::ReceiveDeactivateMessage(Node& sender, Node& receiver, Message& message)
{

}

} /* namespace protocols */
