//#pragma once
#include <iostream>
#include "list.h"
using namespace std;

template <class T>
class ListStack { //链表栈
	Mylist<T> list;
public:
	ListStack() :list() { }  //初始化
	int getSize() { return list.getLength(); } //得到当前栈内元素个数
	bool is_empty() { return list.getLength() == 0; }  //判空
	void push(T elem) {	list.insertAsfirst(elem);	 } //进栈
	T pop() //出栈
	{
		T temp = list.getelem(0);
		list.remove(0);
		return temp;
	}
	T get_Top() { return list.getelem(0); }  //得到栈顶元素
	void clear() {  //清空栈
		list.clear();
	}
};