#ifndef _STROKA_2017_
#define _STROKA_2017_
#include <cstring>

class stroka {
	std::size_t Len;
	char *data;
public:
	stroka(const char *str = "");
	stroka(int N);
	stroka(const stroka&);
	~stroka();
	stroka& operator= (const stroka&);
	std::size_t size() const {
		return Len;
	}
	std::size_t length() const {
		return strlen(data);
	}
	const char* str() const {
		return data;
	}

	char operator[] (std::size_t i) const;

	bool operator== (const stroka& X) const {
			return strcmp(data, X.data) == 0;
		}

	bool operator!= (const stroka& X) const {
		return strcmp(data, X.data) != 0;
	}

	bool operator< (const stroka& X) const {
		return strcmp(data, X.data) < 0;
	}
	stroka operator+ (const stroka&) const;
};

#include <iostream>
	std::ostream& operator<< (std::ostream&, const stroka&);

#endif
