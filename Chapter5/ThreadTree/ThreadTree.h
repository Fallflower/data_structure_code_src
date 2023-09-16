#ifndef __THREAD_TREE_H__
#define __THREAD_TREE_H__
#include "../../Chapter3/CirQueue/CirQueue.h"
#include "../../Chapter3/Stack/Stack.h"

template<typename E>
struct ThreadNode
{
    E data;
    bool ltag, rtag;
    ThreadNode *lchild, *rchild;

    ThreadNode(const E& d, ThreadNode<E> *lc, ThreadNode<E> *rc) :ltag(0), rtag(0) {
        data = d;
        lchild = lc;
        rchild = rc;
    }
};

template<typename E>
class ThreadTree
{
private:
    ThreadNode<E> *root;

    //清空线索
    void ClearThread(ThreadNode<E> *r) {
        if (r != NULL)
        {
            if (r->ltag == 1)
                {r->lchild = NULL; r->ltag = 0;}
            else 
                ClearThread(r->lchild);

            if (r->rtag == 1)
                {r->rchild = NULL; r->rtag = 0;}
            else
                ClearThread(r->rchild);
        }
    }

    // 先序遍历二叉树，同时构造先序线索二叉树
    void PreThread(ThreadNode<E> *r, ThreadNode<E> *&pre) {
        if (r != NULL) {
            if (r->lchild == NULL) {
                r->lchild = pre;
                r->ltag = 1;
            }
            if (pre != NULL && pre->rchild == NULL) {
                pre->rchild = r;
                pre->rtag = 1;
            }
            pre = r;
            if (r->ltag == 0) // 是左孩子而不是前驱
                PreThread(r->lchild, pre);
            PreThread(r->rchild, pre);
        }
    }

    // 中序遍历二叉树，同时构造中序线索二叉树
    void InThread(ThreadNode<E> *r ,ThreadNode<E> *&pre) {
        if (r != NULL) {
            InThread(r->lchild, pre);
            if (r->lchild == NULL) {
                r->lchild = pre;
                r->ltag = 1;
            }
            if (pre !=NULL && pre->rchild == NULL) {
                pre->rchild = r;
                pre->rtag = 1;
            }
            pre = r;
            InThread(r->rchild, pre);
        }
    }

    void InOrderVisit(ThreadNode<E> *r, void Visit(const E& e)) {
        if (r != NULL) {
            if (!r->ltag) InOrderVisit(r->lchild, Visit);
            Visit(r->data);
            if (!r->rtag) InOrderVisit(r->rchild, Visit);
        }
    }

    ThreadNode<E>* __init_with_pre_in__(E pre[], int preStart, int preEnd, E in[], int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) return NULL;
        ThreadNode<E> *sub_root;
        sub_root = new ThreadNode<E>{pre[preStart], NULL, NULL};

        for (int i = inStart; i <= inEnd; i++)
        {
            if (in[i] == pre[preStart]) {
                sub_root->lchild = __init_with_pre_in__(pre, preStart+1, preStart+i-inStart, in, inStart, i - 1);
                sub_root->rchild = __init_with_pre_in__(pre, preStart+i-inStart+1,preEnd, in, i + 1, inEnd);
            }
        }
        
        return sub_root;
    }

    void Destroy(ThreadNode<E> *r) {
        if (r != NULL) {
            Destroy(r->lchild);
            Destroy(r->rchild);
            delete r;
        }
    }

public:
    ThreadTree(E pre[], E in[], int length) {
        root = __init_with_pre_in__(pre, 0, length - 1, in, 0, length - 1);
    }
    ~ThreadTree() {
        Destroy(root);
    }
    // 先序线索化
    void CreatePreThread() {
        ClearThread(root);
        ThreadNode<E> *pre = NULL;
        PreThread(root, pre);
        if (pre->rchild == NULL)
            pre->rtag = 1;
    }

    // 中序线索化
    void CreateInThread() {
        ClearThread(root);
        ThreadNode<E> *pre = NULL;
        InThread(root, pre);
        if (pre->rchild == NULL)
            pre->rtag = 1;
    }



    void InOrderVisit(void Visit(const E& e)) {
        if (root != NULL)
            InOrderVisit(root, Visit);
    }
};
#endif
