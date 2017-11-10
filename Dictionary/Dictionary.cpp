#include <iostream>
#include <fstream>
#include <time.h>
#include "stroka.h"
#include "Errors.h"
#include "dictpara.h"
#include "array.h"
#include "list.h"
#include "bintree.h"
#include "aatree.h"
// -------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const DictPara &X) {
	out << X.get_word() << ": " << X.get_translate() << std::endl;
	return out;
}
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
std::ifstream& operator>>(std::ifstream &in, DictPara &X) {
	char tmp[1024];
	in.getline(tmp, 1024);
	char *p = tmp;
	while ((*p != '\t') && (*p)) {
		++p;
	}
	if (*p) {
		*p = 0;
		++p;
	}
	X = DictPara(stroka(tmp), stroka(p));
	return in;
}
// -------------------------------------------------------------------------------------
int main() {
	typedef AATree<DictPara> Cont;
	try {
		char fname[] = "en_ru.txt";
		std::ifstream inFile(fname);
		if (!inFile) throw ErrorMessage(stroka("Can't open file ") + stroka(fname));
		DictPara X;
		Cont Dictionary;
		int i = 0;
		clock_t tic = clock();
		while (inFile.peek() != EOF) {
			inFile >> X;
			Dictionary.push_back(X);
			++i;
		}
		tic = clock() - tic;
		inFile.close();

		std::cout << "Reading from file: " << tic << " tics" << std::endl;
		std::cout << "Total: " << Dictionary.size() << std::endl;
		std::cout << "Height: " << Dictionary.height() << std::endl;

		i = 0;
		for (Cont::iterator pos = Dictionary.begin(); pos != Dictionary.end() && i < 10; ++pos, ++i) {
			std::cout << *pos << std::endl;
		}

		char what[128];
		Cont::iterator pos;
		do {
			std::cout << "> ";
			std::cin.getline(what, 128);
			if (strlen(what) < 1) {
				break;
			}
			tic = clock();
			for (int i = 0; i < 1000; ++i) {
				pos = Dictionary.find(DictPara(what, ""));
			}
			tic = clock() - tic;
			std::cout << "Finded at: " << tic << " tics" << std::endl;
			if (pos != Dictionary.end()) {
				std::cout << *pos << std::endl;
			}
			else {
				std::cout << "There are no word \"" << what << "\" in dictionary" << std::endl;
			}
		} while (1);

	} 
	catch (const Error &e) {
		std::cout << e.get() << std::endl;
	}
	catch (const char* e) {
		std::cout << e << std::endl;
	}

	system("pause");
	return 0;
}