#include<string>
#include<iostream>
using namespace std;

class newKMP
{
private:
    int *nextval;
    int length;
    string T;

    void Clear() {
        delete nextval;
    }

    string prefix(const string& p, int i) const {
        return p.substr(0, i);
    }

    string suffix(const string& p, int i) const {
        return p.substr(p.size() - i, i);
    }

    void get_nextval() {
        nextval = new int[length+1];
        nextval[1] = 0;
        int i = 1, j = 0;
        while (i < length)
        {
            if (j == 0||T[i-1]==T[j-1]) {
                i++; j++;
                if (T[i-1] != T[j-1]) nextval[i]=j;
                else nextval[i] = nextval[j];
            }
            else
                j=nextval[j];
        }
        
    }

public:
    newKMP():nextval(NULL),length(0) {}
    newKMP(const string& pattern) { // 手算法求nextval数组
        T = pattern;
        length = pattern.size();
        /*两坨** 选其一：1. 模拟手算 2. 机算*/
        // 1.
        int *next = new int[length+1]{0};
        nextval = new int[length+1]{0};
        next[2] = 1;
        for (int i = 3; i <= length; i++)
        {
            string np = pattern.substr(0, i - 1);
            int j = 0;
            for (j = i - 2; j > 0; j--)
                if (prefix(np, j) == suffix(np, j))
                    break;
            next[i] = j + 1;
        } // 到此 求得next数组 需进化为 nextval
        for (int i = 2; i <= length; i++)
        {
            if (T[i-1] == T[next[i] - 1])
                nextval[i] = nextval[next[i]];
            else
                nextval[i] = next[i];
        }
        delete[] next;
        // /*-----------------------------*/
        // 2.
        // get_nextval();
    }

    ~newKMP() {
        Clear();
    }



    int solve(const string& main_str) { // 返回值为起始位置的个数（非下标）
        for (int p = 1; p <= length; p++)
        {
            cout << nextval[p];
        }
        cout << endl;
        int i = 1, j = 1;
        while(i <= main_str.size() && j <= length)
            if (j == 0 || main_str[i-1] == T[j-1])
                {i++; j++;}
            else 
                j = nextval[j];
        if (j > length)
            return i - length;
        else
            return 0;
    }
};