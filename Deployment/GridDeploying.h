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
    virtual bool isNeighbors(const Network& network, const Node& node, const Node& neighbor);
    virtual double getPosX(int nodeSequenceId);
    virtual double getPosY(int nodeSequenceId);
public:
	string getDeployingName();
    virtual bool obtainTopology(Network* network);
    GridDeploying();
	GridDeploying(int size);
	virtual ~GridDeploying();
};

} /* namespace protocols */
#endif /* GRIDDEPLOYING_H_ */
