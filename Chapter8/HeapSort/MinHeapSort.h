#include "../../Assistance.h"

template <class E>
void HeapAdjust(E A[], int k, int n) {
    A[0] = A[k];
    for (int j = 2*k; j <= n; j *= 2) {
        if (j < n && A[j] > A[j+1]) j++;
        if (A[0] <= A[j]) break;
        else {
            A[k] = A[j];
            k = j;
        }
    }
    A[k] = A[0];
}

template <class E>
void BuildMinHeap(E A[], int n) {
    for (int i = n / 2; i > 0; i--)
        HeapAdjust(A, i, n);
}

template <class E>
void HeapSort(E A[], int n) {
    BuildMinHeap(A, n);
    for (int i = 1; i <= n; i++)
    {
        swap(A[i], A[1]);
        HeapAdjust(A, i + 1, n)
    }
    
}
