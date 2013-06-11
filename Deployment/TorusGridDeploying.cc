/*
 * TorusGridDeploying.cc
 *
 *  Created on: Jun 1, 2013
 *      Author: thanh
 */

#include "TorusGridDeploying.h"

namespace deployment {

TorusGridDeploying::TorusGridDeploying()
{

}

TorusGridDeploying::TorusGridDeploying(int size) : Deploying() {
	topology->numNodes = size;
    topology->range = 1;
	int sqrtNumNodes = (int)sqrt(topology->numNodes);
	if (sqrtNumNodes != sqrt(topology->numNodes))
	{
		throw nsException("Error: on GRID topology, NUMBER_OF_NODES should be the square of a natural number");
	}
	topology->xTerr = topology->range * (sqrt(topology->numNodes) - 1);
	topology->yTerr = topology->range * (sqrt(topology->numNodes) - 1);
}

TorusGridDeploying::~TorusGridDeploying() {

}

bool TorusGridDeploying::obtainTopology(Network* network)
{
    Deploying::obtainTopology(network);
    int sqrtNumNodes = (int)sqrt(topology->numNodes);
    if (sqrtNumNodes != sqrt(topology->numNodes))
    {
        return false;
    }
    for (int i = 0; i < topology->numNodes; i++)
    {
    	NodePtr newNode(new Node(GetPosX(i), getPosY(i)));
        network->addNode(newNode);
    }
    topology->xTerr = topology->range * (sqrt(topology->numNodes) - 1);
    topology->yTerr = topology->range * (sqrt(topology->numNodes) - 1);
    network->transRange = topology->range;
    return true;
}

double TorusGridDeploying::GetPosX(int nodeSequenceId)
{
    int sqrtNumNodes = (int)sqrt(topology->numNodes);
    return (nodeSequenceId % sqrtNumNodes) * topology->range;
}

double TorusGridDeploying::getPosY(int nodeSequenceId)
{
    int sqrtNumNodes = (int)sqrt(topology->numNodes);
    return (nodeSequenceId / sqrtNumNodes) * topology->range;
}

bool TorusGridDeploying::isNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
    double Xdist = node.posX - neighbor.posX;
    double Ydist = node.posY - neighbor.posY;
    if ((node.posX == 0 && neighbor.posX == topology->xTerr)
        || (node.posX == topology->xTerr && neighbor.posX == 0))
    {
        Xdist += topology->xTerr + topology->range;
    }
    if ((node.posY == 0 && neighbor.posY == topology->yTerr)
        || (node.posY == topology->yTerr && neighbor.posY == 0))
    {
        Ydist += topology->yTerr + topology->range;
    }
    // distance between a given pair of nodes
    return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

string TorusGridDeploying::getDeployingName()
{
	return "TorusGrid";
}

void TorusGridDeploying::createInformationOfGraph(Network* network)
{
    Deploying::createInformationOfGraph(network);
//    foreach (TorusNode node in network.GetNodes())
//    {
//        node.AssignNodeToPort();
//    }
}

} /* namespace domain */
