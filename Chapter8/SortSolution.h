#ifndef __SOLUTION__
#define __SOLUTION__
#include "../Assistance.h"

template<class Etype>
class Solution {
public:
    Solution() {}

    virtual void solve(Etype arr[], int n) = 0;
};
#endif