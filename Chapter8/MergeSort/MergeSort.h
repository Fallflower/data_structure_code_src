#include "../../Assistance.h"



template <class E>
class MergeSort {
private:
    E *B;
    void Merge(E A[], int low, int mid, int high) {
        int n = high - low + 1;
        int m = mid - low;
        for (int i = 0; i < n; i++)
            B[i] = A[low + i];
        int i, j, k;
        for (i = 0, j = m + 1, k = low; i <= m && j < n; k++) {
            if (B[i] <= B[j]) A[k] = B[i++];
            else A[k] = B[j++];
        }
        while(i <= m) A[k++] = B[i++];
        while(j < n) A[k++] = B[j++];
    }

public:
    MergeSort() {B = new E[100];}
    ~MergeSort() {delete[] B;}
    void sort(E A[], int low, int high) {
        if (low < high) {
            int mid = (low + high) / 2;
            sort(A, low, mid);
            sort(A, mid + 1, high);
            Merge(A, low, mid, high);
        }
    }
};