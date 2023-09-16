#include<iostream>
using namespace std;

template<class Elemtype>
struct DNode{
    Elemtype data;
    DNode *prior, *next;
};

template<class Elemtype>
class DLinkList{
private:
    DNode<Elemtype> *head;
    int length;

    // 结点p后面插入结点s
    bool InsertNextNode(DNode<Elemtype> *p, DNode<Elemtype> *s) {
        if (p == NULL || s == NULL)
            return false;
        s->next = p->next;
        if (p->next != NULL)
            p->next->prior = s;
        p->next = s;
        s->prior = p;
        length++;
        return true;
    }
    // 删除结点p后面的结点，如果成功返回被删结点指针
    DNode<Elemtype>* DeleteNextNode(DNode<Elemtype> *p) {
        if (p == NULL)
            return NULL;
        DNode<Elemtype> * q = p->next;
        if (q != NULL)
        {
            p->next = q->next;
            if (q->next != NULL)
                q->next->prior = p;
            length--;
        }
        return q;
    }

public:

    DLinkList() {
        head = NULL;
        length = 0;
    }
    ~DLinkList() {
        DNode<Elemtype> *p = head;
        for (; p != NULL; p=p->next)
        {
            p = p->next;
            delete (p->prior);
        }
    }

    int getLength() const{
        return length;
    }

    bool Insert(const Elemtype& e, const int& loc) {
        if (loc < 1 || loc > length + 1)
            return false;
        if (head == NULL)
        {
            head = new DNode<Elemtype>{e, NULL, NULL};
            length = 1;
            return true;
        }
        int i = 1;
        DNode<Elemtype> *p = head, *s;
        while (i < loc - 1)
        {
            p = p->next;
            i++;
        }
        if (p == NULL)
            return false;
        s = new DNode<Elemtype>;
        s->data = e;
        return InsertNextNode(p, s);
    }

};
