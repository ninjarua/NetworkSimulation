/*
 * StatisticSummary.h
 *
 *  Created on: May 30, 2013
 *      Author: thanh
 */

#ifndef STATISTICSUMMARY_H_
#define STATISTICSUMMARY_H_

#include "stdafx.h"
#include <list>
#include <boost/math/distributions/normal.hpp>

class StatisticSummary {
public:
	StatisticSummary();
	virtual ~StatisticSummary();

	int x;
	double variance;
	double mean;
	double summation;
	long length;
	double standardDeviation;
	double median;

	void reset();
	double getConfidenceInterval(double significance);
	StatisticSummary* summarize(const vector<long>& elements);
	StatisticSummary* summarize(const vector<double>& elements);
};

#endif /* STATISTICSUMMARY_H_ */
