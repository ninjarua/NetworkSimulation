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
//	numberOfByzantines.erase(numberOfByzantines.begin(), numberOfByzantines.end());
//	numberOfDetectors.erase(numberOfDetectors.begin(), numberOfDetectors.end());
//	numberOfNormals.erase(numberOfNormals.begin(), numberOfNormals.end());
//	numberOfSacrifices.erase(numberOfSacrifices.begin(), numberOfSacrifices.end());
//	largestConnectedAreas.erase(largestConnectedAreas.begin(), largestConnectedAreas.end());
	numberOfByzantines.clear();
	numberOfDetectors.clear();
	numberOfNormals.clear();
	numberOfSacrifices.clear();
	largestConnectedAreas.clear();
}

void ByzantineReport::AddByzantineValue(long value)
{
	numberOfByzantines.push_back(value);
}

void ByzantineReport::AddDetectorValue(long value)
{
	numberOfDetectors.push_back(value);
}

void ByzantineReport::AddNormalValue(long value)
{
	numberOfNormals.push_back(value);
}

void ByzantineReport::AddSacrificeValue(long value)
{
	numberOfSacrifices.push_back(value);
}

void ByzantineReport::AddLargestConnectedAreaValue(long value)
{
	largestConnectedAreas.push_back(value);
}

ByzantineReport* ByzantineReport::Summarize(double significance)
{
	StatisticSummary summary = StatisticSummary();
	summary.Summarize(numberOfByzantines);
	averageOfByzantines = summary.mean;
	ciOfByzantines = summary.GetConfidenceInterval(significance);
	summary.Summarize(numberOfDetectors);
	averageOfDetectors = summary.mean;
	ciOfDetectors = summary.GetConfidenceInterval(significance);
	summary.Summarize(numberOfSacrifices);
	averageOfSacrifices = summary.mean;
	ciOfSacrifices = summary.GetConfidenceInterval(significance);
	summary.Summarize(numberOfNormals);
	averageOfNormals = summary.mean;
	ciOfNormals = summary.GetConfidenceInterval(significance);
	summary.Summarize(largestConnectedAreas);
	averageOfLargestConnectedAreas = summary.mean;
	ciOfLargestConnectedAreas = summary.GetConfidenceInterval(significance);
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
