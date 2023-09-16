#ifndef __ADJ_LIST_NETWORK_H__
#define __ADJ_LIST_NETWORK_H__
#include "KruskalEdge.h"						// 辅助软件包

#include<queue>
//#include "AdjListUndirNetworkEdge.h"		// 网络邻接表的边结点类
#include "AdjListUndirNetworkVex.h"			// 网络邻接表的顶点结点类
#include "equivalence.h"
#include "MineHeap.h"
// 无向网的邻接表类
template <class ElemType, class WeightType>
class AdjListUndirNetwork
{
protected:
// 邻接表的数据成员:
	int vexNum, vexMaxNum, edgeNum;					// 顶点数目、允许的顶点最大数目和边数
	AdjListNetworkVex<ElemType, WeightType> *vexTable;	// 顶点表
	mutable Status *tag;					        // 标志数组				
	WeightType infinity;							// 无穷大的值

	int helpGetBranch_viaBFS(int v) const;
	void BFS(const AdjListUndirNetwork<ElemType, WeightType> &network, int v, void (*Visit)(const ElemType &)) const;
	void DFS(const AdjListUndirNetwork<ElemType, WeightType> &network, int v, void (*Visit)(const ElemType &)) const;
	void RefreshTag() const;

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjListUndirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// ok 以数组es[]为顶点数据,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,
        // infinit表示无穷大,边数为0构造无向网
	AdjListUndirNetwork(int vertexMaxNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// ok 构造允许的顶点最大数目为vertexMaxNum,infinit表示无穷大,边数为0的无向网
	~AdjListUndirNetwork();						 // ok 析构函数

	void Clear();			                     // ok 清空无向网			 
	
	bool IsEmpty();                              // ok 判断无向网是否为空 
	int GetOrder(ElemType &d) const;             // ok 求顶点的序号
	int GetDegreeofVex(const int& v) const;		 // new 根据顶点下标求其度数
	Status GetElem(int v, ElemType &d) const;    // ok 求顶点的元素值	
	Status SetElem(int v, const ElemType &d);    // ok 设置顶点的元素值
	WeightType GetInfinity() const;				 // ok 取无穷大的值			 
	int GetVexNum() const;						 // ok 求无向网的顶点个数			 
	int GetedgeNum() const;						 // ok 求无向网的边数个数
	int GetBranchNum() const;					 // new 求无向网连通分支数
	int FirstAdjVex(int v) const;				 // ok 求无向网中顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		 // ok 求无向网中顶点v1的相对于v2的下一个邻接点			 
	
	void InsertVex(const ElemType &d);			 // ok 插入元素值为d的顶点		 
	void InsertEdge(int v1, int v2, WeightType w);// ok 插入从顶点为v1到v2、权为w的边			 
	void DeleteVex(const ElemType &d);			 // ok 删除元素值为d的顶点
	void DeleteEdge(int v1, int v2);			 // ok 删除从顶点为v1到v2的边
	WeightType GetWeight(int v1, int v2) const;	 // ok 求从顶点为v1到v2的边的权值
	void SetWeight(int v1, int v2, WeightType w);// ok 设置从顶点为v1到v2的边的权值
	Status GetTag(int v) const;				     // ok 求顶点v的标志		 
	void SetTag(int v, Status tag) const;	     // ok 设置顶点v的标志为tag	 
	
	AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy);	// 复制构造函数
	AdjListUndirNetwork<ElemType, WeightType> &operator =
		(const AdjListUndirNetwork<ElemType, WeightType> &copy); // 重载赋值运算符 
    void Display();	// 显示无向网邻接表 

