/*
 * NetworkStatistic.cc
 *
 *  Created on: May 31, 2013
 *      Author: thanh
 */
#include "NetworkStatistic.h"

NetworkStatistic::NetworkStatistic()
{

}

NetworkStatistic::~NetworkStatistic()
{

}

void NetworkStatistic::Reset()
{
	infections = 0;
	sanes = 0;
	inactives = 0;
	detectors = 0;
	lca = 0;
}

ofstream& operator<<(ofstream& ofs, const NetworkStatistic& statistic)
{
	ofs << statistic.infections << "\t" << statistic.inactives << "\t"
		<< statistic.detectors << "\t" << statistic.sanes << "\t" << statistic.lca << "\n";
	return ofs;
}
