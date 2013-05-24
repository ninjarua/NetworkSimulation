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
	vector<Node*> _listInfectedNodes;
	vector<Node*> _listDetectors;
public:
	NetworkInfo();
	virtual ~NetworkInfo();
	vector<Node*> GetInfectedNodes();
	vector<Node*> GetDetectors();
};
}
#endif /* NETWORKINFO_H_ */
