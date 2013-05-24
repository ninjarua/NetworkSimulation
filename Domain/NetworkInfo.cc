/*
 * NetworkInfo.cpp
 *
 *  Created on: May 21, 2013
 *      Author: thanh
 */

#include "NetworkInfo.h"
namespace domain{

NetworkInfo::NetworkInfo() {
	_listInfectedNodes = vector<Node*>();
	_listDetectors = vector<Node*>();
}

NetworkInfo::~NetworkInfo() {
}

vector<Node*> NetworkInfo::GetInfectedNodes()
{
	return _listInfectedNodes;
}

vector<Node*> NetworkInfo::GetDetectors()
{
	return _listDetectors;
}
}
