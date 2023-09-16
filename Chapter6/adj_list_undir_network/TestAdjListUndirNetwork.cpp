/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 * 
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *            佛祖保佑     永不宕机     永无BUG
 */

#include "AdjListUndirNetwork.h"			// 无向图的邻接表
#include "conio.h"


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
			case '\t':   cout << "[Tab] ";   break;					// 选项中的Tab字符'\t'{即ASCII编码9)
			case '\x1b': cout << "[Esc] ";   break;					// 选项中的Esc字符'\x1b'{即ASCII编码27)
			case ' ':    cout << "[Space] "; break;					// 选项中的空格字符' '{即ASCII编码32)
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
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
		int m[6][6] = {// 参考教材P237 图7-18的无向网
			{infity, 34, 46, infity, infity, 19},
			{34, infity, infity, infity, 12, infity},
			{46, infity, infity, 17, infity, 25},
			{infity, infity, 17, infity, 38, 25},
			{infity, 12, infity, 38, infity, 26},
			{19, infity, 25, 25, 26, infity}
		};
		char c = 'a', e, e1, e2;
		int n = 6, v, v1, v2, w;

		AdjListUndirNetwork<char, int> network(vexs, n);

		for (int v = 0; v < n; v++)
			for (int u = v; u < n; u++)		// 节约时间只利用m的上三角矩阵的信息
				if (m[v][u] != infity) network.InsertEdge(v, u, m[v][u]);// 已避免插入重复边的问题

	    while (c != '0' && c != '\x1b')	{
            cout << endl << "1. 无向图清空.";
            cout << endl << "2. 显示无向图.";
            cout << endl << "3. 取指定顶点的值.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
            cout << endl << "9. 设置指定边的权.";
			cout << endl << "/. 求各个顶点的度.";
			cout << endl << "*. 求连通分量数目.";
			cout << endl << "-. 求最小生成树.";
		    cout << endl << "0. 退出[Esc]";
			cout << endl;
			c = Choice("请选择：", "123456789/*-0\x1b");
			switch (c) 		{
			    case '1':
				{
					char c = Choice("确认清空无向图吗?", "YN");
					if (c == 'Y' || c == 'y')
						network.Clear();
				    break;
				}
			    case '2':
                    if (network.IsEmpty())
                        cout << "该无向图为空。" << endl;
                    else 
			            network.Display();
				    break;
			    case '3':
			        cout << endl << "输入顶点序号{无向图的顶点序号从0开始):";
			        cin >> v;
		            network.GetElem(v, e);
		            cout << "序号为" << v << "的顶点值为" << e;
			        break;
			    case '4':
			        cout << endl << "输入顶点序号{无向图的顶点序号从0开始):";
			        cin >> v;
			        cout << endl << "输入" << v <<"号顶点的值:";
			        cin >> e;
		            network.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "输入被删除顶点的值:";
			        cin >> e;
		            network.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "输入插入顶点的值:";
			        cin >> e;
		            network.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "输入与被删除边关联的两个顶点值:";
			        cin >> e1 >> e2;
			        v1 = network.GetOrder(e1);
			        v2 = network.GetOrder(e2);
		            network.DeleteEdge(v1, v2);
			        break;
			    case '8':
			        cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
			        cin >> e1 >> e2 >> w;
			        v1 = network.GetOrder(e1);
			        v2 = network.GetOrder(e2);
		            network.InsertEdge(v1, v2, w);
			        break;
			    case '9':
			        cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
			        cin >> e1 >> e2 >> w;
			        v1 = network.GetOrder(e1);
			        v2 = network.GetOrder(e2);
		            network.SetWeight(v1, v2, w);
			        break;
				case '/':
					cout << endl; 
					for (int i = 0; i < network.GetVexNum(); i++)
					{
						char c;
						network.GetElem(i, c);
						cout << c << '\t';
					}
					cout << endl;
					for (int i = 0; i < network.GetVexNum(); i++)
					{
						cout << network.GetDegreeofVex(i) << '\t';
					}
					break;
				case '*':
					cout << endl
						 << "连通分量数目为: " << network.GetBranchNum();
					break;
				case '-':
					cout << "\nKruskal算法求最小生成树" << endl;
					network.Kruskal();
					cout << "\nPrim算法求最小生成树" << endl;
					network.Prim(0);
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

