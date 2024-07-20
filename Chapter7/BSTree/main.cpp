#include "BSTree.h"
using namespace std;

void Visit(const char& c) {
    printf("%c", c);
}

int main()
{
    char arr[] = {'A', 'B', 'C', 'D' ,'E'};
    BSTree<char> t(arr, 5);

    t.InOrderShow(Visit);
    // cout << t.root->getElem() << endl;
    return 0;
}