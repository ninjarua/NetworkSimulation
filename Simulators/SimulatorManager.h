/*
 * SimulatorManager.h
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#ifndef SIMULATORMANAGER_H_
#define SIMULATORMANAGER_H_

#include <boost/thread.hpp>

class SimulatorManager {
public:
	SimulatorManager();
	virtual ~SimulatorManager();

	boost::thread_group simulatorGroup;
};

#endif /* SIMULATORMANAGER_H_ */
