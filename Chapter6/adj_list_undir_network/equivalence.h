#ifndef __ELEM_NODE_H__
#define __ELEM_NODE_H__


// 并查集元素结点类
template <class ElemType>
struct ElemNode 
{
// 数据成员:
	ElemType data;				// 数据域
	int parent;	                // 双亲域 
};

#endif


#ifndef __SIMPLE_EQUIVALENCE_H__				// 如果没有定义__SIMPLE_EQUIVALENCE_H__
#define __SIMPLE_EQUIVALENCE_H__				// 那么定义__SIMPLE_EQUIVALENCE_H__

// 并查集
template <class ElemType>
class Equivalence
{
protected:
// 并查集的数据成员:
	ElemNode<ElemType> *set;					// 存储结点的双亲
	int size;									// 结点个数

// 辅助函数
    int Find(ElemType e) const;					// 查找元素e所在等价类的根
	void GetParent(int*&) const;
	int GetHeight(ElemType e) const;

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	Equivalence(ElemType es[], int sz);					// 构造sz个单结点树(等价类)
	virtual ~Equivalence();				// 析构函数
	ElemType GetElem(int p)const;
	int GetOrder(ElemType e)const;
	void Union(ElemType a, ElemType b);					// 合并a与b所在的等价类
	void Union_byHeight(ElemType a, ElemType b);
	void Union_byNumofNodes(ElemType a, ElemType b);
	bool Differ(ElemType a, ElemType b) const;			// 如果a与b不在同一棵树上，返回true，否则返回false
	Equivalence(const Equivalence &copy);				// 复制构造函数
	Equivalence &operator =(const Equivalence &copy);	// 赋值运算符
	void Show() const;
	int GetSize() const;
	void ShowParent() const;
};

                                                                                                                                       
// 并查集的实现部分
template <class ElemType>
Equivalence<ElemType>::Equivalence(ElemType es[], int sz)
// 操作结果：构造sz个单结点树(等价类)
{
	size = sz;									// 容量
	set = new ElemNode<ElemType>[size];						// 分配空间
	for (int i = 0; i < size; i++) {
        set[i].data = es[i];
		set[i].parent = -1;							// 每个结点构成单结点树形成的等价类
    }
}

template <class ElemType>
int Equivalence<ElemType>::Find(ElemType e) const
// 操作结果：查找结点p所在树的根
{
	int p = 0; int level = 0;
    while (p < size && set[p].data != e)
        p++;
	if (p == size)
		throw Error("元素不存在!");					// 抛出异常
	int cur = p;
	while (set[p].parent > -1)
	{//找到根
		p = set[p].parent;
		level++;								//记录查找路径
	}
	if (level > 2)								//判断查找路径大于2
	{
		while (p != set[cur].parent)			//按折叠规则压缩路径
		{
			int k = set[cur].parent;
			set[cur].parent = p;
			cur = k;
		}
	}
	//if (level > 2)								//查找路径大于2
	//	set[cur].parent = p;
	return p;									// 返回根
}

template<class ElemType>
inline int Equivalence<ElemType>::GetHeight(ElemType e) const
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (e == set[i].data)
			break;
	}
	if (i == size)
		throw Error("元素不存在!");
	else
	{
		int height = 0;
		for (int j = i; j >= 0; j = set[j].parent)
		{
			height++;
		}
		return height;
	}
}

template <class ElemType>
Equivalence<ElemType>::~Equivalence()
// 操作结果：释放对象占用的空间――析构函数
{
	delete []set;							// 释放数组parent
}

template <class ElemType>
ElemType Equivalence<ElemType>::GetElem(int p) const
// 操作结果：查找结点p所在树的根
{
	if (p < 0 || p >= size)
		throw Error("元素不存在!");					// 抛出异常
	return set[p].data;									// 返回根
}

template <class ElemType>
int Equivalence<ElemType>::GetOrder(ElemType e) const
// 操作结果：查找结点p所在树的根
{
    int p = 0;
    while (p < size && set[p].data != e)
        p++;
	if (p == size)
		throw Error("元素不存在!");					// 抛出异常
	return p;									// 返回根
}

