#ifndef __BINARY_SEARCH_TREE_NODE__
#define __BINARY_SEARCH_TREE_NODE__
#include "../../Assistance.h"

template<typename E>
struct BSTreeNode
{
    E data;
    BSTreeNode *lchild, *rchild;

    BSTreeNode() :lchild(nullptr), rchild(nullptr)
};


#endif