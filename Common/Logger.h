/*
 * Logger.h
 *
 *  Created on: May 31, 2013
 *      Author: thanh
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "stdafx.h"
#include <fstream>

class Logger {
public:
	Logger(){};
	virtual ~Logger(){};

	template<class T>
	static void Write(T* instance, string filename, ofstream::openmode mode = ofstream::out)
	{
		ofstream f(filename.c_str(), mode);
		f << (*instance);
		f.close();
	}

	template<class T>
	static void Write(const T& instance, string filename, ofstream::openmode mode = ofstream::out)
	{
		ofstream f(filename.c_str(), mode);
		f << instance;
		f.close();
	}

	template<class T>
	static void Write(const T& instance, string (*printInstance)(const T&, string), string original, string filename, ofstream::openmode mode = ofstream::out)
	{
		ofstream f(filename.c_str(), mode);
		f << printInstance(instance, original);
		f.close();
	}
};

#endif /* LOGGER_H_ */