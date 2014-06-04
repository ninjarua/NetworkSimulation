/*
 * ByzantineSummary.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: thanhnd
 */

#include <ByzantineReport.h>
ByzantineAverage::ByzantineAverage()
{
	_report = NULL;
	averageOfByzantines = averageOfSacrifices = averageOfDetectors
			= averageOfNormals = averageOfLargestConnectedAreas
			= averageOfDegree = averageOfDiameter = 0;
	ciOfByzantines = ciOfSacrifices = ciOfDetectors
			= ciOfNormals = ciOfLargestConnectedAreas
			= ciOfDegrees = ciOfDiameters = 0;
}

ByzantineAverage::ByzantineAverage(ByzantineReport* report) {
	_report = report;
	averageOfByzantines = averageOfSacrifices = averageOfDetectors
			= averageOfNormals = averageOfLargestConnectedAreas
			= averageOfDegree = averageOfDiameter = 0;
	ciOfByzantines = ciOfSacrifices = ciOfDetectors
			= ciOfNormals = ciOfLargestConnectedAreas
			= ciOfDegrees = ciOfDiameters = 0;
}

ByzantineAverage::~ByzantineAverage() {
}

ofstream& operator<<(ofstream& ofs, const ByzantineAverage& report)
{
	ofs << report._report->nothingProb << "\t" << report._report->byzantineProb << "\t"
		<< std::fixed << report.averageOfByzantines << "\t"
		<< std::fixed << report.ciOfByzantines << "\t"
		<< std::fixed << report.averageOfSacrifices << "\t"
		<< std::fixed << report.ciOfSacrifices << "\t"
		<< std::fixed << report.averageOfDetectors << "\t"
		<< std::fixed << report.ciOfDetectors << "\t"
		<< std::fixed << report.averageOfNormals << "\t"
		<< std::fixed << report.ciOfNormals << "\t"
		<< std::fixed << report.averageOfLargestConnectedAreas << "\t"
		<< std::fixed << report.ciOfLargestConnectedAreas << "\t" << report._report->size << "\n";
	return ofs;
}
