/*
 * Tools.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef TOOLS_H_
#define TOOLS_H_

using namespace std;
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <typeinfo>
//#include <boost/smart_ptr/shared_ptr.hpp>
#include "Logger.h"

//typedef

class Tools{
public:
	Tools(){};
	virtual ~Tools();

	template<typename T>
	static void EraseAll(list<T*>& listInput)
	{
		typename list<T*>::iterator it = listInput.begin();
		while(it != listInput.end())
		{
			delete *it;
			it = listInput.erase(it);
		}
		listInput.clear();
	}

	template<typename T>
	static void EraseAll(vector<T*>& listInput)
	{
		//vector<T*> result = vector<T*>();
		typename vector<T*>::iterator it = listInput.end();
		while(it > listInput.begin())
		{
			it--;
			if (it != listInput.end() && *it != NULL)
			{
				delete *it;
				it = listInput.erase(it);
			}
		}
		listInput.clear();
	}

	template<typename T>
	static bool Contain(vector<T>& lst, T value)
	{
		int size = lst.size();
		int left = 0;
		int right = size - 1;
		int mid;
		while (left <= right)
		{
			mid = (left + right)/2;
			T midValue = lst[mid];
			if (value > midValue)
				left = mid + 1;
			else if(value < midValue)
				right = mid - 1;
			else
				return true;
		}
		return false;
	}
};
#endif /* TOOLS_H_ */
