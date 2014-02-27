/*
 * ByzantineReport.cc
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#include "ByzantineReport.h"

ByzantineReport::ByzantineReport() {
	average = ByzantineAverage(this);
	numberOfByzantines = vector<long>();
	numberOfDetectors = vector<long>();
	numberOfNormals = vector<long>();
	numberOfSacrifices = vector<long>();
	largestConnectedAreas = vector<long>();
	degrees = vector<long>();
	diameters = vector<long>();
	size = 0;
	byzantineProb = nothingProb = 0;
}

ByzantineReport::~ByzantineReport() {
}

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
	average.averageOfByzantines = summary.mean;
	average.ciOfByzantines = summary.getConfidenceInterval(significance);
	summary.summarize(numberOfDetectors);
	average.averageOfDetectors = summary.mean;
	average.ciOfDetectors = summary.getConfidenceInterval(significance);
	summary.summarize(numberOfSacrifices);
	average.averageOfSacrifices = summary.mean;
	average.ciOfSacrifices = summary.getConfidenceInterval(significance);
	summary.summarize(numberOfNormals);
	average.averageOfNormals = summary.mean;
	average.ciOfNormals = summary.getConfidenceInterval(significance);
	summary.summarize(largestConnectedAreas);
	average.averageOfLargestConnectedAreas = summary.mean;
	average.ciOfLargestConnectedAreas = summary.getConfidenceInterval(significance);
	summary.summarize(degrees);
	average.averageOfDegree = summary.mean;
	average.ciOfDegrees = summary.getConfidenceInterval(significance);
	summary.summarize(diameters);
	average.averageOfDiameter = summary.mean;
	average.ciOfDiameters = summary.getConfidenceInterval(significance);
	size = summary.length;
	return this;
}

ofstream& operator<<(ofstream& ofs, const ByzantineReport& report)
{
	ofs << report.nothingProb << "\t" << report.byzantineProb << "\n";
	for(int i=0; i < report.numberOfByzantines.size(); i++)
	{
		ofs << report.numberOfByzantines[i] << "\t"
			<< report.numberOfSacrifices[i] << "\t"
			<< report.numberOfDetectors[i] << "\t"
			<< report.numberOfNormals[i] << "\t"
			<< report.largestConnectedAreas[i] << "\t"
			<< "\n";
	}
	return ofs;
}
