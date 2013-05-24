/*
 * Topology.h
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */

#ifndef TOPOLOGY_H_
#define TOPOLOGY_H_

namespace domain {
class Topology{
public:
	double XTerr;
	double YTerr;
	double Area(){ return XTerr * YTerr; }
	double Distance;
	double D0;
	int NumNodes;
};
}
#endif /* TOPOLOGY_H_ */
