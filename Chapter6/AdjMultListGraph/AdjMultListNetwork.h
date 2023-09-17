/*
 * @Author: Metaphor
 */
#ifndef __ADJMULTLISTNETWORK_H_
#define __ADJMULTLISTNETWORK_H_

#include "AdjVexNode.h"
#include <fstream>

//#pragma execution_character_set("utf-8")
#define DEFAULTSIZE 1000
#define DIS_INFINITY 65535
#define COST_INFINITY 99999.9

using namespace std;

class AdjMultListNetwork
{
private:
    AdjVexNode *vexTable;
    int vexNum;
    int vexMaxNum;
    int edgeNum;

protected:
//
    void Clear();   // 删除边
    bool IfValid(int v1, int v2) const;
    void HelpCreateInsert(int v1, int v2, const double &Cost, const int& Distance = DIS_INFINITY);

public:
//
    AdjMultListNetwork(int MaxNum = DEFAULTSIZE );
    AdjMultListNetwork(const string& filename);
    ~AdjMultListNetwork();

    bool IsEmpty() const;
    void display() const;

    void InsertEdge(int v1, int v2, const double &Cost, const int& Distance);
    void SetCost(int v1, int v2, const double &Cost);
    void SetDistance(int v1, int v2, const int &Distance);

    double GetCost(int v1, int v2) const;           // 求两村之间修路成本
    int GetDistance(int v1, int v2) const;          // 求两村距离
    int GetPopulation(int v1, int v2) const;        // 求两村人口总数
    int GetVexNum() const;                          // 求顶点数
    int GetIndex(string name) const;
    string GetName(int index) const;


    void DeleteEdge(int v1, int v2);
};


bool AdjMultListNetwork::IfValid(int v1, int v2) const
{
    if (v1 < 0 || v1 >=vexNum)
    {
        cerr << "Invalid input of v1" << endl;
        return false;
    }
    if (v2 < 0 || v2 >=vexNum)
    {
        cerr << "Invalid input of v2" << endl;
        return false;
    }
    if (v1 == v2)
    {
        cerr << "Error: v1 equals to v2" << endl;
        return false;
    }
    return true;
}

void AdjMultListNetwork::Clear()
{
    for (int i = 0; i < vexNum; i++)
    {
        AdjEdgeNode *p = vexTable[i].GetFirstEdge();
        if (p != NULL)
            delete[] p;
    }
}

void AdjMultListNetwork::HelpCreateInsert(int v1, int v2, const double &Cost, const int& Distance)
{
    AdjEdgeNode *p = vexTable[v1].GetFirstEdge();
    AdjEdgeNode *q = vexTable[v2].GetFirstEdge();
    vexTable[v1].firstEdge = vexTable[v2].firstEdge = new AdjEdgeNode(v1, v2, Cost, Distance, p, q);
    edgeNum++;
    //printf("\n已插入%d %d\n",v1,v2);
}

AdjMultListNetwork::AdjMultListNetwork(int MaxNum)
{
    vexMaxNum = MaxNum;
    vexTable = new AdjVexNode[vexMaxNum];
    vexNum = 0;
    edgeNum = 0;
}

AdjMultListNetwork::AdjMultListNetwork(const string& filename)
{
    ifstream infile;
    infile.open(filename);
    if(!infile) //如果失败，请尝试输入文件绝对路径
        cerr << "Open file: " << filename << " failed!" << endl;
    vexMaxNum = DEFAULTSIZE;
    vexTable = new AdjVexNode[vexMaxNum];
    infile >> vexNum;
    edgeNum = 0;
    // cout << vexNum << endl;
    for (int i = 0; i < vexNum; i++)
    {
        CountryNode p;
        infile >> p.name >> p.population;
        //cout << p << endl;
        vexTable[i] = AdjVexNode(p);
    }
    for (int i = 0; i < vexNum; i++)
        for (int j = 0; j < vexNum; j++)
        {// 读入成本矩阵
            double cost;infile >> cost;
            //cout << m << endl;
            if (i < j && cost < COST_INFINITY)
            {
                cost /= GetPopulation(i, j);    // 依据人口修真成本
                HelpCreateInsert(i,j,cost);
            }
        }
    for (int i = 0; i < vexNum; i++)
        for (int j = 0; j < vexNum; j++)
        {// 读入距离矩阵
            int m;infile >> m;
            //cout << m << endl;
            if (i < j && m < DIS_INFINITY)
                SetDistance(i,j,m);
        }
    infile.close();
    //cout << vexNum << endl;
}

AdjMultListNetwork::~AdjMultListNetwork()
{
    Clear();
    if(vexTable!=NULL)
        delete[] vexTable;
}

bool AdjMultListNetwork::IsEmpty() const
{
    return (vexNum == 0);
}

void AdjMultListNetwork::display() const
{//以邻接表的方式输出邻接多重表
    AdjEdgeNode *p;
    cout << "无向网共有" << vexNum << "个顶点，" << edgeNum << "条边。" << endl; 
	for (int v = 0; v < vexNum; v++)	{	// 显示第v个邻接链表
		cout << v << ":\t" << vexTable[v].country;				// 显示顶点号
	    p = vexTable[v].firstEdge;
	    while (p != NULL) {

            if (v == p->adjvex1)
            {
                cout << "-->(" << p->adjvex2 << "," << p->cost << "," << p->distance << ")";
                p = p->nextEdge1;
            }
            else
            {
                cout << "-->(" << p->adjvex1 << "," << p->cost << "," << p->distance << ")";
                p = p->nextEdge2;
            }
        }
		cout << endl; 
	}
}

