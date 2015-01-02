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
#include <vector>

using namespace std;

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

	static bool ContainNode(vector<LinkPtr>& links, NodePtr node)
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

//	static LinkPtr GetLinkByDest(vector<LinkPtr>& links, NodePtr node)
//	{
//		int size = links.size();
//		int left = 0;
//		int right = size - 1;
//		int mid;
//		while (left <= right)
//		{
//			mid = (left + right)/2;
//			LinkPtr linkMid = links[mid];
//			if (node->id > linkMid->dest->id)
//				left = mid + 1;
//			else if(node->id < linkMid->dest->id)
//				right = mid - 1;
//			else
//				return linkMid;
//		}
//		return NULL;
//	}

	static LinkPtr GetSrcLinkPtr(vector<LinkPtr> links, const int& id)
	{
		int size = links.size();
		int left = 0;
		int right = size - 1;
		int mid;
		while (left <= right)
		{
			mid = (left + right)/2;
			LinkPtr linkMid = links.at(mid);
			if (id > linkMid->src->id)
				left = mid + 1;
			else if(id < linkMid->src->id)
				right = mid - 1;
			else
				return linkMid;
		}
		return NULL;
	}

	static LinkPtr GetLinkPtr(vector<LinkPtr> links, const int& id)
	{
		int size = links.size();
		int left = 0;
		int right = size - 1;
		int mid;
		while (left <= right)
		{
			mid = (left + right)/2;
			LinkPtr linkMid = links[mid];
			if (id > linkMid->dest->id)
				left = mid + 1;
			else if(id < linkMid->dest->id)
				right = mid - 1;
			else
				return linkMid;
		}
		return NULL;
	}

	static bool ContainNodeIn2Hop(list<Link2Hop*>& links, NodePtr node, list<Link2Hop*>::iterator& it)
	{
		it = links.begin();
		while (it != links.end() && (*it)->dest->id <= node->id)
		{
			if ((*it)->dest->id == node->id)
				return true;
			it++;
		}
		return false;
	}

	static bool ContainNodeIn2Hop(vector<Link2Hop*> links, NodePtr node)
	{
		int size = links.size();
		int left = 0;
		int right = size - 1;
		int mid;
		while (left <= right)
		{
			mid = (left + right)/2;
			Link2Hop* linkMid = links[mid];
			if (node->id > linkMid->dest->id)
				left = mid + 1;
			else if(node->id < linkMid->dest->id)
				right = mid - 1;
			else
				return true;
		}
		return false;
	}

	static void InsertIntoSortedLinks2Hop(list<Link2Hop*>& lstLinks, Link2Hop* link)
	{
		list<Link2Hop*>::iterator it = lstLinks.begin();
		while (it != lstLinks.end() && (*it)->dest->id < link->dest->id)
		{
			it++;
		}
		lstLinks.insert(it, link);
	}

	static void MoveToVector(list<Link2Hop*>& lstLinks, vector<Link2Hop*>& vectorLinks)
	{
		while (!lstLinks.empty())
		{
			//Link2Hop* l = new Link2Hop(*lstLinks.front());
			vectorLinks.push_back(lstLinks.front());
			lstLinks.pop_front();
		}
	}

	static LinkPtr GetReverseLink(LinkPtr link)
	{
		//LinkPtr srcLink = GetSrcLinkPtr(link->src->srcLinks, link->dest->id);
		return link->reverseLink;
	}
};
}

#endif /* NETWORKTOOLS_H_ */
