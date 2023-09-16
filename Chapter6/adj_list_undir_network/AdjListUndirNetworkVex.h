/*
 * @Author: Metaphor
 */
/*
 * @Author: Metaphor
 */
#ifndef __ADJ_LIST_NETWORK_VEX_H__
#define __ADJ_LIST_NETWORK_VEX_H__

#include "AdjListUndirNetworkEdge.h"

// 邻接表图顶点结点类
template <class ElemType, class WeightType>
struct AdjListNetworkVex
{
// 数据成员:
	ElemType data;						// 数据元素值
	AdjListNetworkEdge<WeightType> *firstEdge;
		// 指向邻接链表边结点的指针

// 构造函数:
	AdjListNetworkVex();				// 无参数的构造函数
	AdjListNetworkVex(ElemType val, 
		AdjListNetworkEdge<WeightType> *adj = NULL);
		// 有参数的构造函数
};

// 邻接表图顶点结点类的实现部分
template <class ElemType, class WeightType>
AdjListNetworkVex<ElemType, WeightType>::AdjListNetworkVex()
// 操作结果：构造一个空顶点结点――无参构造函数
{
	firstEdge = NULL;	
}

template <class ElemType, class WeightType>
AdjListNetworkVex<ElemType, WeightType>::AdjListNetworkVex(ElemType  val, 
	AdjListNetworkEdge<WeightType> *adj)
// 操作结果：构造数据为val,边为eg的顶点
{
	data = val;
	firstEdge = adj;
}

#endif
