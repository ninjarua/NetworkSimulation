/*
 * NetworkGenerator.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef NETWORKGENERATOR_H_
#define NETWORKGENERATOR_H_

#include "stdafx.h"
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "Deploying.h"

using namespace boost;
using namespace deployment;

namespace generators {

class NetworkGenerator {
protected:
	Deploying* deployment;
public:
	bool specificInputFile;
	NetworkGenerator();
	virtual ~NetworkGenerator();
	virtual string generateToFiles(Network* network, string folder, int times = 1, bool create2HopInfo = false);
	virtual bool generateFromFiles(Network* network, string folder, int index = 0);
	virtual void writeNetworkToFile(Network* network, string folder, int index = 0);
	string getDeployingName();
	void switch2HopInfo(bool using2HopInfo);

protected:
	virtual string getFilenameByDeployment(string folder, int number);
	string getFilename(int id);
	string getVerifyFilename(int id);
	string getFailureString(int count);
};

} /* namespace generators */
#endif /* NETWORKGENERATOR_H_ */
