#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__
// #include "TreeNode.h"
#include "../../Chapter3/CirQueue/CirQueue.h"
#include "Tree.h"


template<typename E>
class BSTree : public Tree<E>
{
private:

    TreeNode<E>* __get_most_left_in_rtree(TreeNode<E>* r) {
        if (r->rchild == nullptr) return nullptr;
        TreeNode<E>* p = r->rchild;
        while (p->lchild != nullptr)
        {
            p = p->lchild;
        }
        return p; 
    }
    
    TreeNode<E>* __get_most_right_in_ltree(TreeNode<E>* r) {
        if (r->lchild == nullptr) return nullptr;
        TreeNode<E>* p = r->lchild;
        while (p->rchild != nullptr)
        {
            p = p->rchild;
        }
        return p; 
    }

    TreeNode<E> * parent(TreeNode<E> *p) {
        CirQueue<TreeNode<E>*> queue;
        queue.EnCirQueue(Tree<E>::root);
        while (!queue.isEmpty())
        {
            TreeNode<E> *q;
            queue.DeCirQueue(q);
            if (q->lchild == p || q->rchild == p) return q;
            queue.EnCirQueue(q->lchild);
            queue.EnCirQueue(q->rchild);
        }
        return NULL;
    }

public:
    BSTree(E *arr, int length) {
        int i = 0;
        while (i < length && Insert(Tree<E>::root, arr[i]))
            i++;
        
    }

    bool Insert(TreeNode<E> * &p, const E& e) override {
        if (p == NULL) {
            p = new TreeNode<E>{e, NULL, NULL};
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
        TreeNode<E> * p = Search(e), pp;
        pp = parent(p);
        if (p->lchild == NULL && p->rchild == NULL)
        {
            if (pp->lchild == p) pp->lchild = NULL;
            else if (pp->rchild == p) pp->rchild = NULL;
            else Tree<E>::root = NULL;
            delete p;
        } 
        else if (p->lchild == NULL) { // 找右子树中最左下的来替代

        }
        else if (p->rchild == NULL) { // 找左子树中最右下的来替代

        }
        else { // 找中序前驱或后继

        }
    }

    TreeNode<E> *Search(E key) {
        TreeNode<E> *T = Tree<E>::root;
        while (T != NULL && key != T->elem)
        {
            if (key < T->elem) T = T->lchild;
            else T = T->rchild;
        }
        return T;
    }
};

#endif