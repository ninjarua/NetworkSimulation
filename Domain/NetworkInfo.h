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

struct NetworkInfo {
	int seedId;
	int numberOfInfectedNodes;
	int numberOfDetectors;
	int numberOfInactiveNodes;
};
}
#endif /* NETWORKINFO_H_ */
