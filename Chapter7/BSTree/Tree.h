#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include "TreeNode.h"

template<class Etype>
class Tree
{
protected:
    TreeNode<Etype> *root;

    void Destroy(TreeNode<Etype> *& p) {
        if (p == nullptr) return;
        Destroy(p->lchild);
        Destroy(p->rchild);
        delete p;
    }

    TreeNode<Etype>* init_with_in_post(Etype in[], int is, int ie, Etype post[], int ps, int pe) {
        if (ie < is) return nullptr;
        TreeNode<Etype>* p = new TreeNode<Etype>;
        p->elem = post[pe];
        for (int i = is; i <= ie; i++)
        {
            if (in[i] == p->elem)
            {
                int pel = i - is, pol = ie - i;
                p->lchild = init_with_in_post(in, is, i-1, post, ps, ps+pel-1);
                p->rchild = init_with_in_post(in, i+1, ie, post, pe-pol, pe-1);
                break;
            } 
        }
        return p;
    }

    TreeNode<Etype>* init_with_in_pre(Etype in[], int is, int ie, Etype pre[], int ps, int pe) {
        if (ie < is) return nullptr;
        TreeNode<Etype>* p = new TreeNode<Etype>;
        p->elem = pre[ps];
        for (int i = is; i <= ie; i++)
        {
            if (in[i] == p->elem)
            {
                int pel = i - is, pol = ie - i;
                p->lchild = init_with_in_pre(in, is, i-1, pre, ps+1, ps+pel);
                p->rchild = init_with_in_pre(in, i+1, ie, pre, pe-pol+1, pe);
                break;
            } 
        }
        return p;
    }

    void InOrderVisit(TreeNode<Etype> *p, void Visit(const Etype& e)) const {
        if (p == nullptr) return;
        InOrderVisit(p->lchild, Visit);
        Visit(p->elem);
        InOrderVisit(p->rchild, Visit);
    }

    void PreOrderVisit(TreeNode<Etype> *p, void Visit(const Etype& e)) const {
        if (p == nullptr) return;
        Visit(p->elem);
        PreOrderVisit(p->lchild, Visit);
        PreOrderVisit(p->rchild, Visit);
    }

    void PostOrderVisit(TreeNode<Etype> *p, void Visit(const Etype& e)) const {
        if (p == nullptr) return;
        PostOrderVisit(p->lchild, Visit);
        PostOrderVisit(p->rchild, Visit);
        Visit(p->elem);
    }

public:
    Tree() :root(nullptr) {}
    Tree(Etype in[], Etype pre[], int n, string mode) {
        if (mode == "pre")
            root = init_with_in_pre(in, 0, n-1, pre, 0, n-1);
        else if (mode == "post")
            root = init_with_in_post(in, 0, n-1, pre, 0, n-1);
        else
            throw Error(404, string("Unrecognized mode: ")+mode);
    }

    virtual ~Tree() {
        Destroy(root);
    }

    virtual void InOrderShow(void Visit(const Etype& e)) const {
        InOrderVisit(root, Visit);
    }

    virtual void PreOrderShow(void Visit(const Etype& e)) const {
        PreOrderVisit(root, Visit);
    }

    virtual void PostOrderShow(void Visit(const Etype& e)) const {
        PostOrderVisit(root, Visit);
    }

    virtual bool Insert(TreeNode<Etype> *&p, const Etype& e) = 0;
};

#endif