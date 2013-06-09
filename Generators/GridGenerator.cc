/*
 * GridGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "GridGenerator.h"

namespace generators {

GridGenerator::GridGenerator()
{
	deployment = new GridDeploying();
}

GridGenerator::GridGenerator(int size) {
	deployment = new GridDeploying(size);
}

GridGenerator::~GridGenerator() {
	delete deployment;
}

void GridGenerator::GenerateFromFiles(Network* network, string folder, int index)
{
	while (!network->hasTopology)
	{
		network->hasTopology = deployment->RunDeploy(network);
	}
}

} /* namespace generators */
