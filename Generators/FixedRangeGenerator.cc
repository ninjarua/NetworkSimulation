/*
 * FixedRangeGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "FixedRangeGenerator.h"

namespace generators {

FixedRangeGenerator::FixedRangeGenerator(int numberNodes, int xTerr, int yTerr, int range) {
	deployment = new FixedRangeRandomDeploying(numberNodes, xTerr, yTerr, range);
}

FixedRangeGenerator::~FixedRangeGenerator() {
	delete deployment;
}

} /* namespace generators */
