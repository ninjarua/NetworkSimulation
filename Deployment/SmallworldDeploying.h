/*
 * SmallworldDeploying.h
 *
 *  Created on: Jul 26, 2013
 *      Author: thanhnd
 */

#ifndef SMALLWORLDDEPLOYING_H_
#define SMALLWORLDDEPLOYING_H_

#include "FixedRangeRandomDeploying.h"

namespace deployment {

class SmallworldDeploying: public FixedRangeRandomDeploying {
	int numberOfLongEdge;
	int numberOfShortEdge;
	bool isLongEdgeNeighbors(const Network& network, const Node& node, const Node& neighbor);
public:
	SmallworldDeploying();
	SmallworldDeploying(int numberNodes, int xTerr, int yTerr, int range, int noOfShortEdge, double noOfLongEdge);
	virtual ~SmallworldDeploying();
	string getDeployingName();
	void neighborInitialization(Network* network);
};

} /* namespace domain */
#endif /* SMALLWORLDDEPLOYING_H_ */
