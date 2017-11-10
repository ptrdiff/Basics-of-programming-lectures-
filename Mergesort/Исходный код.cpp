#include <iostream>
#include <fstream>
//-------------------------------------------------------------------------
bool generate_file(int N, const char *fname) {
	std::ofstream outFile(fname);
	if (!outFile) {
		return false;
	}
	while (N-- > 0) {
		outFile << ' ' << rand() % 1000;
	}
	outFile.close();
	return true;
}
//-------------------------------------------------------------------------
bool isSorted_file(const char *fname) {
	std::ifstream inFile(fname);
	int last, current;
	if (!inFile) throw "Can not open file";
	inFile >> last;
	bool answer = true;
	while (inFile.peek() != EOF) {
		inFile >> current;
		if (current < last) {
			answer = false;
			break;
		}
		last = current;
	}
	inFile.close();
	return answer;
}
//-------------------------------------------------------------------------
bool _Split_file(const char *fname, const char *tmp1, const char *tmp2, unsigned long long &c) {
	std::ifstream inFile(fname);
	if (!inFile) throw "Can not read file";
	std::ofstream outFile[2];
	outFile[0].open(tmp1);
	outFile[1].open(tmp2);
	if (!outFile[0] || !outFile[1]) {
		inFile.close();
		throw "Can not write to file";
	}
	bool result = false;
	int current, last;
	unsigned char num = 0;//номер файла в который пишем
	inFile >> last;
	outFile[num] << last;
	while (inFile.peek() != EOF) {
		inFile >> current;
		if (current < last) {
			num = !num;
			result = true;
		}
		++c;
		outFile[num] << ' ' << current;
		last = current;
	}
	outFile[0].close();
	outFile[1].close();
	inFile.close();
	return result;
}
//-------------------------------------------------------------------------
bool _Merge_file(const char *fname, const char *tmp1, const char *tmp2, unsigned long long &c) {
	std::ofstream outFile(fname);
	if (!outFile) throw "Can not write to file";
	std::ifstream inFile[2];
	inFile[0].open(tmp1);
	inFile[1].open(tmp2);
	if (!inFile[0] || !inFile[1]) {
		throw "Can't read temp files";
	}
	int last, current[2];
	unsigned char num;
	inFile[0] >> current[0];
	inFile[1] >> current[1];
	num = (current[1] < current[0]) ? 1 : 0;
	++c;
	outFile << current[num];
	last = current[num];
	while (inFile[num].peek() != EOF) {
		inFile[num] >> current[num];
		bool s1 = current[num] < last;
		++c;
		bool s2 = current[!num] < last;
		++c;
		if (s1 == s2) {
			num = (current[1] < current[0]) ? 1 : 0;
			++c;
		}
		else {
			if (s1) {
				num = !num;
			}
		}
		outFile << ' ' << current[num];
		last = current[num];
	}
	outFile << ' ' << current[!num];
	num = !num;
	while (inFile[num].peek() != EOF) {
		inFile[num] >> current[num];
		outFile << ' ' << current[num];
	}
	outFile.close();
	inFile[0].close();
	inFile[1].close();
}
//-------------------------------------------------------------------------
int MergeFileSorting(const char *fname, unsigned long long &c) {
	int counter = 0;
	bool key;
	char tmp1[] = "temporarufile1.txt", tmp2[] = "temporarufile2.txt";
	do {
		key = _Split_file(fname, tmp1, tmp2, c);
		if (key) {
			_Merge_file(fname, tmp1, tmp2, c);
		}
		++counter;
	} while (key);
	return counter;
	{

	}
}
//-------------------------------------------------------------------------
int main() {
	int N = 1000;
	char fname[] = "data.txt";
	if (!generate_file(N, fname)) {
		std::cout << "Can not create file for test" << std::endl;
		return 1;
	}
	try {
		unsigned long long c = 0;
		int N = MergeFileSorting(fname, c);
		if (!isSorted_file(fname)) throw "Sorted - ERROR";
		std::cout << "Total " << N << " splits";
		std::cout << c << " comparisons" << std::endl;
	}
	catch(const char *error) {
		std::cout << "Error: " << error << std::endl;
	}
	return 0;
}