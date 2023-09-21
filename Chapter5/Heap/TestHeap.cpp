#include "Heap.h"

using namespace std;

int main() {
    int A[] = {1, 2, 3, 4, 5};
    MaxHeap<int> H;
    H.makeHeap(A, 5);
    return 0;
}