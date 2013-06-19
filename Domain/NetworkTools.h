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
#include <list>

namespace domain{

class NetworkTools
{
public:
	// Check if except the exception node, node n1 and n2 have the common neighbors or not?
	static bool HasCommonNeighborsExcept(NodePtr n1, NodePtr n2, NodePtr exception)
	{
		vector<LinkPtr>::iterator it = n1->links.begin();
		// for each neighbor of n1, check if it is in list neighbors of n2
		for (; it != n1->links.end(); it++)
			if ((*it)->dest->id != exception->id && ContainNode(n2->links, (*it)->dest))
				return true;
		return false;
	}

	static bool ContainNode(vector<LinkPtr> links, NodePtr node)
	{
		int size = links.size();
		int left = 0;
		int right = size - 1;
		int mid;
		while (left <= right)
		{
			mid = (left + right)/2;
			LinkPtr linkMid = links[mid];
			if (node->id > linkMid->dest->id)
				left = mid + 1;
			else if(node->id < linkMid->dest->id)
				right = mid - 1;
			else
				return true;
		}
		return false;
	}
};
}

#endif /* NETWORKTOOLS_H_ */
