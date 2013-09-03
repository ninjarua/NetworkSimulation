/*
 * StatisticSummary.cc
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#include "StatisticSummary.h"

using namespace boost::math;
StatisticSummary::StatisticSummary() {

}

StatisticSummary::~StatisticSummary() {

}

void StatisticSummary::reset()
{
    summation = variance = mean = standardDeviation = 0;
    x = 0;
    length = 0;
}

double StatisticSummary::getConfidenceInterval(double significance)
{
	normal_distribution<double> dist = normal_distribution<double>(0, 1);
	double delta = quantile(complement(dist, significance/2));
	return delta * standardDeviation / sqrt(length);
}

double sum(const vector<long>& values)
{
	double summation = 0;
	vector<long>::const_iterator it = values.begin();
	for (; it != values.end(); it++)
	{
		summation += (double)(*it);
	}
	return summation;
}

StatisticSummary* StatisticSummary::summarize(const vector<long>& elements)
{
	reset();
	length = elements.size();
	//list<double> doubleValues = elements.ConvertAll<double>(c => Convert.ToDouble(c));
	summation = sum(elements);
	// mean value
	mean = summation / length;

	// variance
	variance = 0;
	vector<long>::const_iterator it = elements.begin();
	for (; it != elements.end(); it++)
	{
		variance += (*it - mean) * (*it - mean);
	}
	variance = variance / (length - 1);
//	median = Statistics.Median(doubleValues);
	standardDeviation = sqrt(variance);
	return this;
}
