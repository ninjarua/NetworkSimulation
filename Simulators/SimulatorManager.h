/*
 * SimulatorManager.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef SIMULATORMANAGER_H_
#define SIMULATORMANAGER_H_
#include "stdafx.h"
#include <boost/thread.hpp>
#include "ByzantineSimulator.h"

namespace simulators
{

class SimulatorManager {
public:
	boost::thread_group simulatorGroup;

	SimulatorManager();
	virtual ~SimulatorManager();
	void SetParameters(DeployingType deployingType, int numberOfNodes, int transRange, float xTerr, float yTerr, float d0);

	void RunSimulation(TypeOfTolerance type);
};

}
#endif /* SIMULATORMANAGER_H_ */
