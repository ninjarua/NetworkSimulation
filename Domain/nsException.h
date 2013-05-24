/*
 * nsException.h
 *
 *  Created on: May 24, 2013
 *      Author: thanh
 */

#ifndef NSEXCEPTION_H_
#define NSEXCEPTION_H_

#include "stdafx.h"
using namespace std;
#include <exception>
#include <string>

namespace domain{

struct nsException : public exception{
	string _message;
	nsException(string message) : _message(message) {}
	virtual ~nsException() throw() {}
	const char* what() const throw() { return _message.c_str(); }
};

}
#endif /* NSEXCEPTION_H_ */
