/*
 * ScaleFreeGenerator.cc
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#include "ScaleFreeGenerator.h"
#include "ScaleFreeDeploying.h"

using namespace deployment;

namespace generators {

ScaleFreeGenerator::ScaleFreeGenerator() {
	deployment = new ScaleFreeDeploying();
}

ScaleFreeGenerator::ScaleFreeGenerator(int m0, int m, int N)
{
	deployment = new ScaleFreeDeploying(m0, m, N);
}

ScaleFreeGenerator::~ScaleFreeGenerator() {

}

} /* namespace generators */
