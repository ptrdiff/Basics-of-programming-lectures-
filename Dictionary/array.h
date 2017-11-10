#ifndef _ARRAY_2017_
#define _ARRAY_2017_
#include "Errors.h"
#include <algorithm>
#define QUICK_SORT
template <typename T>
class Array {
	T *data;
	bool isSorted;
	std::size_t Len, maxLen;
	void QuickSort(T*, size_t);
public:
	Array(std::size_t N = 0) : Len(0), maxLen(N), data(nullptr), isSorted(true) {
		if (maxLen > 0) {
			data = new T[maxLen];
			if (!data) throw ErrorBadAlloc();
		}
	}
	Array(const Array &A) {
		Len = A.Len;
		maxLen = A.maxLen;
		isSorted = A.isSorted;
		if (maxLen > 0) {
			data = new T[maxLen];
			if (!data) throw ErrorBadAlloc();
		}
		for (std::size_t i = 0; i < Len; ++i) {
			data[i] = A.data[i];
		}
	}
	~Array() { clear(); }
	void push_back(const T&);
	Array&operator=(const Array&);
	std::size_t size() const { return Len; }
	std::size_t maxsize() const { return maxLen; }
	void clear() {
		if (data) {
			delete[] data;
			data = nullptr;
			Len = maxLen = 0;
		}
	}
	void empty() { Len = 0; }
	T& operator[](unsigned int i) const {
		if (i > Len) {
			throw ErrorOutOfBounds();
		}
		return data[i];
	}

	class iterator {
		T *current;
	public:
		iterator(T *p = nullptr) : current(p) {}
		T& operator*()const { return *current; }
		bool operator==(const iterator& p) const {
			return current == p.current;
		}
		bool operator!=(const iterator& p) const {
			return current != p.current;
		}

		iterator& operator++() { ++current; return *this; }

		iterator operator++(int) {
			T *tmp = current;
			++current;
			return iterator(tmp);
		}
	};

	iterator begin() const { return iterator(data); }
	iterator end() const { return iterator(data + Len); }

	class reverse_iterator {
		T *current;
	public:
		reverse_iterator(T *p = nullptr) : current(p) {}
		T& operator*()const { return *current; }
		bool operator==(const reverse_iterator& p) const {
			return current == p.current;
		}
		bool operator!=(const reverse_iterator& p) const {
			return current != p.current;
		}

		reverse_iterator& operator++() { --current; return *this; }

		reverse_iterator operator++(int) {
			T *tmp = current;
			--current;
			return reverse_iterator(tmp);
		}
	};

	reverse_iterator rbegin() const { return reverse_iterator(data + Len - 1); }
	reverse_iterator rend() const { return reverse_iterator(data - 1); }


