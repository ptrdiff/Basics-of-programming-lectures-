#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void hexMultiplicationTable(streambuf *buffer, int num) {
	ostream hexout(buffer);
	hexout << hex << showbase;
	hexout.setf(ios::left);
	for (int i = 1; i <= num; ++i) {
		for (int j = 1; j <= num; ++j) {
			hexout << setw(4) << i*j << ' ';
		}
		hexout << endl;
	}
}

int main() {
	int num = 5;
	cout << "Print " << num << " lines hexademal" << endl;
	hexMultiplicationTable(cout.rdbuf(), num);

	ofstream outFile("hexresult.txt");
	if (outFile) hexMultiplicationTable(outFile.rdbuf(), num);
	outFile.close();

	ostringstream os;
	hexMultiplicationTable(os.rdbuf(), num);
	cout << "Result " << endl << os.str() << endl;

	return 0;
} 