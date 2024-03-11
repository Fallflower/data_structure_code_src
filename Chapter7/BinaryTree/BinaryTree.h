#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include "BinaryTreeNode.h"
#include<string>
#include<iostream>
using namespace std;

template<class Etype>
class BinaryTree
{
private:
    BinaryTreeNode<Etype> *root;

    void Destroy(BinaryTreeNode<Etype> *& p) {
        if (p == nullptr) return;
        Destroy(p->lchild);
        Destroy(p->rchild);
        delete p;
    }

    BinaryTreeNode<Etype>* init_with_in_post(Etype in[], int is, int ie, Etype post[], int ps, int pe) {
        if (ie < is) return nullptr;
        BinaryTreeNode<Etype>* p = new BinaryTreeNode<Etype>;
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

    BinaryTreeNode<Etype>* init_with_in_pre(Etype in[], int is, int ie, Etype pre[], int ps, int pe) {
        if (ie < is) return nullptr;
        BinaryTreeNode<Etype>* p = new BinaryTreeNode<Etype>;
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

    void InOrderVisit(BinaryTreeNode<Etype> *p, void Visit(const Etype& e)) const {
        if (p == nullptr) return;
        InOrderVisit(p->lchild, Visit);
        Visit(p->elem);
        InOrderVisit(p->rchild, Visit);
    }

    void PreOrderVisit(BinaryTreeNode<Etype> *p, void Visit(const Etype& e)) const {
        if (p == nullptr) return;
        Visit(p->elem);
        PreOrderVisit(p->lchild, Visit);
        PreOrderVisit(p->rchild, Visit);
    }

    void PostOrderVisit(BinaryTreeNode<Etype> *p, void Visit(const Etype& e)) const {
        if (p == nullptr) return;
        PostOrderVisit(p->lchild, Visit);
        PostOrderVisit(p->rchild, Visit);
        Visit(p->elem);
    }

public:
    BinaryTree() :root(nullptr) {}
    BinaryTree(Etype in[], Etype pre[], int n, string mode) {
        if (mode == "pre")
            root = init_with_in_pre(in, 0, n-1, pre, 0, n-1);
        else if (mode == "post")
            root = init_with_in_post(in, 0, n-1, pre, 0, n-1);
        else
            cerr << "Unrecognized mode " << mode << endl;
    }

    ~BinaryTree() {
        Destroy(root);
    }

    void InOrderShow(void Visit(const Etype& e)) const {
        InOrderVisit(root, Visit);
    }

    void PreOrderShow(void Visit(const Etype& e)) const {
        PreOrderVisit(root, Visit);
    }

    void PostOrderShow(void Visit(const Etype& e)) const {
        PostOrderVisit(root, Visit);
    }
};

#endif