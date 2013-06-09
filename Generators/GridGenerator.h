/*
 * GridGenerator.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef GRIDGENERATOR_H_
#define GRIDGENERATOR_H_

#include "NetworkGenerator.h"
#include "GridDeploying.h"

namespace generators {

class GridGenerator: public NetworkGenerator {
public:
	GridGenerator();
	GridGenerator(int size);
	virtual ~GridGenerator();
	void GenerateFromFiles(Network* network, string folder, int index = 0);
};

} /* namespace generators */
#endif /* GRIDGENERATOR_H_ */
