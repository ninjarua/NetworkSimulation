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

void NetworkProtocol::AddNewMessageToNetwork(Network*& network, Message*& message)
{
	network->newMessages.push_back(message);
	network->messageCount++;
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
            AddNewMessageToNetwork(sender->ownerNetwork, message);
        }
    }
}

void NetworkProtocol::SendMessage(NodePtr sender, NodePtr receiver, MessageReaction receivingAction)
{
    if (receiver->state == Inactive)
        return;
    Message* message = new Message(sender, receiver, sender->ownerNetwork->currentTimeSlot);
    message->receivingAction = receivingAction;
    AddNewMessageToNetwork(receiver->ownerNetwork, message);
}

void NetworkProtocol::SendMessage(NodePtr sender, NodePtr receiver, MessageReaction receivingAction, Message* message)
{
    message->creationTime = sender->ownerNetwork->currentTimeSlot;
    message->receivingAction = receivingAction;
    AddNewMessageToNetwork(receiver->ownerNetwork, message);
}

void NetworkProtocol::Initialize(Network* network)
{
    Reset(network);
}

void NetworkProtocol::Reset(Network* network)
{
	network->info.numberOfDetectors = 0;
	network->info.numberOfInfectedNodes = 0;
	network->info.numberOfInactiveNodes = 0;
    //network->messages.clear();
    network->messageCount = 0;
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
    while (network->messageCount > 0)
    {
		list<Message*>::iterator it = network->newMessages.begin();
    	if (it != network->newMessages.end())
    	{
    		(*it)->receivingAction(this, (*it)->sender, (*it)->receiver, (*it));
    		//Logger::Write(*(*it), GetLogFilename(), ofstream::out | ofstream::app);
    		delete *it;
    		network->newMessages.pop_front();
    		network->messageCount--;
    	}
    }
//    while (network->messageCount > 0)
//    {
//    	int randId = rand() % network->messageCount;
//        list<Message*>::iterator it = network->messages.begin();
//    	for (; randId > 0; randId--)
//    	{
//    		it++;
//    	}
//    	if (it == network->messages.end())
//    		break;
//        if ((*it)->status == Sending && (*it)->creationTime < network->currentTimeSlot)
//        {
//        	(*it)->receivingAction(this, (*it)->sender, (*it)->receiver, (*it));
//        	//Logger::Write(*(*it), GetLogFilename(), ofstream::out | ofstream::app);
//            delete *it;
//            network->messages.erase(it);
//            network->messageCount--;
//            //RemoveMessageFromNetwork(network, it);
//        }
//    }
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
