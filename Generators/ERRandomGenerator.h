/*
 * ERRandomGenerator.h
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#ifndef ERRANDOMGENERATOR_H_
#define ERRANDOMGENERATOR_H_

#include "NetworkGenerator.h"

namespace generators {

class ERRandomGenerator : public NetworkGenerator {
public:
	ERRandomGenerator();
	ERRandomGenerator(int numberNodes, double p);
	virtual ~ERRandomGenerator();
};

} /* namespace generators */
#endif /* ERRANDOMGENERATOR_H_ */
