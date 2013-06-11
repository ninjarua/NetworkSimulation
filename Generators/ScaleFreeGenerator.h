/*
 * ScaleFreeGenerator.h
 *
 *  Created on: Jun 11, 2013
 *      Author: thanhnd
 */

#ifndef SCALEFREEGENERATOR_H_
#define SCALEFREEGENERATOR_H_

#include "NetworkGenerator.h"

namespace generators {

class ScaleFreeGenerator : public NetworkGenerator {
public:
	ScaleFreeGenerator();
	ScaleFreeGenerator(int m0, int m, int N);
	virtual ~ScaleFreeGenerator();
};

} /* namespace generators */
#endif /* SCALEFREEGENERATOR_H_ */
