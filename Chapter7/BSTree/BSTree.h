#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__
#include "BSTreeNode.h"
#include "../../Chapter3/CirQueue/CirQueue.h"
#include "../BinaryTree/BinaryTree.h"


template<typename E>
class BSTree : public BinaryTree
{
private:
    BSTreeNode<E> *root;

    BSTreeNode<E>* __get_most_left_in_rtree(BSTreeNode<E>* r) {
        if (r->rchild == nullptr) return nullptr;
        BSTreeNode<E>* p = r->rchild;
        while (p->lchild != nullptr)
        {
            p = p->lchild;
        }
        return p; 
    }
    
    BSTreeNode<E>* __get_most_right_in_ltree(BSTreeNode<E>* r) {
        if (r->lchild == nullptr) return nullptr;
        BSTreeNode<E>* p = r->lchild;
        while (p->rchild != nullptr)
        {
            p = p->rchild;
        }
        return p; 
    }

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
        {
            if (pp->lchild == p) pp->lchild = NULL;
            else if (pp->rchild == p) pp->rchild = NULL;
            else root = NULL;
            delete p;
        } 
        else if (p->lchild == NULL) { // 找右子树中最左下的来替代

        }
        else if (p->rchild == NULL) { // 找左子树中最右下的来替代

        }
        else { // 找中序前驱或后继

        }
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
        InOrderVisit(root, Visit);
    }
};

#endif