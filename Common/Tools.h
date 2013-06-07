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
	static void EraseAll(vector<T*>& listInput)
	{
		vector<T*> result = vector<T*>();
		typename vector<T*>::iterator it = listInput.begin();
		while(it != listInput.end())
		{
			delete *it;
			it = listInput.erase(it);
		}
		listInput.clear();
	}
//
//	template<typename T>
//	static void EraseAll(vector< shared_ptr<T> >& listInput)
//	{
//		vector< shared_ptr<T> > result = vector< shared_ptr<T> >();
//		typename vector< shared_ptr<T> >::iterator it = listInput.begin();
//		while(it != listInput.end())
//		{
//			(*it).reset();
//			//delete ptr;
//			it = listInput.erase(it);
//		}
//		listInput.clear();
//	}

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
//
//	template<class T>
//	static void FindAllToVector(list< shared_ptr<T> >& inputVector, list< shared_ptr<T> >& outputVector, bool (*pCondition)(const T&))
//	{
//		typename list< shared_ptr<T> >::iterator it = inputVector.begin();
//		while(it != inputVector.end())
//		{
//			if ((*pCondition)(*(*it)))
//			{
//				outputVector.push_back(*it);
//				//Logger::Write(*(*it), "debug2.out", ofstream::out|ofstream::app);
//			}
//			it++;
//		}
//	}

	template<class T>
	static void FindAllToVector(list<T*>& inputVector, list<T*>& outputVector, bool (*pCondition)(const T&))
	{
		typename list<T*>::iterator it = inputVector.begin();
		while(it != inputVector.end())
		{
			if ((*pCondition)(*(*it)))
			{
				outputVector.push_back(*it);
				//Logger::Write(*(*it), "debug2.out", ofstream::out|ofstream::app);
			}
			it++;
		}
	}
//
//	template<class T, typename U>
//	static void FindAllToVector(vector< shared_ptr<T> >& inputVector, list< shared_ptr<T> >& outputVector, bool (*pCondition)(const T&, const U&), const U& condition)
//	{
//		typename vector< shared_ptr<T> >::iterator it = inputVector.begin();
//		while(it != inputVector.end())
//		{
//			if ((*pCondition)(*(*it), condition))
//			{
//				outputVector.push_back(*it);
//				//Logger::Write(*(*it), "debug2.out", ofstream::out|ofstream::app);
//			}
//			it++;
//		}
//	}

	template<class T, typename U>
	static void FindAllToVector(vector<T*>& inputVector, list<T*>& outputVector, bool (*pCondition)(const T&, const U&), const U& condition)
	{
		typename vector<T*>::iterator it = inputVector.begin();
		while(it != inputVector.end())
		{
			if ((*pCondition)(*(*it), condition))
			{
				outputVector.push_back(*it);
				//Logger::Write(*(*it), "debug2.out", ofstream::out|ofstream::app);
			}
			it++;
		}
	}
//
//	template<class T>
//	static long CountAll(const list< shared_ptr<T> >& listInput, bool (*pCondition)(const T&))
//	{
//		long count = 0;
//		typename vector< shared_ptr<T> >::const_iterator it = listInput.begin();
//		while(it != listInput.end())
//		{
//			if ((*pCondition)(*(*it)))
//				count++;
//			it++;
//		}
//		return count;
//	}

	template<class T>
	static long CountAll(const list<T*>& listInput, bool (*pCondition)(const T&))
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
//
//	template<class T, typename U>
//	static long CountAll(const vector< shared_ptr<T> >& listInput, bool (*pCondition)(const T&, const U&), const U& condition)
//	{
//		long count = 0;
//		typename vector< shared_ptr<T> >::const_iterator it = listInput.begin();
//		while(it != listInput.end())
//		{
//			if ((*pCondition)(*(*it), condition))
//				count++;
//			it++;
//		}
//		return count;
//	}

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

//	template<class T, typename U>
//	static int DetachWithPredicate(list< shared_ptr<T> >& vectorInput, bool (*pCondition)(const T&, U), U condition)
//	{
//		int count = 0;
//		typename list< shared_ptr<T> >::iterator it(vectorInput.begin());
//		while(it != vectorInput.end())
//		{
//			if ((*pCondition)(*(*it), condition))
//			{
//				it = vectorInput.erase(it);
//				count++;
//			}
//			else
//				it++;
//		}
//		return count;
//	}

	template<class T, typename U>
	static int DetachWithPredicate(list<T*>& vectorInput, bool (*pCondition)(const T&, U), U condition)
	{
		int count = 0;
		typename list<T*>::iterator it(vectorInput.begin());
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
	static int RemoveWithPredicate(list<T*>& vectorInput, bool (*pCondition)(const T&))
	{
		int count = 0;
		typename list<T*>::iterator it = vectorInput.begin();
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
	static bool Remove(list<T>& vectorInput, T& item)
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

//	template<class T>
//	static bool Exists(const list< shared_ptr<T> >& listInput, bool (*pCondition)(const T&))
//	{
//		typename list< shared_ptr<T> >::const_iterator it = listInput.begin();
//		while(it != listInput.end())
//		{
//			if ((*pCondition)(*(*it)))
//				return true;
//			it++;
//		}
//		return false;
//	}

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

//	template<class T, typename U>
//	static bool Exists(const list< shared_ptr<T> >& listInput, bool (*pCondition)(const T&, const U&), const U& condition)
//	{
//		typename list< shared_ptr<T> >::const_iterator it = listInput.begin();
//		while(it != listInput.end())
//		{
//			if ((*pCondition)(*(*it), condition))
//				return true;
//			it++;
//		}
//		return false;
//	}

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
