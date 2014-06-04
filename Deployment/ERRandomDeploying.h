/*
 * ERRandomDeploying.h
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#ifndef ERRANDOMDEPLOYING_H_
#define ERRANDOMDEPLOYING_H_

#include "Deploying.h"

namespace deployment {

class ERRandomDeploying : public Deploying {
	double connectedProbability;
public:
	ERRandomDeploying();
	ERRandomDeploying(int numberNodes, double probability);
	virtual ~ERRandomDeploying();
	virtual bool isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor);

	string getDeployingName();
	double getPosX(int nodeSequenceId);
	double getPosY(int nodeSequenceId);

	bool obtainTopology(Network* network);
};

} /* namespace domain */
#endif /* ERRANDOMDEPLOYING_H_ */
