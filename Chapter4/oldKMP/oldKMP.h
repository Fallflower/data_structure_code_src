#include<string>
#include<iostream>
using namespace std;

class oldKMP
{
private:
    int *next;
    int length;
    string T;

    void Clear() {
        delete next;
    }

    string prefix(const string& p, int i) const {
        return p.substr(0, i);
    }

    string suffix(const string& p, int i) const {
        return p.substr(p.size() - i, i);
    }

public:
    oldKMP():next(NULL),length(0) {}
    oldKMP(const string& pattern) { // 手算法求next数组
        length = pattern.size();
        next = new int[length+1]{0};
        next[2] = 1;
        for (int i = 3; i <= length; i++)
        {
            string np = pattern.substr(0, i - 1);
            int j = 0;
            for (j = i - 2; j > 0; j--)
                if (prefix(np, j) == suffix(np, j))
                    break;
            next[i] = j + 1;
        }
        T = pattern;
    }

    ~oldKMP() {
        Clear();
    }

    int solve(const string& main_str) { // 返回值为起始位置的个数（非下标）
        for (int p = 1; p <= length; p++)
        {
            cout << next[p];
        }
        cout << endl;
        int i = 1, j = 1;
        while(i <= main_str.size() && j <= length)
            if (j == 0 || main_str[i-1] == T[j-1])
                {i++; j++;}
            else 
                j = next[j];
        if (j > length)
            return i - length;
        else
            return 0;
    }
};