#pragma once
#include "Mytool.h"
typedef int Rank;
#define Default 5
using namespace std;
template <class T>
class Vector
{
private:
	int _size;
	int _capacity;
	T* _elem;
public:
	//构造函数
	Vector(int c = Default, int size = 0, T elem = 0);
	Vector(const T* a, Rank n) { copyfrom(a, 0, n); }
	Vector(const T* a, Rank lo, Rank hi) { copyfrom(a, lo, hi); }
	Vector(const Vector<T>& v) { copyfrom(v._elem, 0, v._size); }
	//各种功能
	inline int size() { return _size; } 
	inline bool is_empty() { return _size == 0; }
	inline bool is_full();
	void expand();//扩容
	void shrink();//缩容
	void insert_s(Rank r, T &t);//在指定的秩插入指定的元素，该函数适用于传间接参数
	void insert(Rank r, T t);//在指定的秩插入指定的元素，该函数适用于传直接参数
	void insert_s(T &t) { if (_size >= _capacity) return;  _elem[_size] = t; _size++; is_full(); }//在数组末尾插入指定的元素，该函数适用于传间接参数
	void insert(T t) { if (_size >= _capacity) return;  _elem[_size] = t; _size++; is_full(); }//在数组末尾插入指定的元素，该函数适用于传直接参数
	void copyfrom(const T* a, Rank lo, Rank hi);//拷贝一个数组中[lo,hi)中的元素到自己的数组中
	int remove(Rank low, Rank hi);//删除[low,hi)元素
	T remove(Rank r) { T temp = _elem[r]; remove(r, r + 1); return temp; }//删除指定秩的元素
	void unsort() { array_rand(_elem, _size); }//数组置乱
	void Bubble_Sort() { BubbleSort(_elem, _size); }//冒泡排序
	void Merge_Sort() { MergeSort(_elem, 0, _size); }//归并排序
	bool is_sorted();   //判断是否已经升序排序
	Rank find_s(T &t,Rank low, Rank hi); //在[low,hi)内寻找为t的元素并返回t所在的Rank,该函数适用于传间接参数
	Rank find(T t, Rank low, Rank hi);  //在[low,hi)内寻找为t的元素并返回t所在的Rank,该函数适用于传直接参数
	Rank find_s(T &t) { return find_s(t, 0, _size); }//在数组内寻找为t的元素并返回t所在的Rank,该函数适用于传间接参数
	Rank find(T t) { return find(t, 0, _size); }//在数组内寻找为t的元素并返回t所在的Rank,该函数适用于传直接参数
	void deduplicate();//删除数组内重复的元素
	void traverse(void(*visit)(T&));//通过函数指针对每个元素做visit操作
	void show();
	void insertforward(Rank r1, Rank r2);
	void insertbackward(Rank r1, Rank r2);
	void insertionsort();//插入排序
	void selectionsort();//选择排序
	//运算符重载
	Vector& operator=(Vector const &v);
	inline T& operator[](Rank r) { return _elem[r]; }
	template <class Y>
	friend ostream& operator <<(ostream& os, const Vector<Y> &v);
	//析构函数
	~Vector() { delete[]_elem; }
};
//以下为接口实现
template <class T>
Vector<T>::Vector(int c, int size, T elem) :_capacity(c), _size(size)
{
	_elem = new T[c];
	for (int i = 0; i<size; i++)
		_elem[i] = elem;
}

template <class T>
void Vector<T>::copyfrom(const T* arr, Rank lo, Rank hi)
{
	_size = 0;
	_capacity = (hi - lo) * 2;
	if (_elem)
		delete[]_elem;
	_elem = new T[_capacity];
	for (int i = 0; i < hi-lo; i++)
	{
		_elem[i] = arr[i+lo];
		_size++;
	}
}

template <class T>
bool Vector<T>::is_full()
{
	if (_size == _capacity)
	{
		expand();
		return true;
	}
	else return false;
}

template <class T>
void Vector<T>::expand()
{
	T* oldelem = _elem;
	_elem = new T[_capacity *= 2];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldelem[i];
	}
	delete[] oldelem;
}

