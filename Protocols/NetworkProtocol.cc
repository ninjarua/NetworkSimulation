/*
 * NetworkProtocol.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "NetworkProtocol.h"

namespace protocols {

NetworkProtocol::NetworkProtocol() {
	// TODO Auto-generated constructor stub

}

NetworkProtocol::~NetworkProtocol() {
	// TODO Auto-generated destructor stub
}

void NetworkProtocol::BroadcastMessage(Node* sender, void (*action)(Node*, Node*, Message*))
{
	list<Node*>::iterator it;
    for (it = sender->neighbors->begin(); it != sender->neighbors->end(); it++)// Node neighbor in sender.Neighbors)
    {
        if ((*it)->state != Inactive)
        {
            Message* message = new Message(sender, *it, sender->ownerNetwork->currentTimeSlot);
            message->receivingAction = action;
            sender->ownerNetwork->newMessages->push_back(message);
        }
    }
}

void NetworkProtocol::SendMessage(Node* sender, Node* receiver, void (*action)(Node*, Node*, Message*))
{
    if (receiver->state == Inactive)
        return;
    Message* message = new Message(sender, receiver, sender->ownerNetwork->currentTimeSlot);
    message->receivingAction = action;
    sender->ownerNetwork->newMessages->push_back(message);
}

void NetworkProtocol::SendMessage(Node* sender, Node* receiver, void (*action)(Node*, Node*, Message*), Message* message)
{
    message->creationTime = sender->ownerNetwork->currentTimeSlot;
    message->receivingAction = action;
    sender->ownerNetwork->newMessages->push_back(message);
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

void NetworkProtocol::RunNetwork(Network* network, void (*startAction)(), bool (*pCondition)(Network))
{
    (*startAction)();
    while (!(*pCondition)(*network))
    {
        RunNetworkStep(network);
    }
}

bool isExpired(Message* m)
{
	return m->status == Expired;
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
        	(*messages)[i]->receivingAction((*messages)[i]->sender, (*messages)[i]->receiver, (*messages)[i]);
    }
    Tools::RemoveWithUnaryPredicate(*network->messages, isExpired);
    network->currentTimeSlot++;
}

void NetworkProtocol::CreateReportString(Network* network)
{
}

} /* namespace protocols */
