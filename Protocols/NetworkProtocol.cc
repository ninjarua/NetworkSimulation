/*
 * NetworkProtocol.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "NetworkProtocol.h"

namespace protocols {

NetworkProtocol::NetworkProtocol() {
	report = new ByzantineReport();
}

NetworkProtocol::~NetworkProtocol() {

}

void NetworkProtocol::BroadcastMessage(NodePtr sender, MessageReaction receivingAction)
{
	list<NodePtr>::iterator it;
    for (it = sender->neighbors.begin(); it != sender->neighbors.end(); it++)// Node neighbor in sender.Neighbors)
    {
        if ((*it)->state != Inactive)
        {
            Message* message = new Message(sender, *it, sender->ownerNetwork->currentTimeSlot);
            message->receivingAction = receivingAction;
            sender->ownerNetwork->newMessages.push_back(message);
        }
    }
}

void NetworkProtocol::SendMessage(NodePtr sender, NodePtr receiver, MessageReaction receivingAction)
{
    if (receiver->state == Inactive)
        return;
    Message* message = new Message(sender, receiver, sender->ownerNetwork->currentTimeSlot);
    message->receivingAction = receivingAction;
    sender->ownerNetwork->newMessages.push_back(message);
}

void NetworkProtocol::SendMessage(NodePtr sender, NodePtr receiver, MessageReaction receivingAction, Message* message)
{
    message->creationTime = sender->ownerNetwork->currentTimeSlot;
    message->receivingAction = receivingAction;
    sender->ownerNetwork->newMessages.push_back(message);
}

void NetworkProtocol::Initialize(Network* network)
{
    Reset(network);
}

void NetworkProtocol::Reset(Network* network)
{
    network->messages.clear();
    network->newMessages.clear();
    network->currentTimeSlot = 0;
}

void NetworkProtocol::RunNetwork(Network* network, void (*startAction)(void* ptr, Network*), bool (*networkCondition)(const Network&))
{
    (*startAction)(this, network);
    while (!(*networkCondition)(*network))
    {
        RunNetworkStep(network);
    }
}

void NetworkProtocol::RunNetworkStep(Network* network)
{
    network->messages.insert(network->messages.end(),
    		network->newMessages.begin(), network->newMessages.end());
    network->newMessages.clear();
    int size = network->messages.size();
    while (size > 0)
    {
    	int randId = rand() % size;
        list<Message*>::iterator it = network->messages.begin();
    	for (; randId > 0; randId--)
    	{
    		it++;
    	}
        if ((*it)->status == Sending && (*it)->creationTime < network->currentTimeSlot)
        {
        	(*it)->receivingAction(this, (*it)->sender, (*it)->receiver, (*it));
            delete *it;
            network->messages.erase(it);
        }
        size = network->messages.size();
    }
    network->currentTimeSlot++;
}

string NetworkProtocol::GetLogFilename()
{
	return "base.txt";
}

void NetworkProtocol::CreateReportString(Network& network)
{

}

} /* namespace protocols */
