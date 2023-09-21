#ifndef __MAX_HEAP_H__
#define __MAX_HEAP_H__
#include "../../Assistance.h"
#define MAX_SIZE 100
template<class E>
class MaxHeap
{
private:
    E data[MAX_SIZE+1];
    int length;

    void adjustHeap(int k) {
        data[0] = data[k];
        for (int i = 2*k; i <= length; i*=2)
        {
            if (i < length && data[i] < data[i+1])
                i++;
            if (data[0]>=data[i]) break;
            else {
                data[k] = data[i];
                k = i;
            }
        }
        data[k] = data[0];
    }

    void percolateUp(const int& holeIndex, const E& e) {
        int hi = holeIndex;
        int pi = holeIndex / 2;
        while (hi > 1 && data[pi] < e)
        {
            data[hi] = data[pi];
            hi = [pi];
            pi /= 2;
        }
        data[hi] = e;
    }

public:
    /*
    所有非终端节点：编号 i <= floor(n / 2)
    */
    MaxHeap(): length(0) {}
    MaxHeap(const E A[], const int& n) {
        makeHeap(A, n);
    }

    void makeHeap(const E A[], const int& len) {
        length = len;
        for (int i = 0; i < length; i++)
            data[i+1] = A[i];
        for (int i = length/2; i > 0; i--) // 调整所有非终端结点
            adjustHeap(i);
        
        // TestHeap
        Display(data, length+1);
    }

    void Insert(const E& e) {
        if (length == MAX_SIZE) throw Error("Heap array OVERFLOW!");
        percolateUp(++length, e);
    }
};




#endif