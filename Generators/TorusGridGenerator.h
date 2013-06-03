/*
 * TorusGridGenerator.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef TORUSGRIDGENERATOR_H_
#define TORUSGRIDGENERATOR_H_

#include "NetworkGenerator.h"
#include "TorusGridDeploying.h"

namespace generators {

class TorusGridGenerator: public NetworkGenerator {
public:
	TorusGridGenerator(int size);
	virtual ~TorusGridGenerator();
//	void GeneratorFromFiles(Network* network, string folder, int index = 0);
};

} /* namespace generators */
#endif /* TORUSGRIDGENERATOR_H_ */