template <class T>
void Vector<T>::shrink()
{
	if (_capacity < Default) return;
	if (_size < _capacity / 2)
	{
		T* oldelem = _elem;
		_elem = new T[_capacity /= 2];
		for (int i = 0; i < _size; i++)
			_elem[i] = oldelem[i];
		delete[] oldelem;
	}
}

template <class T>
void Vector<T>::insert_s(Rank r, T &t)
{
	if (r >= _capacity)
	{
		std::cout << "输入的秩大于或等于了容量!\n";
		return;
	}
	if (r > _size && r < _capacity)
	{
		for (int i = _size; i < r; i++)
		{
			_elem[i] = 0; _size++;
		}
		_elem[r] = t; _size++;
		return;
	}
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = t;
	_size++;
	is_full();
}

template <class T>
void Vector<T>::insert(Rank r, T t)
{
	if (r >= _capacity)
	{
		std::cout << "输入的秩大于或等于了容量!\n";
		return;
	}
	if (r > _size && r < _capacity)
	{
		for (int i = _size; i < r; i++)
			{ _elem[i] = 0; _size++; }
		_elem[r] = t; _size++;
		return;
	}
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = t;
	_size++;
	is_full();
}

template <class T>
int Vector<T>::remove(Rank low, Rank hi)
{
	int move = _size - hi;
	for (int i = 0; i < move; i++)
		_elem[low++] = _elem[hi++];
	_size = low;
	shrink();
	return hi - low;
}

template <class T>
bool Vector<T>::is_sorted()
{
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] > _elem[i])
			return false;
	}
	return true;
}

template <class T>
Rank Vector<T>::find_s(T &t,Rank low, Rank hi)
{
	if (hi > _size) return -2;
	for (int i = low; i < hi; i++)
	{
		if (_elem[i] == t)
			return i;
	}
	return -1;
}

template <class T>
Rank Vector<T>::find(T t, Rank low, Rank hi)
{
	if (hi > _size) return -2;
	for (int i = low; i < hi; i++)
	{
		if (_elem[i] == t)
			return i;
	}
	return -1;
}

template <class T>
void Vector<T>::deduplicate()
{
	for (int r,i = 0; i < _size; i++)
	{
		while (r=find_s(_elem[i],i+1,_size) > 0)
			remove(r);
	}
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> const &v)
{
	if (_elem)
		delete[] _elem;
	copyfrom(v._elem, 0, v._size);
	return *this;
}

template <class T>
void Vector<T>::show() {
	for (int i = 0; i<_size; i++)
	{
		std::cout << _elem[i] << " ";
	}
}

template <class Y>
ostream& operator <<(ostream& os, const Vector<Y> &v)
{
	for (int i = 0; i < v._size; i++)
		os << v._elem[i] << " "; 
	return os;
}

template <class T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)
		(*visit)(_elem[i]);
}

template <class T>
void Vector<T>::insertforward(Rank r1, Rank r2)
{
	if (r1 == r2 || r2 == (r1+1))
		return;
	T temp = _elem[r2];
	remove(r2, r2 + 1);
	insert_s(r1+1, temp);
}

template <class T>
void Vector<T>::insertbackward(Rank r1, Rank r2)
{
	if (r1 == r2)
		return;
	T temp = _elem[r1];
	remove(r1, r1 + 1);
	insert_s(r2, temp);
}

template <class T>
void Vector<T>::insertionsort() //升序
{
	for (int i = 1; i < _size; i++)
	{
		bool flag = false;
		for (int j = i - 1; j >= 0; j--)
		{
			if (_elem[i] >= _elem[j])
			{
				insertforward(j, i);
				flag = true;
				break;
			}
		}
		if(flag == false)
		insertforward(-1, i);
	}
}

template <class T>
void Vector<T>::selectionsort()
{
	for(int i=_size-1;i>0;i--)
		for (int j = 0; j < i; j++)
		{
			if (_elem[j] > _elem[i])
				h_swap(_elem[j], _elem[i]);
		}
}
//template <class VST>     //don't understand
//void traverse(VST &vst)
//{
//	for (int i = 0; i < _size; i++)
//		vst(_elem[i]);
//}

