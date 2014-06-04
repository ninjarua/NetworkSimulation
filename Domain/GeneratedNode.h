/*
 * RandomNode.h
 *
 *  Created on: May 31, 2014
 *      Author: thanh
 */

#ifndef RANDOMNODE_H_
#define RANDOMNODE_H_
#include "Node.h"

namespace domain {

class GeneratedNode : public Node{
public:
	double posX;
	double posY;
	int D;
	int diameter;
	GeneratedNode();
	GeneratedNode(Network* network);
	GeneratedNode(double x, double y);
	virtual ~GeneratedNode();
	friend ostream& operator<<(ostream& os, const GeneratedNode& node);

private:
	void Initialize();
};

} /* namespace protocols */

#endif /* RANDOMNODE_H_ */
