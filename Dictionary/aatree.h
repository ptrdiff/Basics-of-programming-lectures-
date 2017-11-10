#ifndef _AATREE_2017_
#define _AATREE_2017_

template<typename T>
class AATree {
	struct Node {
		Node *left, *right, *parent;
		unsigned char Lev;
		T data;
		Node(const T &X) :left(nullptr), right(nullptr), parent(nullptr), data(X), Lev(1) {}
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
	size_t count;
	Node *skew(Node *);
	Node *split(Node *);
public:
	AATree() :root(nullptr), count(0) {}
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
};

template <typename T>
void AATree<T>::insert(const T &X) {
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

	now = now->parent;
	while (now) {
		now = skew(now);
		Node* now2 = split(now);
		if (now == now2) break;
		now = now2;
		now = now->parent;
	}
}

template <typename T>
typename AATree<T>::Node *AATree<T>::skew(typename AATree<T>::Node * S) {
	if (!S) return S;
	Node *L;
	if (S->left) L = S->left; else return S;
	if (L->Lev != S->Lev) return S;
	S->left = L->right;
	if (L->right) L->right->parent = S;

	L->parent = S->parent;
	if (S->parent) {
		if (S->parent->left == S) S->parent->left = L;
		else S->parent->right = L;
	}
	else root = L;

	L->right = S;
	S->parent = L;
	return L;
}


template <typename T>
typename AATree<T>::Node *AATree<T>::split(typename AATree<T>::Node * S) {
	if (!S) return S;
	Node *R;
	if (S->right) R = S->right; else return S;
	if (R->Lev != S->Lev) return S;
	if (!(R->right)) return S;
	if (R->right->Lev != R->Lev) return S;

	S->right = R->left;
	if (R->left) R->left->parent = S;
	R->parent = S->parent;
	if (S->parent) {
		if (S->parent->left == S) S->parent->left = R;
		else S->parent->right = R;
	}
	else root = R;
	R->left = S;
	S->parent = R;
	++(R->Lev);
	return R;
}
#endif 
