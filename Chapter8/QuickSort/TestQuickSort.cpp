#include "QuickSort.h"
using namespace std;

struct myEtype {
    int data;

    myEtype(const int& d):data(d) {}

    ostream& output(ostream &out) const {
        out << data;
        return out;
    }

    friend bool operator<=(const myEtype& a, const myEtype& b) {
        return a.data <= b.data;
    }
    
    friend bool operator>=(const myEtype& a, const myEtype& b) {
        return a.data >= b.data;
    }
};

ostream& operator<<(ostream& out, const myEtype& e) {
    e.output(out);
    return out;
}

int main() {

    QuickSort<myEtype> qs;

    myEtype A[] = {25, 84, 21, 47, 15, 27, 68, 35, 20};
    qs.sort(A, 9);
    Display(A, 9);

    return 0;
}