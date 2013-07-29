/*
 * SmallworldGenerator.cc
 *
 *  Created on: Jul 29, 2013
 *      Author: thanhnd
 */

#include "SmallworldGenerator.h"
#include "SmallworldDeploying.h"

namespace generators {

SmallworldGenerator::SmallworldGenerator() {

}

SmallworldGenerator::SmallworldGenerator(int numberNodes, int xTerr, int yTerr, int range, int numberOfLongEdge) {
	deployment = new SmallworldDeploying(numberNodes, xTerr, yTerr, range, numberOfLongEdge);
}

SmallworldGenerator::~SmallworldGenerator() {
	delete deployment;
}

} /* namespace domain */
