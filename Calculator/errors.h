#ifndef _ERRORS_2017_
#define _ERRORS_2017_

#include <string>

class Error {
public:
	virtual std::string get() const { return std::string("Error"); }
	virtual ~Error() {}
};

class DivideByZero : public Error {
public:
	std::string get() const { return std::string("Divide by zero"); }
};

class UnknownFunctionError : public Error {
	std::string str;
public:
	UnknownFunctionError(char s) { str.push_back(s); }
	UnknownFunctionError(const char* s) : str(s) {}
	std::string get() const { 
		return std::string("Unknown function name")  + str; 
	}
};

class PostfixError : public Error {
	std::string str;
	int index;
public:
	PostfixError(const char *s, int i) : str(s), index(i) {}
	std::string get() const {
		return std::string("Error in postfix string: " + str + std::string(" at position ") + std::to_string(index+1));
	}
};

class FunctionBracketsError : public Error {
	std::string str;
	int index;
public:
	FunctionBracketsError(const char *s, int i) : str(s), index(i) {}
	std::string get() const {
		return std::string("Error with function in string: " + str + std::string(" at position ") + std::to_string(index + 1));
	}
};

class BracketsError : public Error {
	std::string str;
	int index;
public:
	BracketsError(const char *s, int i) : str(s), index(i) {}
	std::string get() const {
		return std::string("Error with brackets in string: " + str + std::string(" at position ") + std::to_string(index + 1));
	}
};

#endif // !_ERRORS_2017_
