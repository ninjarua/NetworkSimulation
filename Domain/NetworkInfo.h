/*
 * NetworkInfo.h
 *
 *  Created on: May 21, 2013
 *      Author: thanh
 */

#ifndef NETWORKINFO_H_
#define NETWORKINFO_H_

#include <vector>
#include "stdafx.h"
#include "Node.h"

namespace domain {

class NetworkInfo {
public:
	NetworkInfo();
	virtual ~NetworkInfo();
	vector<Node*>* listInfectedNodes;
	vector<Node*>* listDetectors;
};
}
#endif /* NETWORKINFO_H_ */
