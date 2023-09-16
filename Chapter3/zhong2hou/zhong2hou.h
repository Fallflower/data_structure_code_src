#include<string>
#include "../Stack/Stack.h"
using namespace std;

class zhong2hou
{
private:
    LinkStack<char> operators;
public:
    zhong2hou(){}

    string solve(const string& notation) {
        operators.Clear();

        string res = "";
        int tag = 0;
        for (int i = 0; i < notation.size(); i++)
        {
            char d = notation[i];
            if (d >= '0' && d <= '9') {
                res += d;
                if ((i+1) <notation.size() && notation[i+1]>='0' && notation[i+1]<='9') continue;
                res += ' ';
            }
            else if (d == '(')
                operators.Push('(');
            else if (d == ')') {
                char c;
                while((operators.Pop(c)) && c!='(') {
                    res += c;
                    res += ' ';
                }
            }
            else if (d == '+' || d == '-' || d == '*' || d == '/')
            {
                char c;
                if (d == '*' || d == '/')
                    while((operators.Pop(c)) && c!='+' && c!='-' && c!='(') {
                        res += c;
                        res += ' ';
                    }
                else if (d == '+' || d == '-')
                    while(operators.Pop(c) && c!='(') {
                        res += c;
                        res += ' ';
                    }
                operators.Push(d);
            }
        }// 扫描完成
        char c;
        while(operators.Pop(c)) {
            res += c;
            res += ' ';
        }
        return res;
    }
};
