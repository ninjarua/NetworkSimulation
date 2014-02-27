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
#include "ByzantineAverage.h"

class ByzantineReport {
public:
	ByzantineReport();
	virtual ~ByzantineReport();
private:
	//static ByzantineReport* _report;
	vector<long> numberOfByzantines;
	vector<long> numberOfDetectors;
	vector<long> numberOfNormals;
	vector<long> numberOfSacrifices;
	vector<long> largestConnectedAreas;
	vector<long> degrees;
	vector<long> diameters;
public:
	//static ByzantineReport* Default();
	long size;
	double nothingProb;
	double byzantineProb;
	ByzantineAverage average;

	void Clear();
	void addByzantineValue(long value);
	void addDetectorValue(long value);
	void addNormalValue(long value);
	void addSacrificeValue(long value);
	void addLargestConnectedAreaValue(long value);
	void addDegrees(int value);
	void addDiameters(int value);
	ByzantineReport* summarize(double significance);
	friend ofstream& operator<<(ofstream& ofs, const ByzantineReport& report);
};

#endif /* BYZANTINEREPORT_H_ */
