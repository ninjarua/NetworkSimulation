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
	NetworkGenerator();
	virtual ~NetworkGenerator();
	virtual string GenerateToFiles(Network* network, string folder, int times = 1);
	virtual void GenerateFromFiles(Network* network, string folder, int index = 0);
	string GetDeployingName();

protected:
	virtual string GetFilenameByDeployment(string folder, int number);
	string GetFilename(int id);
	string GetVerifyFilename(int id);
	string GetFailureString(int count);
};

} /* namespace generators */
#endif /* NETWORKGENERATOR_H_ */