	/***********************/
	int GetDegree(const int &v) const;			// 求顶点的度
	void Kruskal() const;						// Kruskal算法求最小生成树
	void Prim(int u0) const;							// Prim算法求最小生成树
};
template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::helpGetBranch_viaBFS(int v) const
{// 返回v所在的连通分支里的顶点个数，通过vexs传回分支中所有顶点的下标组成的数组
	queue<int> q;
	int u, w, count = 0;
	SetTag(v, VISITED);
	//GetElem(v, e);
	q.push(v);
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		count++;
		for (w = FirstAdjVex(u); w != -1; w = NextAdjVex(u,w))
			if (GetTag(w) == UNVISITED)
			{
				SetTag(w, VISITED);
				//GetElem(w, e);
				q.push(w);
			}
	}
	return count;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::BFS(const AdjListUndirNetwork<ElemType, WeightType> &network, int v, void (*Visit)(const ElemType &)) const
{
	queue<int> q;
	int u, w;
	ElemType e;
	network.SetTag(v, VISITED);
	network.GetElem(v, e);
	(*Visit)(e);
	q.push(v);
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		for (w = network.FirstAdjVex(u); w != -1; w = network.NextAdjVex(u,w))
			if (network.GetTag(w) == UNVISITED)
			{
				network.SetTag(w, VISITED);
				network.GetElem(w, e);
				(*Visit)(e);
				q.push(w);
			}
	}
}
template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::RefreshTag() const
{
	for (int i = 0; i < vexNum; i++)
	{
		tag[i] = UNVISITED;
	}
}

// 无向网的邻接表类的实现部分
template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(ElemType es[],
       int vertexNum, int vertexMaxNum, WeightType infinit)
// 操作结果：构造顶点数据为es[],顶点数为numVex,顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
    	throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;			
	vexMaxNum = vertexMaxNum; 
	edgeNum = 0;
	infinity = infinit;
	
	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetworkVex<ElemType, WeightType>[vexMaxNum];
 
	for (int v = 0; v < vexNum; v++)  {
		tag[v] = UNVISITED;
		vexTable[v].data = es[v];
		vexTable[v].firstEdge = NULL;
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(int vertexMaxNum, WeightType infinit)
// 操作结果：构造顶点最大数目为vertexMaxNum,infinit表示无穷大的空无向网
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;			
	vexMaxNum = vertexMaxNum;
	edgeNum = 0;
	infinity = infinit;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetworkVex<ElemType, WeightType>[vexMaxNum];
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::~AdjListUndirNetwork()
// 操作结果：释放邻接表无向网所占用空间
{
    Clear();                                // 释放边结点
	delete []tag;							// 释放标志
	delete []vexTable;						// 释放邻接表
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::Clear()
// 操作结果：释放所有的边结点，并把无向网的顶点数和边数设置为0.			 
{
	AdjListNetworkEdge<WeightType> *p;
	for (int v = 0; v < vexNum; v++)	{	// 释放边结点
	    p = vexTable[v].firstEdge;
	    while (p != NULL) {
			vexTable[v].firstEdge = p->nextEdge;
			delete p;
			p = vexTable[v].firstEdge;
        }
	}
    vexNum = 0;
	edgeNum = 0;	
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::IsEmpty()
// 操作结果：如果无向网为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetOrder(ElemType &d) const
// 操作结果：求顶点d的序号.顶点的序号从0开始，图中不存在顶点d时返回-1. 
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
           break;
           
	if (v < 0 || v >= vexNum)
		return -1;	// 顶点d不存在,返回-1
	else
		return v;	// 顶点d不存在,返回它的序号 
}
template <class ElemType,class WeightType>
int AdjListUndirNetwork<ElemType,WeightType>::GetDegreeofVex(const int &v) const
// 操作结果：求序号为v的度数, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回一个整数
{
	if (v< 0 || v>=vexNum)
	{
		throw Error("Invalid input of v");
	}
	int degree = 0;
	AdjListNetworkEdge<WeightType> *p;
	p = vexTable[v].firstEdge;
	while (p != NULL)
	{
		p = p->nextEdge;
		degree++;
	}
	return degree;
}

template <class ElemType, class WeightType>
Status AdjListUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &d) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
//	通过d取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;			// 元素不存在
	else	{
		d = vexTable[v].data;		// 将顶点v的元素值赋给d
		return ENTRY_FOUND;			// 元素存在
	}
}	

template <class ElemType, class WeightType>
Status AdjListUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &d)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;			// 位置错
	else	{
		vexTable[v].data = d;		// 顶点元素
		return SUCCESS;				// 成功
	}
}

template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大的值 
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetedgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}


