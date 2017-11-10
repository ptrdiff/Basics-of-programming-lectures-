#ifndef _DICTPARA_2017_
#define _DICTPARA_2017_
#include "stroka.h"

class DictPara {
	stroka word, translate;
public:
	DictPara() : word(""), translate("") {}
	DictPara(const stroka &w, const stroka &t) :
		word(w), translate(t) {}

	const stroka& get_word() const { return word; }
	const stroka& get_translate() const { return translate; }
	bool operator==(const DictPara &X) const { return word == X.word; }
	bool operator!=(const DictPara &X) const { return word != X.word; }
	bool operator<(const DictPara &X) const { return word < X.word; }
};

#endif