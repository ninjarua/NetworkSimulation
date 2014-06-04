/*
 * ScaleFreeDeploying.h
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#ifndef SCALEFREEDEPLOYING_H_
#define SCALEFREEDEPLOYING_H_

#include "Deploying.h"
#include "Network.h"

using namespace domain;

namespace deployment {

class ScaleFreeDeploying : public Deploying {
	int size0;
	int mEdge;
	int size;
	void increaseClique(Network* network, int newSize);
	void attachNewNode(Network* network, int index, unsigned long& totalDegree);
public:
	ScaleFreeDeploying();
	ScaleFreeDeploying(int m0, int m, int N);
	virtual ~ScaleFreeDeploying();
	virtual bool isNeighbors(const Network& network, const NodePtr node, const NodePtr neighbor);
    void neighborInitialization(Network* network);

	string getDeployingName();
	double getPosX(int nodeSequenceId);
	double getPosY(int nodeSequenceId);

	bool obtainTopology(Network* network);
};
} /* namespace deployment */
#endif /* SCALEFREEDEPLOYING_H_ */
