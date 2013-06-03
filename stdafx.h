/*
 * stdafx.h
 *
 *  Created on: May 21, 2013
 *      Author: thanh
 */

#ifndef STDAFX_H_
#define STDAFX_H_

#ifndef BOOST_THREAD_USE_LIB
#define BOOST_THREAD_USE_LIB
#endif

#ifdef WIN32
#define OS_SEP '\\'
#else
#define OS_SEP '/'
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#include "Tools.h"


#endif /* STDAFX_H_ */