template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetBranchNum() const // new 求无向网连通分支数
{
	RefreshTag();
	int numofBranch = 0;
	for (int i = 0; i < vexNum; i++)
	{
		if (GetTag(i) == UNVISITED)
		{
			helpGetBranch_viaBFS(i);
			numofBranch++;
		}
	}

	return numofBranch;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");// 抛出异常

	if (vexTable[v].firstEdge == NULL)
	   return -1;              // 不存在邻接点
	else
	   return vexTable[v].firstEdge->adjVex;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");// 抛出异常
	AdjListNetworkEdge<WeightType> *p;
	p = vexTable[v1].firstEdge;
	while (p != NULL && p->adjVex != v2)	// 找到V2结点
	    p = p->nextEdge;

	if (p == NULL || p->nextEdge == NULL)
		return -1;                   // 不存在相对V2的下一个邻接点
	else
		return p->nextEdge->adjVex;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::InsertVex(const ElemType &d)
// 操作结果：在顶点表的表尾插入元素值为d的顶点。			 
{
	if (vexNum == vexMaxNum)
       throw Error("图的顶点数已经达到允许的最大数!");	// 抛出异常

	vexTable[vexNum].data = d;
	vexTable[vexNum].firstEdge = NULL;
	tag[vexNum] = UNVISITED;
    vexNum++;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");// 抛出异常
	if (w == infinity)
       throw Error("w不能为无空大!");// 抛出异常
	{
		AdjListNetworkEdge<WeightType> *p;
		p = vexTable[v1].firstEdge;
		while (p != NULL && p->adjVex != v2)
			p = p->nextEdge;
		if (p != NULL && p->weight < infinity)	//表示边已存在,则修改其权重
		{
			p->weight = w;
			AdjListNetworkEdge<WeightType> *q;
			q = vexTable[v2].firstEdge;
			while (q != NULL && q->adjVex != v1)
				q = q->nextEdge;
			q->weight = w;
			return;
		}
	}

	AdjListNetworkEdge<WeightType> *p, *q;
	p = vexTable[v1].firstEdge;		// 头插法
    vexTable[v1].firstEdge = new AdjListNetworkEdge<WeightType>(v2, w, p);
	q = vexTable[v2].firstEdge;		// 头插法
    vexTable[v2].firstEdge = new AdjListNetworkEdge<WeightType>(v1, w, q);
	edgeNum++;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &d)
// 操作结果：删除元素值为d的顶点			 
{
    int v;
    AdjListNetworkEdge<WeightType> *p;
    for (v = 0; v < vexNum; v++)
       if	(vexTable[v].data == d)
           break;
	if (v == vexNum)
       throw Error("图中不存在要删除的顶点!");		// 抛出异常

    for (int u = 0; u < vexNum; u++)           // 删除与V关联的边
       if (u != v)
		   DeleteEdge(u, v); // 与edgeNum个数相关的维护在此函数中
	vexNum--;
	// 将数组尾结点搬到被删结点的空位
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstEdge = vexTable[vexNum].firstEdge;
    vexTable[vexNum].firstEdge = NULL;
    tag[v] = tag[vexNum];

    for (int u = 0; u < vexNum; u++)         // 维护与原数组尾结点相邻的其他节点中保存的结点下标信息
       if (u != v) {
	      p = vexTable[u].firstEdge;
	      while (p != NULL) {
             if (p->adjVex == vexNum)
                p->adjVex = v;
             p = p->nextEdge;
          }
       }   
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
       Error("v1不能等于v2!");		// 抛出异常
	int flag = 0;
	// 删除v1邻接表中关联v1、v2的边
	{
		AdjListNetworkEdge<WeightType> *p, *q;
		p = vexTable[v1].firstEdge;
		while (p != NULL && p->adjVex != v2) {
			q = p;
			p = p->nextEdge;
		}
		if (p != NULL) {
			if (vexTable[v1].firstEdge == p)
				vexTable[v1].firstEdge = p->nextEdge;
			else
				q->nextEdge = p->nextEdge;
			delete p;
			flag++;
		}
	}
	// 删除v2邻接表中关联v1、v2的边
	{
		AdjListNetworkEdge<WeightType> *p, *q;
		p = vexTable[v2].firstEdge;
		while (p != NULL && p->adjVex != v1) {
			q = p;
			p = p->nextEdge;
		}
		if (p != NULL) {
			if (vexTable[v2].firstEdge == p)
				vexTable[v2].firstEdge = p->nextEdge;
			else
				q->nextEdge = p->nextEdge;
			delete p;
			flag++;
		}
	}
	if (flag >= 1)
		edgeNum--;
}

template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常

	AdjListNetworkEdge<WeightType> *p;
	p = vexTable[v1].firstEdge;
	while (p != NULL && p->adjVex != v2) 
       p = p->nextEdge;
    if (p != NULL)
	   return p->weight;			// 返回权值
	else
	   return infinity;				// 返回权值为infinity，表示边不存在
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// 操作结果：设置顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");        // 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	    // 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");    // 抛出异常
	if (w == infinity)
       throw Error("w不能为无空大!");   // 抛出异常
	{
		AdjListNetworkEdge<WeightType> *p;
		p = vexTable[v1].firstEdge;
		while (p != NULL && p->adjVex != v2)
		p = p->nextEdge;
		if (p != NULL)
		p->weight = w;		            // 修改v1邻接表中<v1,v2>权值
	}
	{
		AdjListNetworkEdge<WeightType> *p;
		p = vexTable[v2].firstEdge;
		while (p != NULL && p->adjVex != v1)
		p = p->nextEdge;
		if (p != NULL)
		p->weight = w;		            // 修改v2邻接表中<v1,v2>权值
	}
}

