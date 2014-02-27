/*
 * InfectionProtocol.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineProtocol.h"

namespace protocols {

ByzantineProtocol::ByzantineProtocol() {
	byzantineProb = 0;
	nothingProb = 0;
	statisticInfo = new NetworkStatistic();
	tolerance = NULL;
}

ByzantineProtocol::ByzantineProtocol(double byzantineP, double nothingP)
{
	byzantineProb = byzantineP;
	nothingProb = nothingP;
	statisticInfo = new NetworkStatistic();
	tolerance = NULL;
}

ByzantineProtocol::~ByzantineProtocol() {

}

void ByzantineProtocol::Initialize(Network* network, double byzantineP, double nothingP)
{
	byzantineProb = byzantineP;
	nothingProb = nothingP;
	//Reset(network);
	//RandomByzantine(network);
}

void ByzantineProtocol::Refresh(Network* network, bool hubOnly)
{
	Reset(network);
	RandomByzantine(network, hubOnly);
}

void ByzantineProtocol::Reset(Network* network)
{
	NetworkProtocol::Reset(network);
	vector<NodePtr>::iterator it = network->nodes.begin();
	while(it != network->nodes.end())
	{
//		(*it)->state = Sane;
//		//(*it)->disconnectedNodes.clear();
//		(*it)->connectedAreaNumber = 0;
		(*it)->Reset();
		it++;
	}
	statisticInfo->Reset();
}

void ByzantineProtocol::RandomByzantine(Network* network, bool selectHub)
{
	int seed = rand() % network->nodes.size();

	while (selectHub && network->nodes[seed]->D < (network->avgDegree * 3))
	{
		seed = rand() % network->nodes.size();
	}
	network->nodes[seed]->state = Infected;
	network->info.seedId = seed;
	network->info.seedDegree = network->nodes[seed]->D;
	network->info.seedDiameter = network->nodes[seed]->diameter;
	network->info.numberOfInfectedNodes = 1;
	//PropagateFault(network);
}

void ByzantineProtocol::CallbackReceiveByzantineMessage(void* ptr, Message* message)
{
	ByzantineProtocol* instance = static_cast<ByzantineProtocol*>(ptr);
	instance->ReceiveByzantineMessage(message);
}

void ByzantineProtocol::ReceiveByzantineMessage(Message* message)
{
	NodeState destState = message->link->dest->state;
	if (destState == Infected)
	{
		message->status = Expired;
		return;
	}
	double next = (double)rand()/RAND_MAX;
	if (next < byzantineProb)
	{
		message->link->dest->state = Infected;
		message->link->dest->ownerNetwork->info.numberOfInfectedNodes++;
		// Send byzantine message to attack its neighbors
		BroadcastMessage(message->link->dest, CallbackReceiveByzantineMessage);
	}
	else if (next < byzantineProb + nothingProb)
	{
		// Send byzantine message to attack again
		SendMessage(message->link, CallbackReceiveByzantineMessage);
	}
	else
	{
		if (destState != Infected)
		{
			message->link->dest->ownerNetwork->info.numberOfDetectors++;
			tolerance->TolerateNode(message->link);//->dest, message->link->src);
		}
	}
	message->status = Expired;
}

bool ByzantineProtocol::RunStepCheckFinish(Network* network, bool (*stopCondition)(const Network&))
{
	RunNetworkStep(network);
	if (stopCondition(*network))
	{
		Finalize(network);
		return true;
	}
	else
		return false;
}

//string ByzantineProtocol::GetReportFilename()
//{
//	string filename = tolerance->GetToleranceName() + "_";
//	char* number = new char[15];
//	sprintf(number, "%.2f_%.2f_report.out", nothingProb, byzantineProb);
//	filename += number;
//	return filename;
//}
//
//string ByzantineProtocol::GetLogFilename()
//{
//	string filename = tolerance->GetToleranceName() + "_";
//	char* number = new char[15];
//	sprintf(number, "%.2f_%.2f.log", nothingProb, byzantineProb);
//	filename += number;
//	return filename;
//}

void ByzantineProtocol::Finalize(Network* network)
{
	statisticInfo->infections = network->info.numberOfInfectedNodes;
	statisticInfo->inactives = network->info.numberOfInactiveNodes;
	statisticInfo->detectors = network->info.numberOfDetectors;
	statisticInfo->sanes = network->nodes.size() - statisticInfo->infections - statisticInfo->inactives - statisticInfo->detectors;
	statisticInfo->lca = Network::findMaximumConnectedArea(network, &Node::isNodeState, Sane);
	statisticInfo->degree = network->info.seedDegree;
	statisticInfo->diameter = network->info.seedDiameter;
}

void ByzantineProtocol::BroadcastMessage(NodePtr sender, MessageReaction receivingAction)
{
//	list<NodePtr>::iterator it = sender->neighbors.begin();
//    for (; it != sender->neighbors.end(); it++)// Node neighbor in sender.Neighbors)
	vector<LinkPtr>::iterator it = sender->links.begin();
	for(; it != sender->links.end(); it++)
	{
		if ((*it)->state != Cut && (*it)->dest->state != Inactive)
		{
			Message* message = new ByzantineMessage((*it), sender->ownerNetwork->currentTimeSlot,
								byzantineProb, nothingProb);
			message->receivingAction = receivingAction;
			AddNewMessageToNetwork(sender->ownerNetwork, message);
		}
	}
}

void ByzantineProtocol::SendMessage(LinkPtr link, MessageReaction receivingAction)
{
	if (link->dest->state == Inactive)
		return;
	Message* message = new ByzantineMessage(link, link->src->ownerNetwork->currentTimeSlot, byzantineProb, nothingProb);
	message->receivingAction = receivingAction;
	AddNewMessageToNetwork(link->src->ownerNetwork, message);
}

void ByzantineProtocol::RunNetwork(Network* network, void (*startAction)(void* ptr, Network*), bool (*networkCondition)(const Network&))
{
	(*startAction)(this, network);
	bool isContinue = true;
	do
	{
		isContinue = !RunStepCheckFinish(network, (*networkCondition));
	} while (isContinue);
}

void ByzantineProtocol::RunFault(Network* network)
{
	RunNetwork(network, &CallbackPropagateFault, &Network::noNewMessageInNetwork);
}

void ByzantineProtocol::CallbackPropagateFault(void* ptr, Network* network)
{
	ByzantineProtocol* instance = static_cast<ByzantineProtocol*>(ptr);
	instance->PropagateFault(network);
}

void ByzantineProtocol::PropagateFault(Network* network)
{
	Node* firstInfected = network->nodes[network->info.seedId];
	//if (Tools::Exists(firstInfected->neighbors, &Node::isNodeState, Sane))
	Logger::Write(firstInfected->diameter, "");
	BroadcastMessage(firstInfected, CallbackReceiveByzantineMessage);
	network->currentTimeSlot++;
}

}
/* namespace protocols */
