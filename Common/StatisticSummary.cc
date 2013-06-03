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
//
//StatisticSummary* StatisticSummary::_instance = NULL;
//StatisticSummary* StatisticSummary::GetInstance()
//{
//	if (_instance == NULL)
//		_instance = new StatisticSummary();
//	return _instance;
//}

void StatisticSummary::Reset()
{
    sum = variance = mean = standardDeviation = 0;
    x = 0;
    length = 0;
}

double StatisticSummary::GetConfidenceInterval(double significance)
{
	normal_distribution<double> dist = normal_distribution<double>(0, 1);
	double delta = quantile(complement(dist, significance/2));
	return delta * standardDeviation / sqrt(length);
}

double Sum(const list<long>& values)
{
	double sum = 0;
	list<long>::const_iterator it = values.begin();
	for (; it != values.end(); it++)
	{
		sum += (double)(*it);
	}
	return sum;
}

StatisticSummary* StatisticSummary::Summarize(const list<long>& elements)
{
	Reset();
	length = elements.size();
	//list<double> doubleValues = elements.ConvertAll<double>(c => Convert.ToDouble(c));
	sum = Sum(elements);
	// mean value
	mean = sum / length;

	// variance
	variance = 0;
	list<long>::const_iterator it = elements.begin();
	for (; it != elements.end(); it++)
	{
		variance += (*it - mean) * (*it - mean);
	}
	variance = variance / (length - 1);
//	median = Statistics.Median(doubleValues);
	standardDeviation = sqrt(variance);
	return this;
}