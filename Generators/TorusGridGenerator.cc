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

void TorusGridGenerator::GenerateFromFiles(Network* network, string folder, int index)
{
	while (!network->hasTopology)
	{
		network->hasTopology = deployment->RunDeploy(network);
	}
}

} /* namespace generators */
