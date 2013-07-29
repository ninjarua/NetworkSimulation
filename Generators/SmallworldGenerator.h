/*
 * SmallworldGenerator.h
 *
 *  Created on: Jul 29, 2013
 *      Author: thanhnd
 */

#ifndef SMALLWORLDGENERATOR_H_
#define SMALLWORLDGENERATOR_H_

#include "NetworkGenerator.h"

namespace generators {

class SmallworldGenerator: public NetworkGenerator {
public:
	SmallworldGenerator();
	SmallworldGenerator(int numberNodes, int xTerr, int yTerr, int range, int numberOfLongEdge);
	virtual ~SmallworldGenerator();
};

} /* namespace domain */
#endif /* SMALLWORLDGENERATOR_H_ */
