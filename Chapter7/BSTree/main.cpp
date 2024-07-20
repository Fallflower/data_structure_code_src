#include "BSTree.h"
using namespace std;

template<class ElemType>
void Visit(const ElemType& c) {
    cout << c;
}

int main()
{
    try {
        int arr[] = {3, 1, 2, 4, 5};
        BSTree<int> t(arr, 5);
        t.InOrderShow(Visit);
        t.Delete(1);
        t.InOrderShow(Visit);
        t.Delete(3);
        t.InOrderShow(Visit);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    cout << endl;
    return 0;
}