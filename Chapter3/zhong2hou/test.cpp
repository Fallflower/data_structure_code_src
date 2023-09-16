#include "zhong2hou.h"
#include <iostream>
using namespace std;

int main() {
    zhong2hou sys;
    string result;

    result = sys.solve("((15/(7-(1+1)))*3)-(2+(1+1))");
    cout << result << endl;
    return 0;
}