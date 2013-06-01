/*
 * Logger.h
 *
 *  Created on: May 31, 2013
 *      Author: thanh
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Network.h"
#include "NetworkStatistic.h"
#include "ByzantineReport.h"
#include "stdafx.h"
#include <fstream>

using namespace domain;

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

	//template<class T>
//	static void Write(const NetworkStatistic& instance, string filename, ofstream::openmode mode = ofstream::out)
//	{
//		ofstream f(filename.c_str(), mode);
//		f << instance;
//		f.close();
//	}
//
//	static void Write(const ByzantineReport& instance, string filename, ofstream::openmode mode = ofstream::out)
//	{
//		ofstream f(filename.c_str(), mode);
//		f << instance;
//		f.close();
//	}
//
//	static void Write(const Message& instance, string filename, ofstream::openmode mode = ofstream::out)
//	{
//		ofstream f(filename.c_str(), mode);
//		f << instance;
//		f.close();
//	}
//
//	static void Write(const Network& instance, string filename, ofstream::openmode mode = ofstream::out)
//	{
//		ofstream f(filename.c_str(), mode);
//		f << instance;
//		f.close();
//	}

	template<class T>
	static void Write(const T& instance, string filename, ofstream::openmode mode = ofstream::out)
	{
		ofstream f(filename.c_str(), mode);
		f << instance;
		f.close();
	}
};

#endif /* LOGGER_H_ */
