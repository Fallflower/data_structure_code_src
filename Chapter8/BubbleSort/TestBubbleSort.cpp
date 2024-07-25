#include "BubbleSort.h"
using namespace std;

int main() {

    int arr[10] = {9,5,3,0,0,1,2,4,7,8};
    BubbleSort<int> S;
    S.solve(arr, 10);
    Display(arr, 10);
    return 0;
}