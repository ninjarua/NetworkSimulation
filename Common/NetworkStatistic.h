/*
 * NetworkStatistic.h
 *
 *  Created on: May 31, 2013
 *      Author: thanh
 */

#ifndef NETWORKSTATISTIC_H_
#define NETWORKSTATISTIC_H_

#include "stdafx.h"
#include <fstream>

class NetworkStatistic
{
public:
	long infections;
	long sanes;
	long inactives;
	long detectors;
	long lca;
	int diameter;
	int degree;
public:
	NetworkStatistic();
	virtual ~NetworkStatistic();
	void Reset();
	friend ofstream& operator<<(ofstream& ofs, const NetworkStatistic& statistic);
};

#endif /* NETWORKSTATISTIC_H_ */
