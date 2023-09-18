#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__
// #include<stdlib.h>
#include "../../Chapter3/CirQueue/CirQueue.h"

template<typename E>
struct BSTreeNode
{
    E data;
    BSTreeNode *lchild, *rchild;
};

template<typename E>
class BSTree
{
private:
    BSTreeNode<E> *root;


    void InOrderVisit(BSTreeNode<E> *r, void Visit(const E& e)) {
        if (r != NULL) {
            InOrderVisit(r->lchild, Visit);
            Visit(r->data);
            InOrderVisit(r->rchild, Visit);
        }
    }

    void Destroy(BSTreeNode<E> *r) {
        if (r != NULL) {
            Destroy(r->lchild);
            Destroy(r->rchild);
            delete r;
        }
    }

    BSTreeNode<E> * parent(BSTreeNode<E> *p) {
        CirQueue<BSTreeNode<E>*> queue;
        queue.EnCirQueue(root);
        while (!queue.isEmpty())
        {
            BSTreeNode<E> *q;
            queue.DeCirQueue(q);
            if (q->lchild == p || q->rchild == p) return q;
            queue.EnCirQueue(q->lchild);
            queue.EnCirQueue(q->rchild);
        }
        return NULL;
    }

public:
    BSTree(E str[], int length) {
        T = NULL;
        int i = 0;
        while (i < length && Insert(root, str[i]))
            i++;
        
    }
    ~BSTree() {
        Destroy(root);
    }

    bool Insert(BSTreeNode<E> *p, const E& e) {
        if (p == NULL) {
            p = new BSTreeNode<E>{e, NULL, NULL};
            return 1;
        }
        else if (e == p->data)
            return 0;
        else if (e < p->data)
            return Insert(p->lchild, e);
        else
            return Insert(p->rchild, e);
    }

    bool Delete(const E& e) {
        BSTreeNode<E> * p = Search(e), pp;
        pp = parent(p);
        if (p->lchild == NULL && p->rchild == NULL)

    }

    BSTreeNode<E> *Search(E key) {
        BSTreeNode<E> *T = root;
        while (T != NULL && key != T->data)
        {
            if (key < T->data) T = T->lchild;
            else T = T->rchild;
        }
        return T;
    }

    void InOrderVisit(void Visit(const E& e)) {
        if (root != NULL)
            InOrderVisit(root, Visit);
    }
};

#endif