#ifndef __SIMPLE_SELECTION_SORT_H__
#define __SIMPLE_SELECTION_SORT_H__

#ifndef DEFAULT_INFINITY
#define DEFAULT_INFINITY 0x3f3f3f3f
#endif
#include "../../Assistance.h"

template<typename E>
class SimpleSelectionSort
{
public:
    void sort(E arr[], int length) {
        for (int i = 0; i < length - 1; i++)
        {
            E minKey = DEFAULT_INFINITY;
            int target = i;
            for (int j = i+1; j < length; j++)
                if (arr[j] < minKey) target=j;
            if (target != i) Swap(a[i], a[j]);
        }
    }
};

#endif