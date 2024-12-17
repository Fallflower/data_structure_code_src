#include "../../Assistance.h"

template <class E>
void BubbleSort(E a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = 0;
        for (int j = n - 1; j > i; j--)
            if (a[j] < a[j - 1]){
                swap(a[j], a[j - 1]);
                flag = 1;
            }
        if (!flag) break;
    }
}
