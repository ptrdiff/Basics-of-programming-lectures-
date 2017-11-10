#include <iostream>
#include <string>
#include <map>

template<typename T>
class HashTable {
private:
	std::map<T, std::string> table;
public:
	HashTable():table(std::map<T,std::string>()){}
	~HashTable() {}
	void insert(T key, std::string value) {
		table.insert(std::make_pair(key, value));
	}
	std::string find(T k) {
		auto it = table.find(k);
		if (it != table.end()) {
			return it->second;
		}
		else {
			return "Not found!";
		}
	}
	void del(T key){
		table.erase(key);
	}
	void show() {
		for (auto i = table.begin(); i != table.end(); ++i) {
			std::cout << i->first << " - " << i->second << std::endl;
		}
	}
};

int main() {
	HashTable<int> Hash_Table;
	int count;
	std::cout << "Write count of elements: ";
	std::cin >> count;
	std::cout << std::endl;
	for (int i = 0; i < count; ++i) {
		int K;
		std::string W;
		std::cout << "Write key of element: ";
		std::cin >> K;
		std::cout << "Write value of element: ";
		std::cin >> W;
		Hash_Table.insert(K, W);
	}
	std::cout << std::endl;
	Hash_Table.show();
	std::cout << "Want find something?(Write key): ";
	std::cin >> count;
	auto s = Hash_Table.find(count);
	std::cout << "Find element: " <<s << std::endl;
	std::cout << "Want delete something?(Write key): ";
	std::cin >> count;
	Hash_Table.del(count);
	Hash_Table.show();
	system("pause");
	return 0;
}