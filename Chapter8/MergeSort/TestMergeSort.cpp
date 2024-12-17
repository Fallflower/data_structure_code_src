#include "MergeSort.h"

int main()
{
    int A[7] = {49,38,65,97,76,13,27};
    MergeSort<int> s;
    s.sort(A, 0, 6);
    Display(A, 7);
    return 0;
}