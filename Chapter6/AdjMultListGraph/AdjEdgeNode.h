/*
 * @Author: Metaphor
 */

#ifndef __ADJEDGENODE_H_
#define __ADJEDGENODE_H_

#include "CountryNode.h"
using namespace std;

//#pragma execution_character_set("utf-8")

struct AdjEdgeNode
{
//
    bool tag;               // 标记域，标记该边是否被处理或被搜索过
    double cost;               // 修路成本
    int distance;           // 村庄直线距离
    int adjvex1, adjvex2;               // 存储改变相连顶点的序号
    AdjEdgeNode *nextEdge1, *nextEdge2; //分别保存两个顶点除本边之外的相连的下一条边

//
    AdjEdgeNode(bool Tag = false, double Cost = 0.0,int Distance = 0, int v1 = 0, int v2 = 0, AdjEdgeNode *e1 = NULL, AdjEdgeNode *e2 = NULL);
    AdjEdgeNode(int v1, int v2, double Cost,int Distance, AdjEdgeNode *e1 = NULL, AdjEdgeNode *e2 = NULL);
    AdjEdgeNode(const AdjEdgeNode &copy);
    ~AdjEdgeNode();


    AdjEdgeNode &operator=(const AdjEdgeNode &copy);
};

AdjEdgeNode::AdjEdgeNode(bool Tag, double Cost,int Distance, int v1, int v2, AdjEdgeNode *e1, AdjEdgeNode *e2)
{
    tag = Tag;
    cost = Cost;
    distance = Distance;
    adjvex1 = v1;
    adjvex2 = v2;
    nextEdge1 = e1;
    nextEdge2 = e2;
}

AdjEdgeNode::AdjEdgeNode(int v1, int v2, double Cost, int Distance, AdjEdgeNode *e1, AdjEdgeNode *e2)
{
    tag = false;
    cost = Cost;
    distance = Distance;
    adjvex1 = v1;
    adjvex2 = v2;
    nextEdge1 = e1;
    nextEdge2 = e2;
}

AdjEdgeNode::AdjEdgeNode(const AdjEdgeNode &copy)
{
    tag = copy.tag;
    cost = copy.cost;
    distance = copy.distance;
    adjvex1 = copy.adjvex1;
    adjvex2 = copy.adjvex2;
    nextEdge1 = copy.nextEdge1;
    nextEdge2 = copy.nextEdge2;
}

AdjEdgeNode::~AdjEdgeNode()
{
    if(nextEdge1 != NULL)
        delete[] nextEdge1;
    if(nextEdge2 != NULL)
        delete[] nextEdge2;
}
AdjEdgeNode &AdjEdgeNode::operator=(const AdjEdgeNode &copy) = default;

#endif