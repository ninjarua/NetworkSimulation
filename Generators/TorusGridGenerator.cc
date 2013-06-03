/*
 * TorusGridGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "TorusGridGenerator.h"

namespace generators {

TorusGridGenerator::TorusGridGenerator(int size) {
	deployment = new TorusGridDeploying(size);
}

TorusGridGenerator::~TorusGridGenerator() {
	delete deployment;
}
//
//void TorusGridGenerator::GeneratorFromFiles(Network* network, string folder, int index)
//{
//
//}

} /* namespace generators */
