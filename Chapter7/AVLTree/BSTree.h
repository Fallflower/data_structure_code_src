#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__
// #include "TreeNode.h"
#include "../../Chapter3/CirQueue/CirQueue.h"
#include "Tree.h"


template<typename E>
class BSTree : public Tree<E>
{
protected:

    TreeNode<E>* __get_most_left_in_rtree(TreeNode<E>* r) {
        TreeNode<E>* p = r->rchild;
        while (p->lchild != nullptr)
        {
            p = p->lchild;
        }
        return p; 
    }
    
    TreeNode<E>* __get_most_right_in_ltree(TreeNode<E>* r) {
        TreeNode<E>* p = r->lchild;
        while (p->rchild != nullptr)
        {
            p = p->rchild;
        }
        return p; 
    }

    TreeNode<E> * parent(TreeNode<E> *p, bool &r_or_l) {
        CirQueue<TreeNode<E>*> queue;
        queue.EnCirQueue(Tree<E>::root);
        while (!queue.isEmpty())
        {
            TreeNode<E> *q;
            queue.DeCirQueue(q);
            if (q->lchild == p || q->rchild == p) {
                if (q->lchild != nullptr)
                    r_or_l = q->lchild == p ? 0 : 1;
                else if (q->rchild != nullptr)
                    r_or_l = q->rchild == p ? 1 : 0;
                return q;
            }
            if (q->lchild != nullptr) queue.EnCirQueue(q->lchild);
            if (q->rchild != nullptr) queue.EnCirQueue(q->rchild);
        }
        return nullptr;
    }

    void Delete(TreeNode<E> * &p) {
        bool r_or_l;
        TreeNode<E> *pp = parent(p, r_or_l);
        if (p->lchild == nullptr && p->rchild == nullptr)
        {
            if (pp == nullptr) Tree<E>::root = nullptr;
            else if (r_or_l) pp->rchild = nullptr;
            else pp->lchild = nullptr;
            delete p;
        } else if (p->lchild == nullptr) { 
            if (pp == nullptr) Tree<E>::root = p->rchild;
            else if (r_or_l) pp->rchild = p->rchild;
            else pp->lchild = p->rchild;
            delete p;
        } else if (p->rchild == nullptr) { 
            if (pp == nullptr) Tree<E>::root = p->lchild;
            if (r_or_l) pp->rchild = p->lchild;
            else pp->lchild = p->lchild;
            delete p;
        } else { // 找中序前驱或后继
            TreeNode<E> *q = __get_most_left_in_rtree(p);
            E e = q->elem;
            Delete(q);
            p->elem = e;
        }
    }

public:
    BSTree(E *arr, int length) {
        int i = 0;
        while (i < length) {
            if (!Insert(Tree<E>::root, arr[i])) 
                throw Error(100, "Duplicated element in array");
            i++;
        } 
    }

    bool Insert(TreeNode<E> * &p, const E& e) override {
        if (p == nullptr) {
            p = new TreeNode<E>{e, nullptr, nullptr};
            return 1;
        }
        else if (e == p->elem)
            return 0;
        else if (e < p->elem)
            return Insert(p->lchild, e);
        else
            return Insert(p->rchild, e);
    }

    bool Delete(const E& e) {
        TreeNode<E> * p = Search(e);
        if (p == nullptr) return 0;
        Delete(p);
        return 1;
    }

    TreeNode<E> *Search(E key) {
        TreeNode<E> *T = Tree<E>::root;
        while (T != nullptr && key != T->elem)
        {
            if (key < T->elem) T = T->lchild;
            else T = T->rchild;
        }
        return T;
    }

    void InOrderShow(void Visit(const E& e)) const override {
        cout << "\nInOrder: " << endl;;
        Tree<E>::InOrderShow(Visit);
        cout << endl;
    }
};

#endif