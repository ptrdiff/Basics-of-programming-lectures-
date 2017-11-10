#ifndef _MYFUNCTIONS_2017_
#define _MYFUNCTIONS_2017_

#include <cmath>
#include <cstring>
#include "Errors.h"

typedef double(*pfun)(double);
struct Func {
	char ShortName;
	const char *Name;
	pfun fun;

};

const Func FTable[] = {
	{'á',"arcsin",std::asin},
	{'â',"arccos",std::acos},
	{'ã',"sin",std::sin},
	{'ä',"cos",std::cos},
	{'æ',"arctg",std::atan},
	{'ç',"tg",std::tan},
	{'è',"exp",std::exp},
	{'ê',"ln",std::log},
	{'ë',"abs",std::fabs},
	{'ì',"sh",std::sinh},
	{'í',"ch",std::cosh},
};

const int sizeFTable = sizeof(FTable) / sizeof(FTable[0]);

int FunNumberByShortName(char s) {
	for (int i = 0; i < sizeFTable; ++i)
		if ( FTable[i].ShortName == s) return i;
	throw UnknownFunctionError(s);
}

int FunNumberByName(const char* s) {
	for (int i = 0; i < sizeFTable; ++i)
		if (strcmp(FTable[i].Name, s) == 0) return i;
	throw UnknownFunctionError(s);
}

pfun FunByShortName(char s) {
	for (int i = 0; i < sizeFTable; ++i)
		if (FTable[i].ShortName == s ) return FTable[i].fun;
	throw UnknownFunctionError(s);
}

pfun FunByName(const char *s) {
	for (int i = 0; i < sizeFTable; ++i)
		if (strcmp(FTable[i].Name, s) == 0) return FTable[i].fun;
	throw UnknownFunctionError(s);
}

#endif // !_MYFUNCTIONS_2017_
