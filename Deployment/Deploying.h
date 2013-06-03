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
	Deploying();
	virtual ~Deploying();

	public:
		Topology* topology;

    protected:
        virtual void CreateInformationOfGraph(Network* network);
        virtual bool IsNeighbors(const Network& network, const Node& node, const Node& neighbor);
        virtual bool IsAllDistanceValid(const Network& network, const Node& node);
        virtual bool IsValidDistance(const Node& node, const Node& neighbor);
        virtual double GetCellLength();
        virtual double GetPosX(int nodeSequenceId);
        virtual double GetPosY(int nodeSequenceId);
	public:
        bool RunDeploy(Network* network);
        virtual string GetDeployingName();
        virtual bool ObtainTopology(Network* network);
	private:
        void NeighborInitialization(Network* network);
        //vector<Node*> FilterNode(vector<Node*> listInput, pNodeCondition nodeCondition);
};

} /* namespace deployment */
#endif /* DEPLOYING_H_ */
