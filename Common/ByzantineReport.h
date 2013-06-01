/*
 * ByzantineReport.h
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#ifndef BYZANTINEREPORT_H_
#define BYZANTINEREPORT_H_

#include "stdafx.h"
#include <list>
#include <fstream>
#include "StatisticSummary.h"

class ByzantineReport {
public:
	ByzantineReport();
	virtual ~ByzantineReport();
private:
	//static ByzantineReport* _report;
public:
	//static ByzantineReport* Default();
	long size;
	double nothingProb;
	double byzantineProb;

	double averageOfByzantines;
	double averageOfSacrifices;
	double averageOfDetectors;
	double averageOfNormals;
	double averageOfLargestConnectedAreas;

	double ciOfByzantines;
	double ciOfSacrifices;
	double ciOfDetectors;
	double ciOfNormals;
	double ciOfLargestConnectedAreas;

	list<long> numberOfByzantines;
	list<long> numberOfDetectors;
	list<long> numberOfNormals;
	list<long> numberOfSacrifices;
	list<long> largestConnectedAreas;

	void Clear();
	void AddByzantineValue(long value);
	void AddDetectorValue(long value);
	void AddNormalValue(long value);
	void AddSacrificeValue(long value);
	void AddLargestConnectedAreaValue(long value);
	ByzantineReport* Summarize(double significance);
	friend ofstream& operator<<(ofstream& ofs, const ByzantineReport& report);
};

#endif /* BYZANTINEREPORT_H_ */
