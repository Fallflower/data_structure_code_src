#include "../../Assistance.h"

template <class E>
void HeapAdjust(E A[], int k, int n) {
    A[0] = A[k];
    for (int j = 2*k; j <= n; j *= 2) {
        if (j < n && A[j] < A[j+1]) j++;
        if (A[0] >= A[j]) break;
        else {
            A[k] = A[j];
            k = j;
        }
    }
    A[k] = A[0];
}
template <class E>
void BuildMaxHeap(E a[], int n) { // <= 4n次关键词比较
    for (int i = n/2 ; i > 0; i--) 
        HeapAdjust(a, i, n);
}



template <class E>
void HeapSort(E a[], int n) {
    BuildMaxHeap(a, n);
    for (int i = n; i > 1; i--) {
        Swap(a[1], a[i]);
        HeapAdjust(a, 1, i-1);
    }
}