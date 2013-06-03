/*
 * FixedRangeGenerator.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef FIXEDRANGEGENERATOR_H_
#define FIXEDRANGEGENERATOR_H_

#include "NetworkGenerator.h"
#include "FixedRangeRandomDeploying.h"

using namespace deployment;

namespace generators {

class FixedRangeGenerator: public NetworkGenerator {
public:
	FixedRangeGenerator();
	FixedRangeGenerator(int numberNodes, int xTerr, int yTerr, int range);
	virtual ~FixedRangeGenerator();
};

} /* namespace generators */
#endif /* FIXEDRANGEGENERATOR_H_ */
