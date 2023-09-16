#include "ReversePolishNotationComputer.h"
#include <iostream>
using namespace std;

int main() {

    zhong2hou sys;
    ReversePolishNotationComputer calc;

    int res;
    res = calc.solve(sys.solve("((15/(7-(1+1)))*3)-(2+(1+1))"));
    cout << res << endl;
    return 0;
}