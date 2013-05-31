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

//ToleranceBase ToleranceBase::GetBase()
//{
//    if (_instance == NULL)
//        _instance = new ToleranceBase();
//    return _instance;
//}

void ToleranceBase::TolerateNode(Node* node, Node* byzantine)
{
	node->state = Detector;
	node->OwnerNetwork->info->listDetectors->push_back(node);
	node->detectedByzantines->insert(byzantine);
	node->disconnectedNodes->insert(byzantine);
}

void ToleranceBase::CallbackReceiveDeactivateMessage(void* ptr, Node* sender, Node* receiver, Message* message)
{
	ToleranceBase* basePtr = (ToleranceBase*)ptr;
	basePtr->ReceiveDeactivateMessage(sender, receiver, message);
}

void ToleranceBase::ReceiveDeactivateMessage(Node* sender, Node* receiver, Message* message)
{

}

} /* namespace protocols */
