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
	double xTerr;
	double yTerr;
	double Area(){ return xTerr * yTerr; }
	double range;
	double d0;
	int numNodes;
};
}
#endif /* TOPOLOGY_H_ */
