/*
 * FixedRangeRandomDeploying.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef FIXEDRANGERANDOMDEPLOYING_H_
#define FIXEDRANGERANDOMDEPLOYING_H_

#include "stdafx.h"
#include <string>

#include "Network.h"
#include "Deploying.h"
#include "nsException.h"

using namespace domain;

namespace deployment {

class FixedRangeRandomDeploying : public Deploying {
public:
	FixedRangeRandomDeploying();
	virtual ~FixedRangeRandomDeploying();

	string GetDeployingName();

	bool ObtainTopology(Network* network);
	double GetPosX(int nodeSequenceId);

	double GetPosY(int nodeSequenceId);
	double GetCellLength();
};

} /* namespace protocols */
#endif /* FIXEDRANGERANDOMDEPLOYING_H_ */
