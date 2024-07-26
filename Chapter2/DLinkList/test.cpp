#include "DLinkList.h"
#include <iostream>
using namespace std;

int main()
{
    DLinkList<int> l;
    cout << l<< endl;

    l.Insert(1, 1);
    l.Insert(0, 2);
    l.Insert(2, 3);
    cout << l<< endl;
    l.DeleteByLoc(2);
    cout << l << endl;
    return 0;
}