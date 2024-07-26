#ifndef __DLINKLIST__
#define __DLINKLIST__
#include<iostream>
using namespace std;


template<class Elemtype>
struct DNode{
    Elemtype data;
    DNode *prior, *next;

    DNode() {}
    DNode(const Elemtype& e) : data(e), prior(nullptr), next(nullptr) {}
    DNode(const Elemtype& e, DNode<Elemtype> *p, DNode<Elemtype> *n) : data(e), prior(p), next(n) {}
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
            if (p->prior!=nullptr) delete (p->prior);
    }

    int getLength() const{
        return length;
    }

    //将元素插入到第loc个位置（原来的元素顺势后移）
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
        s = new DNode<Elemtype>(e);
        return InsertNextNode(p, s);
    }

    bool Insert(const Elemtype arr[], const int& n, const int& loc) {
        if (loc < 1 || loc > length + 1 || n < 1)
            return false;
        int flag = 0;
        if (head == nullptr)
        {
            head = new DNode<Elemtype>{arr[0], nullptr, nullptr};
            flag = 1;
        }
        DNode<Elemtype> *p = head;
        for (int i = 1; i < loc - 1; i++)
            p = p->next;
        for (int i = flag; i < n && InsertNextNode(p, new DNode<Elemtype>(arr[i])); i++);
        return 1;
    }

    DNode<Elemtype> * DeleteFirstElem(const Elemtype& e) {

    }

    DNode<Elemtype> * DeleteAllElem(const Elemtype& e) {

    }

    bool DeleteByLoc(const int& loc) {
        if (loc < 1 || loc > length || head == nullptr)
            return 0;
        int i = 1;
        DNode<Elemtype> *p = head, *s;
        while (i < loc - 1)
        {
            p = p->next;
            i++;
        }
        if (p == nullptr)
            return 0;
        s = DeleteNextNode(p);
        if (s == nullptr)
            return 0;
        delete s;
        return 1;
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