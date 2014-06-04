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
	FixedRangeRandomDeploying(int numberNodes, int xTerr, int yTerr, int range);
	virtual ~FixedRangeRandomDeploying();

	string getDeployingName();

	bool obtainTopology(Network* network);
	double getPosX(int nodeSequenceId);
	double getPosY(int nodeSequenceId);
	double getCellLength();

	virtual void neighborInitialization(Network* network);
	virtual bool isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor);
};

} /* namespace protocols */
#endif /* FIXEDRANGERANDOMDEPLOYING_H_ */
