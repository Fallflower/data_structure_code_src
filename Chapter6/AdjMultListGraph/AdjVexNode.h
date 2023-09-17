/*
 * @Author: Metaphor
 */
#ifndef __ADJVEXNODE_H_
#define __ADJVEXNODE_H_

#include "AdjEdgeNode.h"
using namespace std;
//#pragma execution_character_set("utf-8")

struct AdjVexNode
{
// 邻接多重表顶点结点
    CountryNode country;        // 数据成员
    AdjEdgeNode *firstEdge;


    AdjVexNode() : country(CountryNode()), firstEdge(NULL){}
    AdjVexNode(CountryNode c, AdjEdgeNode *e = NULL) : country(c), firstEdge(e){}
    AdjVexNode(string Name, int p, AdjEdgeNode *e = NULL) : country(CountryNode(Name, p)), firstEdge(e){}
    AdjVexNode(const AdjVexNode &copy);
    ~AdjVexNode();

    AdjEdgeNode *GetFirstEdge();

    AdjVexNode &operator=(const AdjVexNode &copy);

};


AdjVexNode::AdjVexNode(const AdjVexNode &copy)
{
    country = copy.country;
    firstEdge = copy.firstEdge;
}

AdjVexNode &AdjVexNode::operator=(const AdjVexNode &copy) = default;

AdjVexNode::~AdjVexNode()
{
    if (firstEdge != NULL)
        delete firstEdge;
}

AdjEdgeNode *AdjVexNode::GetFirstEdge()
{
    return firstEdge;
}

#endif