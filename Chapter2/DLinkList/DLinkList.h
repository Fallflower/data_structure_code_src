#ifndef __DLINKLIST__
#define __DLINKLIST__
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
        if (p == nullptr || s == nullptr)
            return false;
        s->next = p->next;
        if (p->next != nullptr)
            p->next->prior = s;
        p->next = s;
        s->prior = p;
        length++;
        return true;
    }
    // 删除结点p后面的结点，如果成功返回被删结点指针
    DNode<Elemtype>* DeleteNextNode(DNode<Elemtype> *p) {
        if (p == nullptr)
            return nullptr;
        DNode<Elemtype> * q = p->next;
        if (q != nullptr)
        {
            p->next = q->next;
            if (q->next != nullptr)
                q->next->prior = p;
            length--;
        }
        return q;
    }

public:

    DLinkList() {
        head = nullptr;
        length = 0;
    }
    ~DLinkList() {
        DNode<Elemtype> *p = head;
        for (; p != nullptr; p=p->next)
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
        if (head == nullptr)
        {
            head = new DNode<Elemtype>{e, nullptr, nullptr};
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
        if (p == nullptr)
            return false;
        s = new DNode<Elemtype>;
        s->data = e;
        return InsertNextNode(p, s);
    }

    DNode<Elemtype> * DeleteFirstElem(const Elemtype& e) {

    }

    DNode<Elemtype> * DeleteAllElem(const Elemtype& e) {

    }

    DNode<Elemtype> * DeleteByLoc(const int& loc) {
        if (loc < 1 || loc > length || head == nullptr)
            return nullptr;
        int i = 1;
        DNode<Elemtype> *p = head;
        while (i < loc - 1)
        {
            p = p->next;
            i++;
        }
        if (p == nullptr)
            return nullptr;
        return DeleteNextNode(p);
    }

    ostream& output(ostream& out) const {
        DNode<Elemtype> *p = head;
        out << "List: [ ";
        for (int i = 0; i < length && p!=nullptr; i++)
        {
           out << p->data;
           p = p->next;
           if (i + 1 < length && p!=nullptr) out << ", ";
        }
        out << " ]";
        return out;
    }
};

template<class Etype>
ostream& operator<<(ostream& out, const DLinkList<Etype> &l) {
    l.output(out);
    return out;
}

#endif