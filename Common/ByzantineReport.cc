/*
 * ByzantineReport.cc
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#include "ByzantineReport.h"

ByzantineReport::ByzantineReport() {
	numberOfByzantines = vector<long>();
	numberOfDetectors = vector<long>();
	numberOfNormals = vector<long>();
	numberOfSacrifices = vector<long>();
	largestConnectedAreas = vector<long>();
	degrees = vector<long>();
	diameters = vector<long>();
}

ByzantineReport::~ByzantineReport() {
	// TODO Auto-generated destructor stub
}

//ByzantineReport* ByzantineReport::_report = NULL;
//ByzantineReport* ByzantineReport::Default()
//{
//	if (_report == NULL)
//		_report = new ByzantineReport();
//	return _report;
//}

void ByzantineReport::Clear()
{
	numberOfByzantines.clear();
	numberOfDetectors.clear();
	numberOfNormals.clear();
	numberOfSacrifices.clear();
	largestConnectedAreas.clear();
	degrees.clear();
	diameters.clear();
}

void ByzantineReport::addByzantineValue(long value)
{
	numberOfByzantines.push_back(value);
}

void ByzantineReport::addDetectorValue(long value)
{
	numberOfDetectors.push_back(value);
}

void ByzantineReport::addNormalValue(long value)
{
	numberOfNormals.push_back(value);
}

void ByzantineReport::addSacrificeValue(long value)
{
	numberOfSacrifices.push_back(value);
}

void ByzantineReport::addLargestConnectedAreaValue(long value)
{
	largestConnectedAreas.push_back(value);
}

void ByzantineReport::addDegrees(int value)
{
	degrees.push_back(value);
}

void ByzantineReport::addDiameters(int value)
{
	diameters.push_back(value);
}

ByzantineReport* ByzantineReport::summarize(double significance)
{
	StatisticSummary summary = StatisticSummary();
	summary.summarize(numberOfByzantines);
	averageOfByzantines = summary.mean;
	ciOfByzantines = summary.getConfidenceInterval(significance);
	summary.summarize(numberOfDetectors);
	averageOfDetectors = summary.mean;
	ciOfDetectors = summary.getConfidenceInterval(significance);
	summary.summarize(numberOfSacrifices);
	averageOfSacrifices = summary.mean;
	ciOfSacrifices = summary.getConfidenceInterval(significance);
	summary.summarize(numberOfNormals);
	averageOfNormals = summary.mean;
	ciOfNormals = summary.getConfidenceInterval(significance);
	summary.summarize(largestConnectedAreas);
	averageOfLargestConnectedAreas = summary.mean;
	ciOfLargestConnectedAreas = summary.getConfidenceInterval(significance);
	summary.summarize(degrees);
	averageOfDegree = summary.mean;
	ciOfDegrees = summary.getConfidenceInterval(significance);
	summary.summarize(diameters);
	averageOfDiameter = summary.mean;
	ciOfDiameters = summary.getConfidenceInterval(significance);
	size = summary.length;
	return this;
}

ofstream& operator<<(ofstream& ofs, const ByzantineReport& report)
{
	ofs << report.nothingProb << "\t" << report.byzantineProb << "\t"
			<< report.averageOfByzantines << "\t"
			<< report.ciOfByzantines << "\t"
			<< report.averageOfSacrifices << "\t"
			<< report.ciOfSacrifices << "\t"
			<< report.averageOfDetectors << "\t"
			<< report.ciOfDetectors << "\t"
			<< report.averageOfNormals << "\t"
			<< report.ciOfNormals << "\t"
			<< report.averageOfLargestConnectedAreas << "\t"
			<< report.ciOfLargestConnectedAreas << "\t" << report.size << "\n";
	return ofs;
}
