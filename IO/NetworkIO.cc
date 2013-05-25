/*
 * NetworkIO.cc
 *
 *  Created on: May 25, 2013
 *      Author: thanh
 */

#include "NetworkIO.h"
#include <iostream>
#include <fstream>

namespace protocols {

NetworkIO::NetworkIO() {
	// TODO Auto-generated constructor stub

}

NetworkIO::~NetworkIO() {
	// TODO Auto-generated destructor stub
}

void NetworkIO::WriteNetworkToFile(Network network, string filename)
{
	ofstream graphFile;
	graphFile.open(filename.c_str(), ios::out);

	graphFile << network;

	graphFile.close();
}

} /* namespace protocols */
