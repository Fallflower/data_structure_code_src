#ifndef __ASSISTANCE_H__				// 如果没有定义__ASSISTANCE_H__
#define __ASSISTANCE_H__				// 那么定义__ASSISTANCE_H__

// 辅助软件包

// ANSI C++标准库头文件
#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数据函数
#include <fstream>					// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>					// 输入输出流格式设置	
#include <cstdarg> 					// 支持变长函数参数	
#include <cassert>					// 支持断言
#include <string>
#include <string.h>
using namespace std;				// 标准库包含在命名空间std中

// 自定义类型
enum Status {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

// 宏定义
#define DEFAULT_SIZE 1000			// 缺省元素个数
#define DEFAULT_INFINITY 1000000	// 缺省无穷大


// 辅助函数声明

char GetChar(istream &inStream = cin); // 从输入流inStream中跳过空格及制表符获取一字符

template <class ElemType >
void Swap(ElemType &e1, ElemType &e2);	// 交换e1, e2之值

template<class ElemType>
void Display(ElemType elem[], int n);	// 显示数组elem的各数据元素值

template <class ElemType>
void Write(const ElemType &e);			// 显示数据元素

// 辅助类
class Error;			// 通用异常类

char GetChar(istream &inStream)
// 操作结果：从输入流inStream中跳过空格及制表符获取一字符
{
	char ch;								// 临时变量
	while ((ch = (inStream).peek()) != EOF	// 文件结束符(peek()函数从输入流中接受1
											// 字符,流的当前位置不变)
		&& ((ch = (inStream).get()) == ' '	// 空格(get()函数从输入流中接受1字符,流
											// 的当前位置向后移1个位置)
		|| ch == '\t'));					// 制表符
	
	return ch;								// 返回字符
}

class Error : public std::exception
{
private:
	unsigned int m_code;
	string m_what;
public:
	Error(unsigned int code,  const string &what_arg): m_code(code), m_what(what_arg){}
	virtual const char * what(void) const noexcept override
	{
		string text = "Error code: " + to_string(m_code) + "\nError message: " + m_what;
		char* mesg = new char[text.length()+1];
		strcpy(mesg, text.c_str());
		return mesg;
	}
};


template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
// 操作结果: 交换e1, e2之值
{
	ElemType temp;		// 临时变量
	// 循环赋值实现交换e1, e2
	temp = e1;	e1 = e2;  e2 = temp;
}

template<class ElemType>
void Display(ElemType elem[], int n)
// 操作结果: 显示数组elem的各数据元素值
{
	for (int i = 0; i < n; i++)
	{	// 显示数组elem
		cout << elem[i] << "  ";
	}
	cout << endl; 
}

template <class ElemType>
void Write(const ElemType &e)
// 操作结果: 显示数据元素
{
    cout << e << "  ";
}

#endif