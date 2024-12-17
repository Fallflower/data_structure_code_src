#include "MinHeapSort.h"
// #include "MaxHeapSort.h"

int main()
{
    int a[11] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    HeapSort(a, 10);
    Display(a, 11);
    return 0;
}