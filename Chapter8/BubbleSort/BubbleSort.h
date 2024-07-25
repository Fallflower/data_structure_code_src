#ifndef __BUBBLESORT__
#define __BUBBLESORT__
#include "../SortSolution.h"

template<class Etype>
class BubbleSort : public Solution<Etype>
{
public:
    void solve(Etype arr[], int n) {
        for (int i = 0; i < n; i++)
            for (int j = 1; j < n - i; j++)
                if (arr[j-1] > arr[j])
                    swap(arr[j-1], arr[j]);
    }
};
#endif