void AdjMultListNetwork::InsertEdge(int v1, int v2, const double &Cost, const int& Distance)
{
    if(!IfValid(v1, v2)) return;
    AdjEdgeNode *p = vexTable[v1].GetFirstEdge();
    AdjEdgeNode *q = vexTable[v2].GetFirstEdge();
    AdjEdgeNode *t;
    if ((t = p) != NULL)
    {
        while(t->nextEdge1 != NULL || t->nextEdge2 != NULL)
        {
            if((t->adjvex1 == v1 && t->adjvex2 == v2)
            || (t->adjvex1 == v2 && t->adjvex2 == v1))
            {// 若边已存在则更新其数据（成本 与 距离）
                t->cost = Cost;
                t->distance = Distance;
                return;
            }
            if (v1 == t->adjvex1)
                t = t->nextEdge1;
            else
                t = t->nextEdge2;
            if (t == NULL)
                break;
        }
    }
    vexTable[v1].firstEdge = vexTable[v2].firstEdge = new AdjEdgeNode(v1, v2, Cost, Distance, p, q);
    edgeNum++;
}

void AdjMultListNetwork::SetCost(int v1, int v2, const double &Cost)
{
    if(!IfValid(v1, v2)) return;
    AdjEdgeNode *t = vexTable[v1].GetFirstEdge();
    //if ((t = vexTable[v1].GetFirstEdge()) != NULL)
    while(t!=NULL)
    // while(t->nextEdge1 != NULL || t->nextEdge2 != NULL)
    {
        if((t->adjvex1 == v1 && t->adjvex2 == v2)
        || (t->adjvex1 == v2 && t->adjvex2 == v1))
        {
            t->cost = Cost;
            return;
        }
        if (v1 == t->adjvex1)
            t = t->nextEdge1;
        else
            t = t->nextEdge2;
        // if (t == NULL)
        //     break;
    }
}

void AdjMultListNetwork::SetDistance(int v1, int v2, const int &Distance)
{
    if(!IfValid(v1, v2)) return;
    // if(v1+v2 == 1)
    //     printf("\nA and B: %d\n", Distance);
    AdjEdgeNode *t = vexTable[v1].GetFirstEdge();
    //if ((t = vexTable[v1].GetFirstEdge()) != NULL)
    while(t != NULL)
    //while(t->nextEdge1 != NULL || t->nextEdge2 != NULL)
    {
        // if(v1+v2 == 1)
        //         printf("\nA and B: %d %d\n", t->adjvex1,t->adjvex2);
        if((t->adjvex1 == v1 && t->adjvex2 == v2)
        || (t->adjvex1 == v2 && t->adjvex2 == v1))
        {
            // if(v1+v2 == 1)
            //     printf("\nA and B: %d\n", Distance);
            t->distance = Distance;
            return;
        }
        if (v1 == t->adjvex1)
            t = t->nextEdge1;
        else
            t = t->nextEdge2;
        // if (t == NULL)
        //     break;
    }
}


double AdjMultListNetwork::GetCost(int v1, int v2) const
{
    if(!IfValid(v1, v2)) return COST_INFINITY;
    AdjEdgeNode *p = vexTable[v1].GetFirstEdge();
    while (p != NULL && 
            !((p->adjvex1 == v1 && p->adjvex2 == v2)
            || (p->adjvex1 == v2 && p->adjvex2 == v1)))
    {
        if (v1 == p->adjvex1)
            p = p->nextEdge1;
        else
            p = p->nextEdge2;
    }
    if (p == NULL)
        return COST_INFINITY;
    return p->cost;
}

int AdjMultListNetwork::GetDistance(int v1, int v2) const
{
    if(!IfValid(v1, v2)) return DIS_INFINITY;
    AdjEdgeNode *p = vexTable[v1].GetFirstEdge();
    while (p != NULL && 
            !((p->adjvex1 == v1 && p->adjvex2 == v2)
            || (p->adjvex1 == v2 && p->adjvex2 == v1)))
    {
        if (v1 == p->adjvex1)
            p = p->nextEdge1;
        else
            p = p->nextEdge2;
    }
    if (p == NULL)
        return DIS_INFINITY;
    return p->distance;
}

int AdjMultListNetwork::GetPopulation(int v1, int v2) const
{
    if(!IfValid(v1, v2)) return 1;
    return vexTable[v1].country.population + vexTable[v2].country.population;
}

int AdjMultListNetwork::GetVexNum() const
{
    return vexNum;
}

void AdjMultListNetwork::DeleteEdge(int v1, int v2)
{
    if(!IfValid(v1, v2)) return;
    AdjEdgeNode *p = vexTable[v1].GetFirstEdge();
    while (p != NULL && 
            !((p->adjvex1 == v1 && p->adjvex2 == v2)
            || (p->adjvex1 == v2 && p->adjvex2 == v1)))
    {
        if (v1 == p->adjvex1)
            p = p->nextEdge1;
        else
            p = p->nextEdge2;
    }
    if (p == NULL)
        return;
    
}
int AdjMultListNetwork::GetIndex(string name) const {
  for (int i = 0; i < vexNum; ++i) {
    if (vexTable[i].country.name == name) return i;
  }
  return -1;
}
string AdjMultListNetwork::GetName(int index) const {
  if (index < 0 || index >= vexNum) cerr << "Invalid index.";
  return vexTable[index].country.name;
}

#endif