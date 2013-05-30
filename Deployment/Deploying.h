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
#include <stack>

#include "Topology.h"
#include "Network.h"

using namespace domain;

namespace deployment {

enum DeployingType { Ring = 0, TorusGrid = 1,
					Grid = 2, ER_Random = 3,
					FixedRange = 4, ScaleFree = 5};

typedef bool (*pNodeCondition)(Node*);

class Deploying {
public:
	Deploying();
	virtual ~Deploying();

	public:
		Topology* networkTopology;

    protected:
        virtual void CreateInformationOfGraph(Network* network);
        virtual bool IsNeighbors(Network network, Node node, Node neighbor);
        virtual bool IsAllDistanceValid(Network network, Node node);
        virtual bool IsValidDistance(Node node, Node neighbor);
        virtual double GetCellLength();
        virtual double GetPosX(int nodeSequenceId);
        virtual double GetPosY(int nodeSequenceId);
	public:
        int FindMaximumConnectedArea(Network* network, bool (*nodeCondition)(Node*, NodeState), NodeState state);
        bool RunDeploy(Network* network);
        virtual bool ObtainTopology(Network* network);
	private:
        void ConnectedAreaSpreading(Node* seed, int spreadingValue, bool (*nodeCondition)(Node*, NodeState), NodeState state);
        void NeighborInitialization(Network* network);
        stack<Node*>* LookingForNode(list<Node*>* listInput, bool (*nodeCondition)(Node*, NodeState), NodeState state);
        void AddingNewNodesWithFilter(stack<Node*>* stack, Node* consideringNode, bool (*nodeCondition)(Node*, NodeState),
        		NodeState state, int number, bool (*filter)(Node* n1, Node* n2, int number));
        bool static FilterDisconnectedNodeAndDifferentConnectedAreaNumber(Node* n1, Node* n2, int number);
        vector<Node*> FilterNode(vector<Node*> listInput, pNodeCondition nodeCondition);
};

} /* namespace deployment */
#endif /* DEPLOYING_H_ */
