#include <iostream>

class List{
private:
	class Node {
	public:
		int value;
		Node* next;
		Node(int v, Node* n) : value(v), next(n) {}
		~Node() { delete next; }
	};
	class Iterator {
	private:
		Node* pointer;
	public:
		Iterator() : pointer(nullptr) {}
		Iterator(Node* p) :pointer(p) {}
		Iterator& operator++() { if (pointer != nullptr) { pointer = pointer->next; return *this; } return Iterator(nullptr); }
		bool operator==(const Iterator& r) const { return pointer == r.pointer; }
		bool operator!=(const Iterator& r) const { return pointer != r.pointer; }
		int& operator*() { return pointer->value; }
	};
	Node *first, *last;
	Iterator begin() { return(Iterator(first)); };
	Iterator end() { return(Iterator(nullptr)); };
public:
	List() : first(nullptr), last(nullptr) {}
	void push_back(int new_n) {
		Node new_node(new_n, nullptr);
		if (begin() == nullptr) {
			first = &new_node;
			last = &new_node;
		}
		else {
			last->next = &new_node;
			last = last->next;
		}
	}
	void show() {
		for (Iterator i = begin(); i != end(); ++i) {
			std::cout << *i << std::endl;
		}
	}
};

int main() {
	List my_list;
	my_list.push_back(10);
	my_list.show();
	system("pause");
	return 0;
}