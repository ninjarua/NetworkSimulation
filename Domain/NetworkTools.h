/*
 * NetworkTools.h
 *
 *  Created on: Jun 10, 2013
 *      Author: thanh
 */

#ifndef NETWORKTOOLS_H_
#define NETWORKTOOLS_H_

#include "Node.h"
#include "Tools.h"

namespace domain{

class NetworkTools
{
public:
	static bool HasCommonNeighborsExcept(NodePtr n1, NodePtr n2, NodePtr exception)
	{
		list<NodePtr>::iterator it = n1->neighbors.begin();
		for (; it != n1->neighbors.end(); it++)
			if ((*it)->id != exception->id && Tools::Contain(n2->neighbors, *it))
				return true;
		return false;
	}
};
}

#endif /* NETWORKTOOLS_H_ */
