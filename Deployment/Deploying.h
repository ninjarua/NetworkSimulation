/*
 * Deploying.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef DEPLOYING_H_
#define DEPLOYING_H_

#include "stdafx.h"
#include <math.h>

#include "Topology.h"
#include "Network.h"

using namespace domain;

namespace deployment {

typedef bool (*pNodeCondition)(Node*);

class Deploying {
public:
	Topology* topology;
	bool using2HopInfo;

	Deploying();
	virtual ~Deploying();
protected:
	virtual bool isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor);
//	virtual bool isAllDistanceValid(const Network& network, const Node& node);
//	virtual bool isValidDistance(const Node& node, const Node& neighbor);
	virtual double getCellLength();
	virtual double getPosX(int nodeSequenceId);
	virtual double getPosY(int nodeSequenceId);
	virtual void neighborInitialization(Network* network);
public:
	bool runDeploy(Network* network);

	virtual string getDeployingName();
	virtual bool obtainTopology(Network* network);
};

} /* namespace deployment */
#endif /* DEPLOYING_H_ */
