#ifndef __BINARY_TREE_NODE__
#define __BINARY_TREE_NODE__


template<class Etype>
struct BinaryTreeNode
{
    Etype elem;
    BinaryTreeNode<Etype> *lchild, *rchild;

    BinaryTreeNode():lchild(nullptr), rchild(nullptr){}
};

#endif