template <class ElemType>
void Equivalence<ElemType>::Union(ElemType a, ElemType b)
// 操作结果：合并a与b所在的等价类
{
	int root1 = Find(a);						// 查找a所在树(等价类)的根		
	int root2 = Find(b);						// 查找b所在树(等价类)的根		
	if (root1 != root2) {
       set[root1].parent += set[root2].parent;
       set[root2].parent = root1;	// 合并树(等价类)
    }
}

template<class ElemType>
inline void Equivalence<ElemType>::Union_byHeight(ElemType a, ElemType b)
{//将高度较低的树并入高度较高的树
	int root1 = Find(a);
	int root2 = Find(b);
	if (root1 != root2)
	{
		int height1 = GetHeight(a);
		int height2 = GetHeight(b);
		//cout << height1 << '\t' << height2 << endl;
		if (height1 >= height2)
		{
			set[root1].parent += set[root2].parent;
			set[root2].parent = root1;
		}
		else
		{
			set[root2].parent += set[root1].parent;
			set[root1].parent = root2;
		}
	}
}

template<class ElemType>
inline void Equivalence<ElemType>::Union_byNumofNodes(ElemType a, ElemType b)
{//将度数低的树并入度数较高的树
	int root1 = Find(a);
	int root2 = Find(b);
	if (root1 != root2)
	{
		if (set[root1].parent <= set[root2].parent)
		{
			set[root1].parent += set[root2].parent;
			set[root2].parent = root1;
		}
		else
		{
			set[root2].parent += set[root1].parent;
			set[root1].parent = root2;
		}
	}
}

template <class ElemType>
bool Equivalence<ElemType>::Differ(ElemType a, ElemType b) const
// 操作结果：如果a与b不在同一棵树上，返回true，否则返回false
{
	int root1 = Find(a);						// 查找a所在树(等价类)的根		
	int root2 = Find(b);						// 查找b所在树(等价类)的根		
	return root1 != root2;						// 比较树(等价类)的根
}

template <class ElemType>
Equivalence<ElemType>::Equivalence(const Equivalence &copy)
// 操作结果：由copy构造新对象――复制构造函数
{
	size = copy.size;							// 容量
	set = new ElemNode<ElemType>[size];						// 分配空间
	for (int i = 0; i < size; i++) {
		set[i].parent = copy.set[i].parent;				// 复制parent的每个元素
		set[i].data = copy.set[i].data;				// 复制parent的每个元素
    }
}

template <class ElemType>
Equivalence<ElemType> &Equivalence<ElemType>::operator=(const Equivalence<ElemType> &copy)
// 操作结果：将copy赋值给当前对象――赋值运算符
{
	if (&copy != this)	{
		size = copy.size;						// 容量
		delete []set;						// 释放空间
	    set = new ElemNode<ElemType>[size];						// 分配空间
	    for (int i = 0; i < size; i++) {
		    set[i].parent = copy.set[i].parent;				// 复制parent的每个元素
		    set[i].data = copy.set[i].data;				// 复制parent的每个元素
         }
	}
	return *this;
}

template<class ElemType>
inline void Equivalence<ElemType>::Show() const
{
	bool* out = new bool[size];				// 已输出的结点值为true，否则值为false
	for (int i = 0; i < size; i++)
		out[i] = false;
	int p = 0;				// 当前结点
	while (p < size)		{	// 对没有输出的当前结点，输出其等价类
		cout << "{" << GetElem(p);
		out[p] = true;
		for (int i = p + 1; i < size; i++)	{	// 输出等价类
			if (!Differ(GetElem(p), GetElem(i)))	{	// p与i在同一个等价类中
				cout << "," << GetElem(i);
				out[i] = true;
			}
		}
		cout << "}" << endl;
		while (p < size && out[p]) p++;
	}
	cout << endl;
	delete[] out;
}

template<class ElemType>
inline int Equivalence<ElemType>::GetSize() const
{
	return size;
}

template<class ElemType>
inline void Equivalence<ElemType>::GetParent(int*& parents) const
{
	if (parents != NULL)
		delete[] parents;
	parents =  new int[size];
	for (int i = 0; i < size; i++)
	{
		parents[i] = set[i].parent;
	}
}

template<class ElemType>
inline void Equivalence<ElemType>::ShowParent() const
{
	int* p=NULL;
	GetParent(p);
	for (int i = 0; i < size; i++)
	{
		cout << p[i] << ',';
	}
	cout << "\b \n" << endl;
}



#endif
