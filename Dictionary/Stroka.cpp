#include "stroka.h"
#include "Errors.h"
// -----------------------------------------------------------
stroka::stroka(const char *str) {
	Len = strlen(str);
	data = new char[Len + 1];
	if (!data) throw ErrorBadAlloc();
	memcpy(data, str, Len + 1);
}
// -----------------------------------------------------------
stroka::stroka(int N) {
	Len = N;
	data = new char[Len + 1];
	if (!data) throw ErrorBadAlloc();
	data[0] = '\0';
}
// -----------------------------------------------------------
stroka::stroka(const stroka& X) {
	Len = X.Len;
	data = new char[Len + 1];
	if (!data) throw ErrorBadAlloc();
	memcpy(data, X.data, Len + 1);
}
// -----------------------------------------------------------
stroka::~stroka() {
	if (data) delete[] data;
	data = nullptr;
	Len = 0;
}
// -----------------------------------------------------------
stroka& stroka::operator= (const stroka& X) {
	if (this != &X) {
		if (data) delete[] data;
		Len = X.Len;
		data = new char[Len + 1];
		if (!data) throw ErrorBadAlloc();
		memcpy(data, X.data, Len + 1);
	}
	return *this;
}
// -----------------------------------------------------------
stroka stroka::operator+ (const stroka& X) const {
	stroka res(Len + X.Len);
	memcpy(res.data, data, Len);
	memcpy(res.data + Len, X.data, X.Len + 1);
	return res;
}
// -----------------------------------------------------------
char stroka::operator[](std::size_t i) const {
	if (i > Len) throw ErrorStringLimits();
	return data[i];
}
// -----------------------------------------------------------
std::ostream& operator<< (std::ostream& out, const stroka& X) {
	out << X.str();
	return out;
}