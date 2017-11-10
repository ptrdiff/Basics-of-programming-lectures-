#include <iostream>

#define each(i,x) for(i=0; i<x; ++i)

#define _max(a,b) ( (a)>(b) ? (a) : (b) )

ptrdiff_t c = 0;

void randomArray (ptrdiff_t *A, ptrdiff_t n) {
	ptrdiff_t i; 
	each(i,n) A[i] = rand() % 100 - 50;
}

inline void printArray (ptrdiff_t *A,ptrdiff_t n){
	ptrdiff_t i;
	each(i,n) std::cout <<A[i] <<' ';
	std::cout << std::endl;

}

inline bool isSorted (ptrdiff_t *A, ptrdiff_t n) {
	ptrdiff_t i;
	each(i,n) if (A[i+1] < A[i] ) return false;
	return true;
}

void msd_radix_sort ( size_t *from, ptrdiff_t Len, size_t mask ) {
	if ( Len < 2 || mask == 0) return;
	ptrdiff_t i = 0, j = Len -1; 
	while (i<j) {
		while(i<Len &&!(from[i]&mask)) ++i;
		while ( j>=0 && (from[j] & mask)) --j;
		if(i<j){ std::swap(from[i], from[j]); ++c;}
	}
	ptrdiff_t mid = i;
	mask >>= 1;
	msd_radix_sort(from, mid, mask);
	msd_radix_sort(from+mid, Len-mid, mask);
} 

void radixSort ( ptrdiff_t *A, ptrdiff_t n) {
	ptrdiff_t i;
	size_t *x = (size_t*) A;
	each(i,n) x[i] ^=INT_MIN;
	msd_radix_sort(x,n,INT_MIN);
	each(i,n) x[i] ^= INT_MIN;

}

ptrdiff_t main() {
	ptrdiff_t n;
	do {std::cout<<"size="; std::cin >> n; } while (n<1);
	ptrdiff_t *M = new ptrdiff_t[n];
	randomArray(M,n);
	printArray(M,n);
	radixSort(M,n);
	printArray(M,n);
	delete[] M;
	std::cout<<"Swap = " << c;
	system("pause");
	return 0;
}