	//you should realize FIND and SORT
	void sort() { QuickSort(data, Len); isSorted = true; };
	bool is_sorted();
	iterator find(const T&)const;
};
// -----------------------------------------------------------
template <typename T>
void Array<T>::push_back(const T& X) {
	if (Len + 1 > maxLen) {
		// out of memory, you need to get new and copy old to it
		std::size_t newLen;
		newLen = maxLen < 20 ? (maxLen + 1) : (1.1*maxLen);
		T *tmp = new T[newLen];
		if (!tmp) throw ErrorBadAlloc();
		for (std::size_t i = 0; i < Len; ++i) {
			tmp[i] = data[i];
		}
		delete[] data;
		data = tmp;
		maxLen = newLen;
	}
	data[Len++] = X;
	isSorted = false;
}
// -----------------------------------------------------------
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& A) {
	if (this != &A) {
		clear();
		Len = A.Len;
		maxLen = A.maxLen;
		isSorted = A.isSorted;
		if (maxLen > 0) {
			data = new T[maxLen];
			if (!data) throw ErrorBadAlloc();
			for (std::size_t i = 0; i < Len; ++i) {
				data[i] = A.data[i];
			}
		}
	}
	return *this;
}
// -----------------------------------------------------------
template <typename T>
bool Array<T>::is_sorted() {
	for (size_t i = 0; i < Len-1; ++i) {
		if ((*this)[i + 1].get_word() < (*this)[i].get_word()) {
			return false;
		}
	}
	return true;
}
// -----------------------------------------------------------
#ifdef BUBBLE_SORT
template <typename T>
void Array<T>::sort() {
	if (!is_sorted()) {
		for (size_t j = 0; j < Len; ++j) {
			for (size_t i = Len; i > j; --i) {
				if ((*this)[i].get_word() < (*this)[i - 1].get_word()) {
					std::swap((*this)[i], (*this)[i - 1]);
				}
			}
		}
	}
}
#endif
// -----------------------------------------------------------
#ifdef QUICK_SORT
	template <typename T>
	void Array<T>::QuickSort(T* A, size_t n) {
		if (n == 0 || isSorted) {
			return;
		}
		size_t i = 0;
		size_t j = n - 1;
		T p = A[i + (j - i) / 2];
		while (i < j) {
			while (A[i] < p) ++i;
			while (p < A[j]) --j;
			if (i < j) {
				std::swap(A[i], A[j]);
				++i; --j;
			}
			else if (i == j) {
				++i;
				if (j) --j;
				else break;
			}
		}
		if (i >(n - 1) / 2) {
			if (i < n - 1) QuickSort(A + i, n - i);
			if (j > 0) QuickSort(A, j + 1);
		}
		else {
			if (j > 0) QuickSort(A, j + 1);
			if (i < n - 1) QuickSort(A + i, n - i);
		}
	}
#endif
// -----------------------------------------------------------
template <typename T>
typename Array<T>::iterator Array<T>::find(const T &X)const {
	if (isSorted) {
		if (Len == 0) return end();
		size_t left = 0, right = Len - 1, p;
		while (left < right) {
			p = left + (right - left) / 2;
			if (data[p] < X) left = p + 1;
			else if (data[p] == X) {
				return iterator(data + p);
			}
			else if (p == 0) {
				break;
			}
			else {
				right = p - 1;
			}
		}
		if (data[left] == X) return iterator(data + left);
		return end();
	}
	else {
		for (size_t i = 0; i < Len; ++i) {
			if (data[i] == X) {
				return iterator(data + i);
			}
		}
	}
	return end();
}
#endif // !_ARRAY_2017_

//#ifdef QUICK_SORT
//template <typename T>
//void Array<T>::sort() {
//	int N = Len, size = 1;
//	while (N > 0) {
//		N >>= 1;
//		++size;
//	}
//	int *StackLeft = new int[size];
//	int *StackRight = new int[size];
//	int LastInStack = -1;
//	++LastInStack;
//	StackLeft[LastInStack] = 0;
//	StackRight[LastInStack] = Len - 1;
//	while (LastInStack > -1) {
//		int left, right;
//		left = StackLeft[LastInStack];
//		right = StackRight[LastInStack];
//		--LastInStack;
//		int pindex = left + (right - left) / 2;
//		DictPara p = (*this)[pindex];
//
//		int i = left, j = right;
//
//		while (i < j) {
//			while ((*this)[i].get_word() < p.get_word()) {
//				++i;
//			}
//			while (p.get_word() < (*this)[j].get_word()) {
//				--j;
//			}
//			if (i < j) {
//				std::swap((*this)[i], (*this)[j]);
//				++i; --j;
//			}
//			else {
//				if (i == j) {
//					++i; --j;
//				}
//			}
//		}
//		if (i > pindex) {
//			if (j > left) {
//				++LastInStack; StackLeft[LastInStack] = left; StackRight[LastInStack] = j;
//			}
//			if (i < right) {
//				++LastInStack; StackLeft[LastInStack] = i; StackRight[LastInStack] = right;
//			}
//		}
//		else {
//			if (i < right) {
//				++LastInStack; StackLeft[LastInStack] = i; StackRight[LastInStack] = right;
//			}
//			if (j > left) {
//				++LastInStack; StackLeft[LastInStack] = left; StackRight[LastInStack] = j;
//			}
//		}
//	}
//	delete[] StackLeft;
//	delete[] StackRight;
//}
//#endif