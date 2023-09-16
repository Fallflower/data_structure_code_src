#include "DLinkList.h"
#include <iostream>
using namespace std;

int main()
{
    DLinkList<int> l;
    cout << l.getLength() << endl;

    cout << l.Insert(1, 1) << endl;
    l.Insert(0, 1);
    l.Insert(2, 3);
    cout << l.getLength() << endl;
    return 0;
}