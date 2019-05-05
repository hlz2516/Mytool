//#pragma once
#include <iostream>
#include "list.h"
using namespace std;

template <class T>
class ListStack { //����ջ
	Mylist<T> list;
public:
	ListStack() :list() { }  //��ʼ��
	int getSize() { return list.getLength(); } //�õ���ǰջ��Ԫ�ظ���
	bool is_empty() { return list.getLength() == 0; }  //�п�
	void push(T elem) {	list.insertAsfirst(elem);	 } //��ջ
	T pop() //��ջ
	{
		T temp = list.getelem(0);
		list.remove(0);
		return temp;
	}
	T get_Top() { return list.getelem(0); }  //�õ�ջ��Ԫ��
	void clear() {  //���ջ
		list.clear();
	}
};