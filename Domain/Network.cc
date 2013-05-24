/*
 * Network.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#include "Network.h"
namespace domain {

Network::Network() {
	currentTimeSlot = 0;
	nodes = new vector<Node*>();
	messages = new vector<Message*>();
	newMessages = new vector<Message*>();
}

Network::~Network() {
	sequenceId = 0;
}
//
//vector<Node*>* Network::GetNodes()
//{
//	return _nodes;
//}
//
//vector<Message*>* Network::GetMessage()
//{
//	return _messages;
//}
//vector<Message*>* Network::GetNewMessage()
//{
//	return _newMessages;
//}

Node* Network::AddNode(Node* node)
{
	node->id = sequenceId++;
	nodes->push_back(node);
	node->OwnerNetwork = this;
	return node;
}

}
