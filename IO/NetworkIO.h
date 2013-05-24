/*
 * NetworkIO.h
 *
 *  Created on: May 25, 2013
 *      Author: thanh
 */

#ifndef NETWORKIO_H_
#define NETWORKIO_H_

#include "stdafx.h"
#include "Network.h"
#include <string>
using namespace domain;
using namespace std;

namespace protocols {

class NetworkIO {
public:
	NetworkIO();
	virtual ~NetworkIO();
	void WriteNetworkToFile(Network network, string filename);
};

} /* namespace protocols */
#endif /* NETWORKIO_H_ */
