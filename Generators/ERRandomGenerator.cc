/*
 * ERRandomGenerator.cc
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#include "ERRandomGenerator.h"
#include "ERRandomDeploying.h"

using namespace deployment;

namespace generators {

ERRandomGenerator::ERRandomGenerator() {
	deployment = new ERRandomDeploying();
}

ERRandomGenerator::ERRandomGenerator(int numberNodes, double p)
{
	deployment = new ERRandomDeploying(numberNodes, p);
}

ERRandomGenerator::~ERRandomGenerator() {

}

} /* namespace generators */
