/*
 * InfectionProtocol.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineProtocol.h"

namespace protocols {

//ByzantineProtocol* ByzantineProtocol::_fault = NULL;
//ByzantineProtocol* ByzantineProtocol::GetInstance(double byzantineProb, double dectectingProb)
//{
//    if (_fault == NULL)
//        _fault = new ByzantineProtocol(byzantineProb, dectectingProb);
//    return _fault;
//}

ByzantineProtocol::ByzantineProtocol() {

}

ByzantineProtocol::ByzantineProtocol(double byzantineP, double nothingP)
{
	byzantineProb = byzantineP;
	nothingProb = nothingP;
}

ByzantineProtocol::~ByzantineProtocol() {

}

NetworkInfo* ByzantineProtocol::GetNetworkInfo(Network* network)
{
    return network->info;
}

void ByzantineProtocol::Initialize(Network* network, double byzantineP, double nothingP)
{
    byzantineProb = byzantineP;
    nothingProb = nothingP;
    Reset(network);
    RandomByzantine(network);
}

void ByzantineProtocol::Refresh(Network* network)
{
    Reset(network);
    RandomByzantine(network);
}

void ByzantineProtocol::Reset(Network* network)
{
    NetworkProtocol::Reset(network);
    vector<Node*>::iterator it = network->nodes->begin();
    while(it != network->nodes->end())
    {
        (*it)->state = Sane;
        (*it)->detectedByzantines->clear();
        (*it)->disconnectedNodes->clear();
        (*it)->connectedAreaNumber = 0;
    }
    GetNetworkInfo(network)->listInfectedNodes->clear();
    GetNetworkInfo(network)->listDetectors->clear();
    Tools::RemoveWithPredicate(*network->nodes, &Node::isNodeState, Inactive);
}

void ByzantineProtocol::RandomByzantine(Network* network)
{
    int seed = rand() % network->nodes->size();
    network->nodes->at(seed)->state = Infected;
    GetNetworkInfo(network)->listInfectedNodes->push_back(network->nodes->at(seed));
    PropagateFault(network);
}

void ByzantineProtocol::CallbackReceiveByzantineMessage(void* ptr, Node* sender, Node* receiver, Message* message)
{
	ByzantineProtocol* instance = static_cast<ByzantineProtocol*>(ptr);
	instance->ReceiveByzantineMessage(sender, receiver, message);
}

void ByzantineProtocol::ReceiveByzantineMessage(Node* sender, Node* receiver, Message* message)
{
    double next = (double)rand()/RAND_MAX;
    if (receiver->state == Infected || receiver->disconnectedNodes->find(sender) != receiver->disconnectedNodes->end())
    {
        message->status = Expired;
        return;
    }
    if (next < byzantineProb)
    {
        if (receiver->state != Inactive)
        {
            receiver->state = Infected;
            Tools::Remove(*receiver->OwnerNetwork->info->listDetectors, receiver);
            Tools::Remove(*receiver->OwnerNetwork->info->listInfectedNodes, receiver);
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

bool ByzantineProtocol::RunStepCheckFinish(Network* network, bool (*stopCondition)(Network*))
{
	vector<Node*>* listDetectors = GetNetworkInfo(network)->listDetectors;

	for (vector<Node*>::iterator it = listDetectors->begin(); it != listDetectors->end(); it++)//network.GetNodes())
	{
		(*it)->state = Inactive;
	}
	GetNetworkInfo(network)->listDetectors->clear();
	RunNetworkStep(network);
	bool stop = (*stopCondition)(network);
	if (stop)
		Finalize(network); ;
	return stop;
	return true;
}

void ByzantineProtocol::Finalize(Network* network)
{
	vector<Node*>::iterator it;
    for (it = GetNetworkInfo(network)->listDetectors->begin(); it != GetNetworkInfo(network)->listDetectors->end(); it++)
        (*it)->state = Inactive;
}

void ByzantineProtocol::RunNetwork(Network* network, void (*startAction)(Network*), bool (*stopCondition)(Network*))
{
    (*startAction)(network);
    do
    {
        for (vector<Node*>::iterator it = GetNetworkInfo(network)->listDetectors->begin();
        		it != GetNetworkInfo(network)->listDetectors->end(); it++)
        {
            (*it)->state = Inactive;
        }
        GetNetworkInfo(network)->listDetectors->clear();
    } while (!RunStepCheckFinish(network, (*stopCondition)));
            //&& network.CheckCollision(network.CollisionChecking));
    Finalize(network);
}

void ByzantineProtocol::RunFault(Network* network)
{
	RunNetwork(network, &PropagateFault, &Network::noNewMessageInNetwork);
}

void ByzantineProtocol::PropagateFault(Network* network)
{
	for (vector<Node*>::iterator it = GetNetworkInfo(network)->listInfectedNodes->begin();
			it != GetNetworkInfo(network)->listInfectedNodes->end(); it++)
	{
		if (Tools::Exists(*(*it)->neighbors, &Node::isNodeState, Sane))
			BroadcastMessage(*it, CallbackReceiveByzantineMessage);
	}
	network->currentTimeSlot++;
}

} /* namespace protocols */
