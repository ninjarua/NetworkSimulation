/*
 * NetworkProtocol.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "NetworkProtocol.h"

namespace protocols {

NetworkProtocol::NetworkProtocol() {

}

NetworkProtocol::~NetworkProtocol() {

}

void NetworkProtocol::BroadcastMessage(Node* sender, void (*receivingAction)(void*, Node*, Node*, Message*))
{
	list<Node*>::iterator it;
    for (it = sender->neighbors->begin(); it != sender->neighbors->end(); it++)// Node neighbor in sender.Neighbors)
    {
        if ((*it)->state != Inactive)
        {
            Message* message = new Message(sender, *it, sender->OwnerNetwork->currentTimeSlot);
            message->receivingAction = receivingAction;
            sender->OwnerNetwork->newMessages->push_back(message);
        }
    }
}

void NetworkProtocol::SendMessage(Node* sender, Node* receiver, void (*receivingAction)(void*, Node*, Node*, Message*))
{
    if (receiver->state == Inactive)
        return;
    Message* message = new Message(sender, receiver, sender->OwnerNetwork->currentTimeSlot);
    message->receivingAction = receivingAction;
    sender->OwnerNetwork->newMessages->push_back(message);
}

void NetworkProtocol::SendMessage(Node* sender, Node* receiver, void (*receivingAction)(void*, Node*, Node*, Message*), Message* message)
{
    message->creationTime = sender->OwnerNetwork->currentTimeSlot;
    message->receivingAction = receivingAction;
    sender->OwnerNetwork->newMessages->push_back(message);
}

void NetworkProtocol::Initialize(Network* network)
{
    Reset(network);
}

void NetworkProtocol::Reset(Network* network)
{
    network->messages->clear();
    network->newMessages->clear();
    network->currentTimeSlot = 0;
}

void NetworkProtocol::RunNetwork(Network* network, void (*startAction)(Network*), bool (*networkCondition)(Network*))
{
    (*startAction)(network);
    while (!(*networkCondition)(network))
    {
        RunNetworkStep(network);
    }
}

void NetworkProtocol::RunNetworkStep(Network* network)
{
    network->messages->insert(network->messages->end(),
    		network->newMessages->begin(), network->newMessages->end());
	vector<Message*>* messages = network->messages;
    network->newMessages->clear();
    for (unsigned int i = 0; i < messages->size(); i++)
    {
        if ((*messages)[i]->status == Sending && (*messages)[i]->creationTime < network->currentTimeSlot)
        {
        	(*messages)[i]->receivingAction(this, (*messages)[i]->sender, (*messages)[i]->receiver, (*messages)[i]);
        }
    }
    Tools::RemoveWithPredicate(*network->messages, &Message::isMessageExpired);
    network->currentTimeSlot++;
}

void NetworkProtocol::CreateReportString(Network* network)
{
	string report = "";
	reportString  = report;
}

} /* namespace protocols */
