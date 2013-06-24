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
	vector<long> numberOfByzantines;
	vector<long> numberOfDetectors;
	vector<long> numberOfNormals;
	vector<long> numberOfSacrifices;
	vector<long> largestConnectedAreas;
	vector<long>	degrees;
	vector<long> diameters;
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
	double averageOfDegree;
	double averageOfDiameter;

	double ciOfByzantines;
	double ciOfSacrifices;
	double ciOfDetectors;
	double ciOfNormals;
	double ciOfLargestConnectedAreas;
	double ciOfDegrees;
	double ciOfDiameters;

	void Clear();
	void AddByzantineValue(long value);
	void AddDetectorValue(long value);
	void AddNormalValue(long value);
	void AddSacrificeValue(long value);
	void AddLargestConnectedAreaValue(long value);
	void AddDegrees(int value);
	void AddDiameters(int value);
	ByzantineReport* Summarize(double significance);
	friend ofstream& operator<<(ofstream& ofs, const ByzantineReport& report);
};

#endif /* BYZANTINEREPORT_H_ */
