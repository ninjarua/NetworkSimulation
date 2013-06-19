/*
 * TorusGridGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "TorusGridGenerator.h"

namespace generators {

TorusGridGenerator::TorusGridGenerator()
{
	deployment = new TorusGridDeploying();
}

TorusGridGenerator::TorusGridGenerator(int size) {
	deployment = new TorusGridDeploying(size);
}

TorusGridGenerator::~TorusGridGenerator() {
	delete deployment;
}

bool TorusGridGenerator::GenerateFromFiles(Network* network, string folder, int index)
{
	while (!network->hasTopology)
	{
		network->hasTopology = deployment->runDeploy(network);
	}
	return true;
}

} /* namespace generators */
