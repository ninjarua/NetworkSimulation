/*
 * GridDeploying.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef GRIDDEPLOYING_H_
#define GRIDDEPLOYING_H_

#include <math.h>
#include "Deploying.h"
#include "nsException.h"

namespace deployment {

class GridDeploying : public Deploying {
    virtual bool IsNeighbors(const Network& network, const Node& node, const Node& neighbor);
    virtual double GetPosX(int nodeSequenceId);
    virtual double GetPosY(int nodeSequenceId);
public:
	string GetDeployingName();
    virtual bool ObtainTopology(Network* network);
    GridDeploying();
	GridDeploying(int size);
	virtual ~GridDeploying();
};

} /* namespace protocols */
#endif /* GRIDDEPLOYING_H_ */
