#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include "../../Assistance.h"

template<typename E>
class QuickSort
{
private:
    int partition(E arr[], const int& l, const int& h) {
        int low = l, high = h;
        E pivot = arr[low];
        while (low < high)
        {
            while (low < high && arr[high]>= pivot) // 每次一定先动high指针
                high--;
            arr[low] = arr[high];
            while (low < high && arr[low] <= pivot)
                low++;
            arr[high] = arr[low];
        }
        arr[low] = pivot;
        return low;
    }

    void sort(E arr[], const int& low, const int& high) {
        if (low < high) {
            int pivot_loc = partition(arr, low, high);
            sort(arr, low, pivot_loc - 1);
            sort(arr, pivot_loc + 1, high);
        }
    }

public:
    void sort(E arr[], const int& length) {
        sort(arr, 0, length - 1);
    }
};




#endif
