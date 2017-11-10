#ifndef _BINTREE_2017_
#define _BINTREE_2017_

template<typename T>
class BinTree {
	struct Node {
		Node *left, *right, *parent;
		T data;
		Node(const T &X) :left(nullptr), right(nullptr), parent(nullptr), data(X) {}
		~Node() {
			if (left) delete left;
			if (right) delete right;
			right = left = parent = nullptr;
		}
		int level()const {
			int L = (left != nullptr) ? left->level() : 0;
			int R = (right != nullptr) ? right->level() : 0;
			return L > R ? L + 1 : R + 1;
		}
		Node *minimum() {
			Node *now = this;
			while (now->left != nullptr) now = now->left;
			return now;
		}

		Node *maximum() {
			Node *now = this;
			while (now->right != nullptr) now = now->right;
			return now;
		}

		Node *next() {
			if (right) return right->minimum();
			Node *p = parent, *now = this;
			while (p) {
				if (now == p->left)break;
				now = p; p = p->parent;
			}
			return p;
		}

		Node *prev() {
			if (left) return leftt->minimum();
			Node *p = parent, *now = this;
			while (p) {
				if (now == p->right)break;
				now = p; p = p->parent;
			}
			return p;
		}
	};
	Node *root;
	unsigned int count;
public:
	BinTree():root(nullptr), count(0) {}
	size_t size()const { return count; }
	void insert(const T &X);
	void push_back(const T &X) { insert(X); }
	int height()const { return (root != nullptr) ? root->level() : 0; }

	class iterator {
		Node *now;
	public:
		iterator(Node *p = nullptr) :now(p) {}
		const T& operator*()const { return now->data; }
		bool operator==(const iterator &p) const { return now == p.now; }
		bool operator!=(const iterator &p) const { return now != p.now; }
		iterator& operator++() { if (now) now = now->next(); return *this; }
		iterator& operator++(int) { Node *tmp = now; if (now) now = now->next(); return tmp; }
	};
	iterator begin()const {
		if (root) return iterator(root->minimum());
		return end();
	}
	iterator end()const {
		return iterator(nullptr);
	}

	class reverse_iterator {
		Node *now;
	public:
		reverse_iterator(Node *p = nullptr) :now(p) {}
		const T& operator*()const { return now->data; }
		bool operator==(const reverse_iterator &p) const { return now == p.now; }
		bool operator!=(const reverse_iterator &p) const { return now != p.now; }
		reverse_iterator& operator++() { if (now) now = now->next(); return *this; }
		reverse_iterator& operator++(int) { Node *tmp = now; if (now) now = now->prev(); return tmp; }
	};
	iterator rbegin()const {
		if (root) return reverse_iterator(root->maximum());
		return end();
	}
	iterator rend()const {
		return reverse_iterator(nullptr);
	}

	iterator find(const T& X)const {
		Node *now = root;
		while (now) {
			if (X == now->data) break;
			if (X < now->data) now = now->left; else now = now->right;
		}
		return iterator(now);
	}
	void balance();
};

template <typename T>
void BinTree<T>::insert(const T &X) {
	++count;
	if (root == nullptr) { root = new Node(X); return; }
	Node *now, *p;
	bool ToLeft;
	now = root;
	do {
		p = now;
		if (X < now->data) {
			now = now->left; ToLeft = true;
		}
		else {
			now = now->right; ToLeft = false;
		}
	} while (now);
	now = new Node(X);
	if (ToLeft) p->left = now; else p->right = now;
	now->parent = p;
}

template <typename T>
void BinTree<T>::balance() {
	if (count < 2) return;

	Node *q, *p, *r;
	p = root;
	while (p) {
		if (p->right == nullptr)
			p = p->left;
		else {
			q = p->parent;
			r = p->right;
			if (q) q->left = r; else root = r;
			r->parent = q;
			p->right = r->left;
			if (r->left) r->left->parent = p;
			r->left = p;
			p->parent = r;
			p = r;
		}
	}

	size_t n = 0, n2 = 1;
	for (size_t i = count + 1; i > 1; i >>= 1, ++n, n2 <<= 1);
	int Lishnee = count - (n2 - 1);

	q = root;
	while (Lishnee > 0) {
		p = q->left;
		p->right = q;
		p->parent = q->parent;
		if (p->parent) p->parent->left = p; else root = p;
		q->parent = p;
		q->left = nullptr;
		q = p->left;
		--Lishnee;
	}

	Node *red, *black;
	size_t BlackInStep = (n2 - 1) / 2;
	for (int step = 1; step < n; ++step, BlackInStep /= 2) {
		red = root;
		for (int i = 1; i <= BlackInStep; ++i) {
			black = red->left;
			black->parent = red->parent;
			if (black->parent) black->parent->left = black; else root = black;
			red->left = black->right;
			if (black->right) black->right->parent = red;
			black->right = red;
			red->parent = black;
			red = black->left;
		}
	}
}

#endif 
