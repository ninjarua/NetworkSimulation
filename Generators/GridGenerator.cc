/*
 * GridGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "GridGenerator.h"

namespace generators {

GridGenerator::GridGenerator(int size) {
	deployment = new GridDeploying(size);
}

GridGenerator::~GridGenerator() {
	delete deployment;
}

} /* namespace generators */
