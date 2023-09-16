#include "ThreadTree.h"
#include <iostream>
using namespace std;

void Visit(const char& c) {
    cout << c << endl;
}

int main() {

    char pre[] = {'A', 'B', 'D', 'G', 'E', 'C', 'F'};
    char in[] = {'D', 'G', 'B', 'E', 'A', 'F', 'C'};

    ThreadTree<char> tree(pre, in, 7);
    tree.InOrderVisit(Visit);
    return 0;
}