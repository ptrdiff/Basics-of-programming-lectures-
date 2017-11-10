#ifndef _ERRORS_2017_
#define _ERRORS_2017_
#include "stroka.h"

class stroka;
class Error {
public:
	virtual stroka get() const { return stroka("Error"); }
	virtual ~Error(){}
};
// -----------------------------------------------------------
class ErrorStringLimits : public Error{
public:
	stroka get() const {
		return stroka("Out of string limits.");
	}
};
// -----------------------------------------------------------
class ErrorBadAlloc : public Error {
public:
	stroka get() const {
		return stroka("Not enough memory");
	}
};
// -----------------------------------------------------------
class ErrorMessage : public Error {
	stroka message;
public:
	ErrorMessage(const stroka &str) : message(str) {}
	stroka get() const { return message; }
};
// -----------------------------------------------------------
class ErrorOutOfBounds : public Error {
public:
	stroka get() const { return stroka("Out of bounds"); }
};
#endif