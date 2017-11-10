#include "formula.h"
#include <iostream>

int main() {
	try {
		Formula F("a+b*c/(d+e)^2");
		F.print();
		std::cout << " = " << std::endl;
		double res = F.calc();

		F.print();
		std::cout << " = " << res << std::endl;
	}
	catch (const Error &e) {
		std::cout << std::endl << e.get() << std::endl;
	}

	system("pause");
	return 0;
}