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
	virtual bool IsNeighbors(const Network& network, const Node& node, const Node& neighbor);

	string GetDeployingName();
	double GetPosX(int nodeSequenceId);
	double GetPosY(int nodeSequenceId);

	bool ObtainTopology(Network* network);
};

} /* namespace domain */
#endif /* ERRANDOMDEPLOYING_H_ */
