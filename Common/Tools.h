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

class Tools{
public:
	Tools(){};
	virtual ~Tools();

	template<typename T>
	static void EraseAll(list<T*>& listInput)
	{
		list<T*> result = list<T*>();
		typename list<T*>::iterator it = listInput.begin();
		while(it != listInput.end())
		{
			delete *it;
			it = listInput.erase(it);
		}
		listInput.clear();
	}

	template<typename T>
	static void EraseAll(list<T>& listInput)
	{
		list<T> result = list<T>();
		typename list<T>::iterator it = listInput.begin();
		while(it != listInput.end())
		{
			it = listInput.erase(it);
		}
		listInput.clear();
	}

	template<class T>
	static void FindAllToVector(const vector<T*>& inputVector, vector<T*>& outputVector, bool (*pCondition)(const T&))
	{
		typename vector<T*>::const_iterator it = inputVector.begin();
		while(it != inputVector.end())
		{
			if ((*pCondition)(*(*it)))
				outputVector.push_back(*it);
			it++;
		}
	}

	template<class T, typename U>
	static void FindAllToVector(const vector<T*>& inputVector, vector<T*>& outputVector, bool (*pCondition)(const T&, const U&), const U& condition)
	{
		typename vector<T*>::const_iterator it = inputVector.begin();
		while(it != inputVector.end())
		{
			if ((*pCondition)(*(*it), condition))
				outputVector.push_back(*it);
			it++;
		}
	}

	template<class T>
	static long CountAll(const vector<T*>& listInput, bool (*pCondition)(const T&))
	{
		long count = 0;
//		for(unsigned int i = 0; i < listInput.size(); i++)
		typename vector<T*>::const_iterator it = listInput.begin();
		while(it != listInput.end())
		{
			if ((*pCondition)(*(*it)))
				count++;
			it++;
		}
		return count;
	}

	template<class T, typename U>
	static long CountAll(const vector<T*>& listInput, bool (*pCondition)(const T&, const U&), const U& condition)
	{
		long count = 0;
		typename vector<T*>::const_iterator it = listInput.begin();
		while(it != listInput.end())
		{
			if ((*pCondition)(*(*it), condition))
				count++;
			it++;
		}
		return count;
	}

//	template<class T>
//	static list<T> FindAllToList(const vector<T>& listInput, bool (*pCondition)(T))
//	{
//		list<T> result = list<T>();
//		typename vector<T>::const_iterator it = listInput.begin();
//		while(it != listInput.end())
//		{
//			if ((*pCondition)(*it))
//				result.push_back(*it);
//			it++;
//		}
//		return result;
//	}
//
//	template<class T>
//	static list<T> ToList(const vector<T>& vectorInput)
//	{
//		list<T> result = list<T>();
//		typename vector<T>::const_iterator it = vectorInput.begin();
//		while(it != vectorInput.end())
//		{
//			result.push_back(*it);
//			it++;
//		}
//		return result;
//	}

	template<class T, typename U>
	static int DetachWithPredicate(vector<T*>& vectorInput, bool (*pCondition)(const T&, U), U condition)
	{
		int count = 0;
		typename vector<T*>::iterator it = vectorInput.begin();
		while(it != vectorInput.end())
		{
			if ((*pCondition)(*(*it), condition))
			{
				it = vectorInput.erase(it);
				count++;
			}
			else
				it++;
		}
		return count;
	}

//	template<class T, typename U>
//	static int RemoveWithPredicate(vector<T*>& vectorInput, bool (*pCondition)(const T&, U), U condition)
//	{
//		int count = 0;
//		typename vector<T*>::iterator it = vectorInput.begin();
//		while(it != vectorInput.end())
//		{
//			if ((*pCondition)(*(*it), condition))
//			{
//				delete *it;
//				it = vectorInput.erase(it);
//				count++;
//			}
//			else
//				it++;
//		}
//		return count;
//	}

	template<class T>
	static int RemoveWithPredicate(vector<T*>& vectorInput, bool (*pCondition)(const T&))
	{
		int count = 0;
		typename vector<T*>::iterator it = vectorInput.begin();
		while(it != vectorInput.end())
		{
			if ((*pCondition)(*(*it)))
			{
				delete *it;
				it = vectorInput.erase(it);
				count++;
			}
			else
				it++;
		}
		return count;
	}

	template<class T>
	static bool Remove(vector<T>& vectorInput, T& item)
	{
		typename vector<T>::iterator it = vectorInput.begin();
		while(it != vectorInput.end())
		{
			if ((*it) == item)
			{
				delete *it;
				it = vectorInput.erase(it);
				return true;
			}
			it++;
		}
		return false;
	}

	template<class T>
	static bool Exists(const list<T*>& listInput, bool (*pCondition)(const T&))
	{
		typename list<T*>::const_iterator it = listInput.begin();
		while(it != listInput.end())
		{
			if ((*pCondition)(*(*it)))
				return true;
			it++;
		}
		return false;
	}

	template<class T, typename U>
	static bool Exists(const list<T*>& listInput, bool (*pCondition)(const T&, const U&), const U& condition)
	{
		typename list<T*>::const_iterator it = listInput.begin();
		while(it != listInput.end())
		{
			if ((*pCondition)(*(*it), condition))
				return true;
			it++;
		}
		return false;
	}
};
#endif /* TOOLS_H_ */
