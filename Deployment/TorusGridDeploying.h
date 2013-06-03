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
    virtual bool IsNeighbors(const Network& network, const Node& node, const Node& neighbor);
    virtual double GetPosX(int nodeSequenceId);
    virtual double GetPosY(int nodeSequenceId);
    virtual void CreateInformationOfGraph(Network* network);
public:
    string GetDeployingName();
    virtual bool ObtainTopology(Network* network);
};

} /* namespace domain */
#endif /* TORUSGRIDDEPLOYING_H_ */
