/*
 * TorusGridDeploying.cc
 *
 *  Created on: Jun 1, 2013
 *      Author: thanh
 */

#include "TorusGridDeploying.h"

namespace deployment {

TorusGridDeploying::TorusGridDeploying() {
	// TODO Auto-generated constructor stub

}

TorusGridDeploying::~TorusGridDeploying() {
	// TODO Auto-generated destructor stub
}

bool TorusGridDeploying::ObtainTopology(Network* network)
{
    Deploying::ObtainTopology(network);
    if (networkTopology.Distance < networkTopology.D0)
    {
        return false;
    }
    int sqrtNumNodes = (int)sqrt(networkTopology.NumNodes);
    if (sqrtNumNodes != sqrt(networkTopology.NumNodes))
    {
        return false;
    }
    for (int i = 0; i < networkTopology.NumNodes; i++)
    {
        network->AddNode(new Node(GetPosX(i), GetPosY(i)));
    }
    networkTopology.XTerr = networkTopology.Distance * (sqrt(networkTopology.NumNodes) - 1);
    networkTopology.YTerr = networkTopology.Distance * (sqrt(networkTopology.NumNodes) - 1);
    return true;
}

double TorusGridDeploying::GetPosX(int nodeSequenceId)
{
    int sqrtNumNodes = (int)sqrt(networkTopology.NumNodes);
    return (nodeSequenceId % sqrtNumNodes) * networkTopology.Distance;
}

double TorusGridDeploying::GetPosY(int nodeSequenceId)
{
    int sqrtNumNodes = (int)sqrt(networkTopology.NumNodes);
    return (nodeSequenceId / sqrtNumNodes) * networkTopology.Distance;
}

bool TorusGridDeploying::IsNeighbors(const Network& network, const Node& node, const Node& neighbor)
{
    double Xdist = node.posX - neighbor.posX;
    double Ydist = node.posY - neighbor.posY;
    if ((node.posX == 0 && neighbor.posX == networkTopology.XTerr)
        || (node.posX == networkTopology.XTerr && neighbor.posX == 0))
    {
        Xdist += networkTopology.XTerr + networkTopology.Distance;
    }
    if ((node.posY == 0 && neighbor.posY == networkTopology.YTerr)
        || (node.posY == networkTopology.YTerr && neighbor.posY == 0))
    {
        Ydist += networkTopology.YTerr + networkTopology.Distance;
    }
    // distance between a given pair of nodes
    return pow((Xdist * Xdist + Ydist * Ydist), 0.5) <= network.transRange;
}

string TorusGridDeploying::GetDeployingName()
{
	return "TorusGrid";
}

void TorusGridDeploying::CreateInformationOfGraph(Network* network)
{
    Deploying::CreateInformationOfGraph(network);
//    foreach (TorusNode node in network.GetNodes())
//    {
//        node.AssignNodeToPort();
//    }
}

} /* namespace domain */
