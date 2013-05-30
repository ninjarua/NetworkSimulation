/*
 * NetworkInfo.cpp
 *
 *  Created on: May 21, 2013
 *      Author: thanh
 */

#include "NetworkInfo.h"
namespace domain{

NetworkInfo::NetworkInfo() {
	listInfectedNodes = new vector<Node*>();
	listDetectors = new vector<Node*>();
}

NetworkInfo::~NetworkInfo() {
}
//
//vector<Node*> NetworkInfo::GetInfectedNodes()
//{
//	return listInfectedNodes;
//}
//
//vector<Node*> NetworkInfo::GetDetectors()
//{
//	return listDetectors;
//}
}
