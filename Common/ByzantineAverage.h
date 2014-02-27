/*
 * ByzantineSummary.h
 *
 *  Created on: Feb 27, 2014
 *      Author: thanhnd
 */

#ifndef BYZANTINEAVERAGE_H_
#define BYZANTINEAVERAGE_H_
#include "stdafx.h"
#include <fstream>

class ByzantineReport;

class ByzantineAverage {
public:
	ByzantineReport* _report;
	double averageOfByzantines;
	double averageOfSacrifices;
	double averageOfDetectors;
	double averageOfNormals;
	double averageOfLargestConnectedAreas;
	double averageOfDegree;
	double averageOfDiameter;

	double ciOfByzantines;
	double ciOfSacrifices;
	double ciOfDetectors;
	double ciOfNormals;
	double ciOfLargestConnectedAreas;
	double ciOfDegrees;
	double ciOfDiameters;

	ByzantineAverage();
	ByzantineAverage(ByzantineReport* report);
	virtual ~ByzantineAverage();
	friend ofstream& operator<<(ofstream& ofs, const ByzantineAverage& report);
};

#endif /* BYZANTINESUMMARY_H_ */
