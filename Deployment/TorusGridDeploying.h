/*
 * TorusGridDeploying.h
 *
 *  Created on: Jun 1, 2013
 *      Author: thanh
 */

#ifndef TORUSGRIDDEPLOYING_H_
#define TORUSGRIDDEPLOYING_H_

#include "stdafx.h"
#include "Deploying.h"
#include "nsException.h"

namespace deployment {

class TorusGridDeploying : public Deploying{
public:
	TorusGridDeploying();
	TorusGridDeploying(int size);
	virtual ~TorusGridDeploying();

protected:
    virtual bool isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor);
    virtual double getPosX(int nodeSequenceId);
    virtual double getPosY(int nodeSequenceId);
public:
    string getDeployingName();
    virtual bool obtainTopology(Network* network);
};

} /* namespace domain */
#endif /* TORUSGRIDDEPLOYING_H_ */
