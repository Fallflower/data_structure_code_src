#include "AdjMatrixDirNetwork.h"		// 邻接矩阵无向图
#include<conio.h>
int Choice(const char* prompt, const char* options = "");	// 函数声明

int Pos(char ch, const char* str)			// 返回指定字符ch在字符串str中的下标。不存在时返回-1
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		if (ch == str[i])
			return i;
	return -1;
}

int Choice(const char* prompt, const char* options)		// 函数定义。输出提示信息prompt，输入选择的字符并返回。
{
	int key;
	cout << prompt << "{";
	for (int i = 0; options[i] != '\0'; i++)
	{
		if (' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// 选项options中的可打印字符
			cout << options[i] << ' ';
		else														// 选项options中的部分控制字符
		{
			switch (options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// 选项中的Tab字符'\t'（即ASCII编码9）
			case '\x1b': cout << "[Esc] ";   break;					// 选项中的Esc字符'\x1b'（即ASCII编码27）
			case ' ':    cout << "[Space] "; break;					// 选项中的空格字符' '（即ASCII编码32）
			}
		}
	}
	cout << "\b}: ";					// '\b'退格。先退一格，在输出右花括号
	do
	{
		key = getch();
	} while (options[0] != '\0' && Pos(key, options) < 0); // 若options为空长度为0的字符串，则输入无限制；否则输入项应该在optins中。
	cout << endl;
	return key;
}

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		char vexs[] = {'A', 'B', 'C', 'D', 'E'};
		double m[5][5] = {	// 引用教程图7-23带权有向图示例
			{WI, 10, WI, 30, 100},
			{WI, WI, 50, WI, WI},
			{WI, WI, WI, WI, 10},
			{WI, WI, 20, WI, 60},
			{WI, WI, WI, WI, WI},
		};
		char c = '9', e, e1, e2;
		int n = 5, v, v1, v2;

		AdjMatrixDirNetwork<char> g(vexs, n, 7);

		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++)
				if (m[u][v] < WI) g.InsertArc(u, v);

	    while (c != '0' && c != '\x1b')	{
            cout << endl << "1. 图清空.";
            cout << endl << "2. 显示图.";
            cout << endl << "3. 取指定顶点的值.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
		    cout << endl << "0. 退出[Esc]";
			c = Choice("\n选择功能: ","123456780\x1b");
		    switch (c) 		{
			    case '1':
			        g.Clear();
				    break;
			    case '2':
                    if (g.IsEmpty())
                        cout << "该图为空。" << endl;
                    else 
			            g.Display();
				    break;
			    case '3':
			        cout << endl << "输入顶点序号（图的顶点序号从0开始）:";
			        cin >> v;
		            g.GetElem(v, e);
		            cout << "序号为" << v << "的顶点为" << e;
			        break;
			    case '4':
			        cout << endl << "输入顶点序号（图的顶点序号从0开始）:";
			        cin >> v;
			        cout << endl << "输入" << v <<"号顶点的值:";
			        cin >> e;
		            g.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "输入被删除顶点的值:";
			        cin >> e;
		            g.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "输入插入顶点的值:";
			        cin >> e;
		            g.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "输入与被删除边关联的两个顶点值:";
			        cin >> e1 >> e2;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
		            g.DeleteArc(v1, v2);
			        break;
			    case '8':
			        cout << endl << "输入与插入边关联的两个顶点值:";
			        cin >> e1 >> e2;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
		            g.InsertArc(v1, v2);
			        break;
       	      }
         }
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	//system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

