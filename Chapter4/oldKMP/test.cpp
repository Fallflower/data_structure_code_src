#include "oldKMP.h"
#include <iostream>

using namespace std;

int main() {
    oldKMP okmp("aaaab");

    int res = okmp.solve("aaabaaaab");
    cout << res << endl;

    return 0;
}