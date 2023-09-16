#include "newKMP.h"
#include <iostream>

using namespace std;

int main() {
    newKMP kmp("aaaab");

    int res = kmp.solve("aaabaaaab");
    cout << res << endl;

    return 0;
}