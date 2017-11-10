#ifndef _LIST_2017_
#define _LIST_2017_

template <typename T>
class List {
	struct Node {  
		Node *prev, *next;
		T data;
		Node(const T& X) : prev(nullptr), next(nullptr), data(X) {}
	};
	Node *first, *last;
	size_t count;
	bool isSorted;

public:
	List() :first(nullptr), last(nullptr), count(0), isSorted(true) {}
	List(const List&);
	~List() { clear(); }
	void clear();
	void empty() { clear(); }
	List& operator=(const List&);
	size_t size()const { return count; }
	void push_back(const T&);

	class iterator {
		Node *current;
	public:
		iterator (Node *p=nullptr): current(p){}
		T& operator* () const { return current->data; }
		bool operator==(const iterator& p) const { return current == p.current; }
		bool operator!=(const iterator& p) const { return current != p.current; }
		iterator& operator++() {
			if (current) {
				current = current->next;
			}
			else {
				throw ErrorOutOfBounds();
			}
			return *this();
		}
		iterator operator++(int) { //postfix operator
			Node *tmp = current;
			if (current) {
				current = current->next;
			}
			else {
				throw ErrorOutOfBounds();
			}
			return iterator(tmp);
		}
	};

	iterator begin() const { return iterator(first); }
	iterator end() const { return iterator(nullptr); }

	class reverse_iterator {
		Node *current;
	public:
		reverse_iterator(Node *p = nullptr) : current(p) {}
		T& operator* () const { return current->data; }
		bool operator==(const reverse_iterator& p) const { return current == p.current; }
		bool operator!=(const reverse_iterator& p) const { return current = p.current; }
		reverse_iterator& operator++() {
			if (current) {
				current = current->prev;
			}
			else {
				throw ErrorOutOfBounds();
			}
			return *this();
		}
		reverse_iterator operator++(int) { //postfix operator
			Node *tmp = current;
			if (current) {
				current = current->prev;
			}
			else {
				throw ErrorOutOfBounds();
			}
			return reverse_iterator(tmp);
		}
	};

	iterator rbegin() const { return reverse_iterator(last); }
	iterator rend() const { return reverse_iterator(nullptr); }

	iterator find(const T& X) const;
	void sort();
	T& operator[](unsigned int)const;
};
// -----------------------------------------------------------
template <typename T>
void List<T>::push_back(const T& X) {
	if (!first) {
		first = last = new Node(X);
	}
	else {
		last->next = new Node(X);
		last->next->prev = last;
		last = last->next;
	}
	++count;
	isSorted = false;
}
// -----------------------------------------------------------
template <typename T>
void List<T>::clear() {
	Node *tmp;
	while (first) {
		tmp = first;
		first = first->next;
		delete tmp;
	}
	count = 0;
	first = last = nullptr;

}
// -----------------------------------------------------------
template <typename T>
List<T>::List(const List<T>& A) {
	Node *tmp = A.first;
	if (tmp) {
		last = first = new Node(tmp->data);
		tmp = tmp->next;
		while (tmp) {
			last->next = new Node(tmp->data);
			last->next->prev = last;
			last = last->next;
			tmp = tmp->next;
		}
	}
	else {
		first = last = nullptr;
	}
	count = A.count;
	isSorted = A.isSorted;
}
// -----------------------------------------------------------
template <typename T>
List<T>& List<T>::operator=(const List<T>& A) {
	if (this != &A) {
		clear();
		Node *tmp = A.first;
		while (tmp) {
			push_back(tmp->data);
			tmp = tmp->next;
		}
		isSorted = A.isSorted;
	}
	return *this;
}
// -----------------------------------------------------------

template <typename T>
T& List<T>::operator[](unsigned int i)const {
	if (i >= count) throw ErrorOutOfBounds();
	Node *tmp;
	if (i <= count / 2) {
		tmp = first;
		unsigned int n = 0;;
		while (n++ < i) {
			tmp = tmp->next;
		}
	}
	else {
		tmp = last;
		unsigned int n = count - 1;
		while ((n--) > i)
			tmp = tmp->prev;
	}
	return tmp->data;
}

template <typename T>
typename List<T>::iterator List<T>::find(const T& X)const {
	Node *now = first;
	if (isSorted) {
		while (now) {
			if (now->data < X) now = now->next;
			else if (now->data == X) return iterator(now);
			else return end();
		}
	}
	else {
		while (now) {
			if (now->data == X)
				return iterator(now);
			now = now->next;
		}
	}
	return end();
}

template <typename T>
void List<T>::sort() {
	if (first == last || isSorted) {
		isSorted = true;
		return;
	}
	do {
		Node *begins[2], *ends[2];
		bool p = 0;
		ends[p] = begins[p] = first;
		first = first->next;
		ends[!p] = begins[!p] = nullptr;
		while (first) {
			if (first->data < ends[p]->data) p = !p;
			if (!begins[p]) begins[p] = first;
			else ends[p]->next = first;
			ends[p] = first;
			first = first->next;
		}
		if (ends[p]) ends[p]->next = nullptr;
		if (ends[!p]) ends[!p]->next = nullptr;
		if (begins[!p]) {
			bool s1, s2;
			p = (begins[0]->data < begins[1]->data) ? 0 : 1;
			last = first = begins[p];
			begins[p] = begins[p]->next;
			while (begins[p]) {
				s1 = (begins[p]->data < last->data);
				s2 = (begins[!p]->data < last->data);
				if (s1 == s2)
					p = (begins[0]->data < begins[1]->data) ? 0 : 1;
				else
					if (s1) p = !p;

				last->next = begins[p];
				begins[p] = begins[p]->next;
				last = last->next;
			}
			last->next = begins[!p]; last = ends[!p];
		}
		else {
			first = begins[p];
			isSorted = true;
		}
	} while (!isSorted);

	first->prev = nullptr;
	Node *now = first;
	while (now->next) {
		now->next->prev = now;
		now = now->next;
	}
	last = now;
}
#endif