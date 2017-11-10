#include <iostream>
#include <sstream>

unsigned int max(const unsigned int x, const unsigned int y) {
	unsigned int z;
	x > y ? z = x : z = y;
	return z;
}

class polynom {
	unsigned int deg;
	double* coef;
public:
	polynom() : deg(0), coef(nullptr) {};
	polynom(unsigned int n) : deg(n) {
		if (deg == UINT32_MAX) {
			throw "Very big deg";
		}
		coef = new double[deg + 1];
		if (!coef) {
			throw "Not enough memory";
		}
		else {
			for (int x = 0; x < deg + 1; ++x) {
				coef[x] = 0;
			}
		}
	}

	polynom(unsigned int n, double* M) :deg(n) {
		if (deg == UINT32_MAX) {
			throw "Very big deg";
		}
		coef = new double[deg + 1];
		if (!coef) {
			throw "Not enough memory";
		}
		else {
			for (int x = 0; x < deg + 1; ++x) {
				coef[x] = M[x];
			}
		}
	}

	~polynom() {
		if (coef) {
			delete[] coef;
		}
		coef = nullptr;
		deg = 0;
	}

	polynom(const polynom &C) {
		deg = C.deg;
		coef = new double[deg + 1];
		if (!coef) throw "Didn't copied";
		for (int x = 0; x < deg + 1; ++x) {
			coef[x] = C.coef[x];
		}
	}

	polynom& operator=(const polynom &C) {
		if (this != &C) {  // this - свой адрес
			if (coef) {
				delete[] coef;
			}

			deg = C.deg;
			coef = new double[deg + 1];
			if (!coef) throw "didn't copied";
			for (int x = 0; x < deg + 1; ++x) {
				coef[x] = C.coef[x];
			}

		}
		return *this;
	}

	unsigned int degree() const {  // расширение функции для ВСЕХ объектов
		return deg;
	}

	double &operator[](unsigned int i) {
		if (i > deg + 1) {
			throw "Out of range";
		}
		return coef[i];
	}

	double operator[] (unsigned int i) const {
		if (i > deg + 1) {
			throw "Out of range";
		}
		return coef[i];
	}

	polynom operator + (const polynom& Y) const {
		polynom Z;
		Z.deg = max(deg, Y.deg);
		// ...
		return Z;
	}

	polynom& operator += (const polynom& Y) const {
		// прибавляем к coef[i] Y.coef[i]
		// ...
		return *this;
	}

	double operator () (double x) const {
		double res = 0;
		// по схеме Горнера вычисляем polynom(x)
		return res;
	}
};

ostream& operator << (ostream &out, const polynom &X) {
	for (int i = 0; i < X.degree(); ++i) {
		std::cout << "..." << X[i] << "...";
	}
	return out;
}