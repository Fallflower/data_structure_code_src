#ifndef __BINARY_TREE_NODE__
#define __BINARY_TREE_NODE__
#include "../../Assistance.h"

template<class Etype>
struct TreeNode
{
    Etype elem;
    TreeNode<Etype> *lchild, *rchild;

    TreeNode():lchild(nullptr), rchild(nullptr){}
    TreeNode(Etype e, TreeNode<Etype> *l, TreeNode<Etype> *r):elem(e), lchild(l), rchild(r){}
    virtual ~TreeNode(){}

    virtual Etype getElem() const {return elem;}
};

#endif