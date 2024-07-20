#include "BSTree.h"
using namespace std;

void Visit(const char& c) {
    cout << c;
}

int main()
{
    try {
        char arr[] = {'A', 'B', 'C', 'D', 'E'};
        BSTree<char> t(arr, 5);
        t.InOrderShow(Visit);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}