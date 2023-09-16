/*
 * @Author: Metaphor
 */
/*
 * @Author: Metaphor
 */

#ifndef __ADJ_LIST_NETWORK_EDGE_H__
#define __ADJ_LIST_NetWORK_EDGE_H__
#include "Assistance.h"
// 邻接表网边数据类
template <class WeightType>
class AdjListNetworkEdge
{
	public:
	// 数据成员:
	int adjVex;								  // 弧头顶点序号
	WeightType weight;						  // 边的权值
	AdjListNetworkEdge<WeightType> *nextEdge; // 下一条边结点的指针
											  // 构造函数:
	AdjListNetworkEdge();					  // 无参数的构造函数
	AdjListNetworkEdge(int v, WeightType w, AdjListNetworkEdge<WeightType> *next = NULL);
	// 构造邻接点为v，权为w的邻接边
};

// 邻接表网边数据类的实现部分
template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge()
// 操作结果：构造一个空邻接表边结点边――无参构造函数
{
	adjVex = -1;
}

template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge(int v, WeightType w, AdjListNetworkEdge<WeightType> *next)
// 操作结果：构造邻接点序号为v，边的权为w，下一条边结点的指针为next的邻接边
{
	adjVex = v;
	weight = w;
	nextEdge = next;
}

#endif