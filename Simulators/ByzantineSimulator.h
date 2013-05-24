/*
 * PropagationSimulator.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef PROPAGATIONSIMULATOR_H_
#define PROPAGATIONSIMULATOR_H_

#include "SimulatorBase.h"

namespace simulators {

class ByzantineSimulator: public SimulatorBase {
public:
	ByzantineSimulator();
	virtual ~ByzantineSimulator();
};

} /* namespace deployment */
#endif /* PROPAGATIONSIMULATOR_H_ */
