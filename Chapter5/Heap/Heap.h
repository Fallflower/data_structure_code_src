#ifndef __MAX_HEAP_H__
#define __MAX_HEAP_H__
#include "../../Assistance.h"

template<class E>
class MaxHeap
{
private:
    E *data;
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

public:
    /*
    所有非终端节点：编号 i <= floor(n / 2)
    */
    MaxHeap():length(0), data(NULL) {}
    MaxHeap(E A[], const int& n) {
        makeHeap(A, n);
    }

    void makeHeap(E A[], const int& len) {
        delete[] data;

        length = len;
        data = new E[length + 1]{0};
        for (int i = 0; i <= length; i++)
            data[i+1] = A[i];
        for (int i = length/2; i > 0; i--) // 调整所有非终端结点
            adjustHeap(i);
        

        Display(data, length);
    }

    ~MaxHeap() {
        delete[] data;
    }
};




#endif