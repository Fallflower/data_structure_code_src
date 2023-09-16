#ifndef __LINK_STACK_H__
#define __LINK_STACK_H__
#include<cstdlib>
template<class E>
struct LinkStackNode
{
    E data;
    LinkStackNode* next;
};


template<class E>
class LinkStack
{
private:
    LinkStackNode<E> *head;
public:
    LinkStack():head(NULL){};
    ~LinkStack() {
        Clear();
    }

    void Clear() {
        LinkStackNode<E> *p;
        while (head != NULL)
        {
            p = head;
            head = head->next;
            delete p;
        }
    }

    bool isEmpty() const {
        return (head == NULL);
    }

    bool Push(const E& e) {
        // if (isEmpty()) {
        //     head = new LinkStackNode<E>{e, NULL};
        //     if (head == NULL) return false;
        //     return true;
        // }
        LinkStackNode<E> *p;
        p = new LinkStackNode<E>{e, head};
        if (p == NULL) return false;
        head = p;
        return true;
    }

    bool Pop(E& e) {
        if (isEmpty()) return false;
        e = head->data;
        LinkStackNode<E> *p = head;
        head = head->next;
        delete p;
        return true;
    }

    bool getTop(E& e) const {
        if (isEmpty()) return false;
        e = head->data;
        return true;
    }

    int getLength() const {
        int l = 0;
        LinkStackNode<E> *p = head;
        while (p != NULL)
        {
            p = p->next;
            l++;
        }
        return l;
    }

};
#endif