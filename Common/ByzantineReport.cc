/*
 * ByzantineReport.cc
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#include "ByzantineReport.h"

ByzantineReport::ByzantineReport() {
	numberOfByzantines = new list<long>();
	numberOfDetectors = new list<long>();
	numberOfNormals = new list<long>();
	numberOfSacrifices = new list<long>();
	largestConnectedAreas = new list<long>();
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
	numberOfByzantines->erase(numberOfByzantines->begin(), numberOfByzantines->end());
	numberOfDetectors->erase(numberOfDetectors->begin(), numberOfDetectors->end());
	numberOfNormals->erase(numberOfNormals->begin(), numberOfNormals->end());
	numberOfSacrifices->erase(numberOfSacrifices->begin(), numberOfSacrifices->end());
	largestConnectedAreas->erase(largestConnectedAreas->begin(), largestConnectedAreas->end());
}

void ByzantineReport::AddByzantineValue(long value)
{
	numberOfByzantines->push_back(value);
}

void ByzantineReport::AddDetectorValue(long value)
{
	numberOfDetectors->push_back(value);
}

void ByzantineReport::AddNormalValue(long value)
{
	numberOfNormals->push_back(value);
}

void ByzantineReport::AddSacrificeValue(long value)
{
	numberOfSacrifices->push_back(value);
}

void ByzantineReport::AddLargestConnectedAreaValue(long value)
{
	largestConnectedAreas->push_back(value);
}

ByzantineReport* ByzantineReport::Summarize(double significance)
{
	StatisticSummary::GetInstance()->Summarize(numberOfByzantines);
	averageOfByzantines = StatisticSummary::GetInstance()->mean;
	ciOfByzantines = StatisticSummary::GetInstance()->GetConfidenceInterval(significance);
	StatisticSummary::GetInstance()->Summarize(numberOfDetectors);
	averageOfDetectors = StatisticSummary::GetInstance()->mean;
	ciOfDetectors = StatisticSummary::GetInstance()->GetConfidenceInterval(significance);
	StatisticSummary::GetInstance()->Summarize(numberOfSacrifices);
	averageOfSacrifices = StatisticSummary::GetInstance()->mean;
	ciOfSacrifices = StatisticSummary::GetInstance()->GetConfidenceInterval(significance);
	StatisticSummary::GetInstance()->Summarize(numberOfNormals);
	averageOfNormals = StatisticSummary::GetInstance()->mean;
	ciOfNormals = StatisticSummary::GetInstance()->GetConfidenceInterval(significance);
	StatisticSummary::GetInstance()->Summarize(largestConnectedAreas);
	averageOfLargestConnectedAreas = StatisticSummary::GetInstance()->mean;
	ciOfLargestConnectedAreas = StatisticSummary::GetInstance()->GetConfidenceInterval(significance);
	size = StatisticSummary::GetInstance()->length;
	return this;
}
