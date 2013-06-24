/*
 * NetworkStatistic.cc
 *
 *  Created on: May 31, 2013
 *      Author: thanh
 */
#include "NetworkStatistic.h"
#include "Constants.h"

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
	diameter = 0;
	degree = 0;
}

ofstream& operator<<(ofstream& ofs, const NetworkStatistic& statistic)
{
	ofs << statistic.degree << Constants::tab << statistic.diameter << Constants::tab
		<< statistic.infections << Constants::tab << statistic.inactives << Constants::tab
		<< statistic.detectors << Constants::tab << statistic.sanes << Constants::tab
		<< statistic.lca << Constants::endline;
	return ofs;
}
