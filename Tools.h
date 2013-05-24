/*
 * Tools.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef TOOLS_H_
#define TOOLS_H_

using namespace std;
#include <vector>
#include <list>

class Tools{
public:
	Tools(){};
	virtual ~Tools();

	template<class T>
	static vector<T> FindAllToVector(vector<T> listInput, bool (*pCondition)(T))
	{
		vector<T> result = vector<T>();
		for(unsigned int i = 0; i < listInput.size(); i++)
		{
			if ((*pCondition)(listInput[i]))
				result.push_back(listInput[i]);
		}
		return result;
	}

	template<class T>
	static list<T> FindAllToList(vector<T> listInput, bool (*pCondition)(T))
	{
		list<T> result = list<T>();
		for(int i = 0; i < listInput.size(); i++)
		{
			if ((*pCondition)(listInput[i]))
				result.push_back(listInput[i]);
		}
		return result;
	}

	template<class T>
	static list<T> ToList(vector<T> vectorInput)
	{
		list<T> result = list<T>();
		for(int i = 0; i < vectorInput.size(); i++)
		{
			result.push_back(vectorInput[i]);
		}
		return result;
	}

	template<class T, typename U>
	static int RemoveWithBinaryPredicate(vector<T>& vectorInput, bool (*pCondition)(T, U), U condition)
	{
		int count = 0;
		for(int i = vectorInput.size() - 1; i >= 0; i--)
			if ((*pCondition)(vectorInput[i], condition))
			{
				vectorInput.erase(vectorInput.begin() + i);
				count++;
			}
		return count;
	}

	template<class T>
	static int RemoveWithUnaryPredicate(vector<T>& vectorInput, bool (*pCondition)(T))
	{
		int count = 0;
		for(int i = vectorInput.size() - 1; i >= 0; i--)
			if ((*pCondition)(vectorInput[i]))
			{
				vectorInput.erase(vectorInput.begin() + i);
				count++;
			}
		return count;
	}
};
#endif /* TOOLS_H_ */