template <class ElemType, class WeightType>
Status AdjListUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");		// 抛出异常
	return tag[v];
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy)
// 操作结果：由无向网的邻接矩阵copy构造新无向网的邻接矩阵copy――复制构造函数
{
	AdjListNetworkEdge<WeightType> *p, *q;
	infinity =copy.infinity;
	vexNum = copy.vexNum;
	vexMaxNum = copy.vexMaxNum;	
	edgeNum = copy.edgeNum;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetworkVex<ElemType, WeightType>[vexMaxNum];
	for (int v = 0; v < vexNum; v++)	{
		tag[v] = copy.tag[v];
		vexTable[v].data = copy.vexTable[v].data;
		vexTable[v].firstEdge = NULL;
		p = copy.vexTable[v].firstEdge;
		while (p != NULL) 
           if (vexTable[v].firstEdge == NULL) {
              vexTable[v].firstEdge = new AdjListNetworkEdge<WeightType>(p->adjVex, p->weigth);	
              q = vexTable[v].firstEdge;
              p = p->nextEdge;
           }
           else {   
              q->nextEdge = new AdjListNetworkEdge<WeightType>(p->adjVex, p->weigth);	
              q = q->nextEdge;
              p = p->nextEdge;
           }   
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType> &AdjListUndirNetwork<ElemType, WeightType>::operator =(const AdjListUndirNetwork<ElemType, WeightType> &copy)
// 操作结果：将无向网的邻接矩阵copy赋值给当前无向网的邻接矩阵――赋值语句重载
{
	if (&copy != this)
	{
        Clear();                                    // 释放当前无向网边结点
	    delete []tag;								// 释放当前无向网标志数组 
	    delete []vexTable;							// 释放当前无向网顶点表 

	    AdjListNetworkEdge<WeightType> *p, *q;
	    infinity =copy.infinity;
	    vexNum = copy.vexNum;
	    vexMaxNum = copy.vexMaxNum;	
	    edgeNum = copy.edgeNum;

	    tag = new Status[vexMaxNum];
	    vexTable = new AdjListNetworkVex<ElemType, WeightType>[vexMaxNum];
	    for (int v = 0; v < vexNum; v++)	{
		   tag[v] = copy.tag[v];
		   vexTable[v].data = copy.vexTable[v].data;
		   vexTable[v].firstEdge = NULL;
		   p = copy.vexTable[v].firstEdge;
		   while (p != NULL) 
               if (vexTable[v].firstEdge == NULL) {
                  vexTable[v].firstEdge = new AdjListNetworkEdge<WeightType>(p->adjVex, p->weigth);	
                  q = vexTable[v].firstEdge;
                  p = p->nextEdge;
               }
               else {   
                  q->nextEdge = new AdjListNetworkEdge<WeightType>(p->adjVex, p->weigth);	
                  q = q->nextEdge;
                  p = p->nextEdge;
               }   
	   }
    }
	return *this;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::Display()
// 操作结果: 显示邻接矩阵无向网
{
	AdjListNetworkEdge<WeightType> *p;
    cout << "无向网共有" << vexNum << "个顶点，" << edgeNum << "条边。" << endl; 
	for (int v = 0; v < vexNum; v++)	{	// 显示第v个邻接链表
		cout << v << ":\t" << vexTable[v].data;				// 显示顶点号
	    p = vexTable[v].firstEdge;
	    while (p != NULL) {
        	cout << "-->(" << p->adjVex << "," << p->weight << ")";
            p = p->nextEdge; 
		}
		cout << endl; 
	}
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetDegree(const int &v) const
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");// 抛出异常
	AdjListNetworkEdge<WeightType> *p;
	int degree = 0;
	for (p = vexTable[v].firstEdge; p!=NULL; p = p->nextEdge)
		degree++;
	return degree;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::Kruskal() const // Kruskal算法求最小生成树
{
	int count;
	KruskalEdge<ElemType, WeightType> KEdge;
	MinHeap<KruskalEdge<ElemType,WeightType>> ha(edgeNum);
	ElemType *kVex, v1, v2;
	kVex = new ElemType[vexNum];
	for (int i = 0; i < vexNum; i++)
		GetElem(i, kVex[i]);
	Equivalence<ElemType> f(kVex, vexNum);
	for (int v = 0; v < vexNum; v++)
		for (int u = FirstAdjVex(v); u > -1; u = NextAdjVex(v,u))
		{
			if (v < u)	// 防止重复
			{
				GetElem(v, v1);
				GetElem(u, v2);
				KEdge.vertex1 = v1;
				KEdge.vertex2 = v2;
				KEdge.weight = GetWeight(v, u);
				ha.Insert(KEdge);
			}
		}
	count = 0;
	while (count < vexNum - 1)
	{
		ha.DeleteTop(KEdge);
		v1 = KEdge.vertex1;
		v2 = KEdge.vertex2;
		if (f.Differ(v1,v2))
		{
			cout << "(" << v1 << "," << v2 << "," << KEdge.weight << ")" << endl;
			f.Union(v1, v2);
			count++;
		}
		
	}
	
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::Prim(int u0) const
{
	WeightType min;
	ElemType v1, v2;
	CloseArcType<ElemType, WeightType> *closeedges;
	if (u0 < 0 || u0 >= vexNum)
	{
		cerr << "顶点u0不存在" << endl;
		return;
	}
	int u, v, k;
	closeedges = new CloseArcType<ElemType, WeightType>[vexNum];
	for (int v = 0; v < vexNum; v++)
	{
		closeedges[v].nearvertex = u0;
		closeedges[v].lowweight = GetWeight(u0, v);
	}
	closeedges[u0].nearvertex = -1;
	closeedges[u0].lowweight = 0;
	for ( k = 1; k < vexNum; k++)
	{
		min = infinity;
		v = u0;
		for (u = 0; u < vexNum; u++)
			if (closeedges[u].lowweight != 0 && closeedges[u].lowweight < min)
			{
				v = u;
				min = closeedges[u].lowweight;
			}
		if (v != u0)
		{
			GetElem(closeedges[v].nearvertex, v1);
			GetElem(v, v2);
			cout << "(" << v1 << "," << v2 << "," << min << ")" << endl;
			closeedges[v].lowweight = 0;
			for (u = FirstAdjVex(v); u != -1;u = NextAdjVex(v,u))
				if(closeedges[u].lowweight != 0 &&
					(GetWeight(v,u) < closeedges[u].lowweight))
				{
					closeedges[u].lowweight = GetWeight(v, u);
					closeedges[u].nearvertex = v;
				}
		}
		
	}
	delete[] closeedges;
}

#endif