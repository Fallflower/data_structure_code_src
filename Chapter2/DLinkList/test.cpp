#include "DLinkList.h"
#include <iostream>
using namespace std;

int main()
{
    DLinkList<int> l;
    int arr[10] = {1,7,7,8,3,4,4,5,6,2};
    l.Insert(arr, 10, 1);
    cout << l << endl;
    cout << l.getLength() << endl;
    l.Insert(1, 1);
    cout << l << endl;
    l.Insert(2, 0);
    cout << l << endl;
    l.Insert(3, 2);
    cout << l << endl;
    l.DeleteByLoc(2);
    cout << l << endl;
    l.DeleteAllElem(1);
    cout << l << endl;
    l.DeleteFirstElem(4);
    cout << l << endl;
    
    return 0;
}