#include "Heap.h"

using namespace std;

void Visit(const int& e) {
    cout << e;
}

int main() {
    int A[] = {1, 2, 3, 4, 5};
    MaxHeap<int> H;
    H.makeHeap(A, 5);

    H.Insert(6);

    H.display(Visit);
    cout << endl;

    return 0;
}