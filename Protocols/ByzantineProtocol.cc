/*
 * InfectionProtocol.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineProtocol.h"

namespace protocols {

ByzantineProtocol::ByzantineProtocol() {

}

ByzantineProtocol::ByzantineProtocol(double byzantineP, double nothingP)
{
	byzantineProb = byzantineP;
	nothingProb = nothingP;
	statisticInfo = new NetworkStatistic();
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

void ByzantineProtocol::Refresh(Network* network)
{
    Reset(network);
    RandomByzantine(network);
}

void ByzantineProtocol::Reset(Network* network)
{
    NetworkProtocol::Reset(network);
    vector<NodePtr>::iterator it = network->nodes.begin();
    while(it != network->nodes.end())
    {
        (*it)->state = Sane;
        (*it)->detectedByzantines.clear();
        (*it)->disconnectedNodes.clear();
        (*it)->connectedAreaNumber = 0;
        it++;
    }
    statisticInfo->Reset();
}

void ByzantineProtocol::RandomByzantine(Network* network)
{
    int seed = rand() % network->nodes.size();
    network->nodes.at(seed)->state = Infected;
    network->info.seedId = seed;
    network->info.numberOfInfectedNodes = 1;
    //PropagateFault(network);
}

void ByzantineProtocol::CallbackReceiveByzantineMessage(void* ptr, NodePtr sender, NodePtr receiver, Message* message)
{
	ByzantineProtocol* instance = static_cast<ByzantineProtocol*>(ptr);
	instance->ReceiveByzantineMessage(sender, receiver, message);
}

void ByzantineProtocol::ReceiveByzantineMessage(NodePtr sender, NodePtr receiver, Message* message)
{
    if (receiver->state == Infected || receiver->disconnectedNodes.find(sender) != receiver->disconnectedNodes.end())
    {
        message->status = Expired;
        return;
    }
    double next = (double)rand()/RAND_MAX;
    if (next < byzantineProb)
    {
        if (receiver->state != Inactive)
        {
            receiver->state = Infected;
            receiver->ownerNetwork->info.numberOfInfectedNodes++;
            // Send byzantine message to attack its neighbors
            BroadcastMessage(receiver, CallbackReceiveByzantineMessage);
        }
    }
    else if (next < byzantineProb + nothingProb)
    {
        // Send byzantine message to attack again
        SendMessage(sender, receiver, CallbackReceiveByzantineMessage);
    }
    else
    {
        if (receiver->state != Inactive && receiver->state != Infected)
        {
            tolerance->TolerateNode(receiver, sender);
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

string ByzantineProtocol::GetReportFilename()
{
	string filename = tolerance->GetToleranceName() + "_";
	char* number = new char[15];
	sprintf(number, "%.2f_%.2f_report.out", nothingProb, byzantineProb);
	filename += number;
	return filename;
}

string ByzantineProtocol::GetLogFilename()
{
	string filename = tolerance->GetToleranceName() + "_";
	char* number = new char[15];
	sprintf(number, "%.2f_%.2f.log", nothingProb, byzantineProb);
	filename += number;
	return filename;
}

void ByzantineProtocol::Finalize(Network* network)
{
    statisticInfo->infections = network->info.numberOfInfectedNodes;
    statisticInfo->inactives = network->info.numberOfInactiveNodes;
    statisticInfo->detectors = network->info.numberOfDetectors;
    statisticInfo->sanes = network->nodes.size() - statisticInfo->infections - statisticInfo->inactives - statisticInfo->detectors;
    statisticInfo->lca = Network::FindMaximumConnectedArea(network, &Node::isNodeState, Sane);
}

void ByzantineProtocol::BroadcastMessage(NodePtr sender, MessageReaction receivingAction)
{
	list<NodePtr>::iterator it = sender->neighbors.begin();
    for (; it != sender->neighbors.end(); it++)// Node neighbor in sender.Neighbors)
    {
        if ((*it)->state != Inactive)
        {
            Message* message = new ByzantineMessage(sender, *it, sender->ownerNetwork->currentTimeSlot, byzantineProb, nothingProb);
            message->receivingAction = receivingAction;
            AddNewMessageToNetwork(sender->ownerNetwork, message);
        }
    }
}

void ByzantineProtocol::SendMessage(NodePtr sender, NodePtr receiver, MessageReaction receivingAction)
{
    if (receiver->state == Inactive)
        return;
    Message* message = new ByzantineMessage(sender, receiver, sender->ownerNetwork->currentTimeSlot, byzantineProb, nothingProb);
    message->receivingAction = receivingAction;
    AddNewMessageToNetwork(sender->ownerNetwork, message);
}

void ByzantineProtocol::RunNetwork(Network* network, void (*startAction)(void* ptr, Network*), bool (*networkCondition)(const Network&))
{
    (*startAction)(this, network);
    bool isContinue = true;
    do
    {
//    	vector<NodePtr>::iterator it = network->info.listDetectors.begin();
//        for (; it != network->info.listDetectors.end(); it++)
//        {
//            (*it)->state = Inactive;
//        }
//        network->info.listDetectors.clear();
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
	if (Tools::Exists(firstInfected->neighbors, &Node::isNodeState, Sane))
		BroadcastMessage(firstInfected, CallbackReceiveByzantineMessage);
	network->currentTimeSlot++;
}

}
/* namespace protocols */
