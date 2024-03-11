#include"BinaryTree.h"
using namespace std;

void Visit(const char& c) {
    printf("%c", c);
}

int main()
{
    char InOrder[] = {'A', 'B', 'C', 'D' ,'E'};
    char PreOrder[] = {'C', 'A', 'B', 'D', 'E'};
    char PostOrder[] = {'B', 'A', 'E', 'D', 'C'};
    int n = 5;

    BinaryTree<char> T1(InOrder, PreOrder, n, "pre");

    T1.PostOrderShow(Visit);

    cout << endl;
    
    BinaryTree<char> T2(InOrder, PostOrder, n, "post");

    T2.PreOrderShow(Visit);

    return 0;
}