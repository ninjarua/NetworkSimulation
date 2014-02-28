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
		<< report.averageOfByzantines << "\t"
		<< report.ciOfByzantines << "\t"
		<< report.averageOfSacrifices << "\t"
		<< report.ciOfSacrifices << "\t"
		<< report.averageOfDetectors << "\t"
		<< report.ciOfDetectors << "\t"
		<< report.averageOfNormals << "\t"
		<< report.ciOfNormals << "\t"
		<< report.averageOfLargestConnectedAreas << "\t"
		<< report.ciOfLargestConnectedAreas << "\t" << report._report->size << "\n";
	return ofs;
}
