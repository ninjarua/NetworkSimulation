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

namespace deployment {

class GridDeploying : public Deploying {
    virtual bool IsNeighbors(Network network, Node node, Node neighbor);
    virtual double GetPosX(int nodeSequenceId);
    virtual double GetPosY(int nodeSequenceId);
public:
    virtual bool ObtainTopology(Network* network);
	GridDeploying();
	virtual ~GridDeploying();
};

} /* namespace protocols */
#endif /* GRIDDEPLOYING_H_ */
