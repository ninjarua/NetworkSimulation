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
	deployment = new SmallworldDeploying();
}

SmallworldGenerator::SmallworldGenerator(int numberNodes, int xTerr, int yTerr, int range, int numberOfShortEdges, int numberOfLongEdges) {
	deployment = new SmallworldDeploying(numberNodes, xTerr, yTerr, range, numberOfShortEdges, numberOfLongEdges);
}

SmallworldGenerator::~SmallworldGenerator() {
	delete deployment;
}

} /* namespace domain */
