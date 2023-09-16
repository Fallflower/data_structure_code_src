#include<string>
// #include "../CirQueue/CirQueue.h"
#include "../Stack/Stack.h"
#include "../zhong2hou/zhong2hou.h"

class ReversePolishNotationComputer
{
private:
    LinkStack<int> op_nums;
    // CirQueue<char> operators;
public:
    ReversePolishNotationComputer() {};

    int solve(string s) {
        op_nums.Clear();
        int res = -1;
        bool flag = 0;
        for (int i = 0; i < s.size(); i++)
        {
            // bool flag = 1;
            if (s[i] <= '9' && s[i] >= '0') {
                // if (flag)
                int o;
                if (flag && op_nums.Pop(o))
                    op_nums.Push((int)o*10+s[i]-'0');
                else
                    {op_nums.Push((int)s[i] - '0'); flag = 1;}
            }
            else if (s[i] == '+') {
                int a, b;
                if (op_nums.Pop(a) && op_nums.Pop(b))
                    op_nums.Push(a+b);
            }
            else if (s[i] == '-') {
                int a, b;
                if (op_nums.Pop(a) && op_nums.Pop(b))
                    op_nums.Push(b - a);
            }
            else if (s[i] == '*') {
                int a, b;
                if (op_nums.Pop(a) && op_nums.Pop(b))
                    op_nums.Push(a*b);
            }
            else if (s[i] == '/') {
                int a, b;
                if (op_nums.Pop(a) && op_nums.Pop(b))
                    op_nums.Push(b / a);
            }
            else if (s[i] == ' ') flag =0;
        }
        op_nums.getTop(res);
        return res;
    }
};