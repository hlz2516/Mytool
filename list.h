#include <iostream>
using std::cout;
using std::endl;

template<class T>
struct Node {
	T data;
	Node* next;
	Node(T i) {
		data = i;
		next = NULL;
	}
};

template<class T>
class Mylist {
	int length;
	Node<T>* head;
public:
	Mylist() { length = 0; head = new Node<T>(T(NULL)); }//生成空链表
	Mylist(T* arr, int n) {
		length = 0; head = new Node<T>(T(NULL));
		for (int i = 0; i < n; i++)
			insertAslast(arr[i]);
	}//用数组生成链表
	int getLength() { return length; }//得到链表长度
	void insertAsfirst(T val);//作为首节点插入
	void insertAslast(T val);//作为尾节点插入
	void insertByindex(int index, T val);//在索引为index的元素前面插入值为val的元素
	int remove(int index);//删除索引为index的元素
	T getelem(int index);//得到索引为index的元素
	void modify(int index, T val);//修改索引为Index的元素的值为val
	void show();//打印链表里的所有元素
	void removeMin();//从线性表中删除具有最小值的元素，空出的位置由最后一个元素填补。 
	void removeFrom_s_to_t(T s, T t);//从线性表中删除其值在给定值s与t之间的所有元素。 
	bool isSorted();//判断是否已经排序
	void remove_duplicate();//从线性表中删除所有值重复的元素。
							//将两个递增的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中不允许有重复的数据。 
	void mergelist(Mylist<T>& list1);
	void clear();  //清空链表
	void reverse();//反转链表
	Node<T>* findmid();//找到中间的节点并返回
};
template<class T>
void Mylist<T>::insertAsfirst(T val)
{
	Node<T>* temp = new Node<T>(val);
	if (head->next == NULL)
		head->next = temp;
	else {
		temp->next = head->next;
		head->next = temp;
	}
	length++;
}

template<class T>
void Mylist<T>::insertAslast(T val) {
	Node<T>* temp = new Node<T>(val);
	if (head->next == NULL)
	{
		head->next = temp;
		length++;
		return;
	}
	Node<T>* p = head;
	for (int i = 0; i<length; i++)
		p = p->next;  //此时p指向最后一个节点 
	p->next = temp;
	length++;
}

template<class T>
void Mylist<T>::insertByindex(int index, T val)
{
	if (index == length)
	{
		insertAslast(val);
		return;
	}
	if (index < 0 || index > length)
		return;
	Node<T>* temp = new Node<T>(val);
	Node<T>* p = head;
	for (int i = 0; i < index; i++)
		p = p->next;    //循环结束时p指向index-1的位置
	temp->next = p->next;
	p->next = temp;
	length++;
}

template<class T>
int Mylist<T>::remove(int index) {
	if (index < 0 || index > length - 1)
		return -1;   //当函数返回-1时通常说明您输入的参数有误
	Node<T>* p = head;
	for (int i = 0; i< index; i++)
		p = p->next;	     //此时p指向要删除的节点的前一个节点
	if (p->next->next == NULL)
	{
		T tempData = p->next->data;
		delete p->next;
		p->next = NULL;
		length--;
		return tempData;
	}
	Node<T>* temp = p->next;
	T tempData = p->data;
	p->next = p->next->next;
	delete temp;
	length--;
	return tempData;
}

template<class T>
T Mylist<T>::getelem(int index) {
	if (index < 0 || index > length - 1)
		return -1;
	Node<T>* p = head->next;
	for (int i = 0; i<index; i++)
		p = p->next;
	return p->data;
}

template<class T>
void Mylist<T>::modify(int index, T val) {
	if (index < 0 || index > length - 1)
		return;
	Node<T>* p = head->next;
	for (int i = 0; i<index; i++)
		p = p->next;
	p->data = val;
}

template<class T>
void Mylist<T>::show() {
	Node<T>* p = head->next;
	for (int i = 0; i<length; i++)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

template<class T>
void Mylist<T>::removeMin() {
	if (length <= 1)
		return;
	//遍历链表找最小元素，并保存尾节点的值
	//如果最小元素是尾节点，啥也不做。
	//如果不是，将最小元素的值更改为尾节点的值，将尾节点删去
	T min = getelem(0), val_of_end = getelem(length - 1), index = 0;
	for (int i = 0; i < length; i++)
	{
		if (i == length - 1 && getelem(i) < min)
			return;
		if (getelem(i) < min)
		{
			min = getelem(i);
			index = i;
		}
	}
	modify(index, val_of_end);
	remove(length - 1);
}

template<class T>
void Mylist<T>::removeFrom_s_to_t(T s,T t)
{
	if (s > t) return;
	for (int i = 0; i<length; i++)
	{
		T elem = getelem(i);
		if (elem >= s && elem <= t)
		{
			remove(i);
			i--;
		}
	}
}

template<class T>
bool Mylist<T>::isSorted() {
	if (length < 2) return true;
	Node<T>* p = head->next;
	while (p->next != NULL) {
		if (p->data > p->next->data)
			return false;
		p = p->next;
	}
	return true;
}

template<class T>
void Mylist<T>::remove_duplicate() {
	for (int i = 0; i < getLength(); i++)
	{
		T elem = getelem(i);
		for (int j = i + 1; j < getLength(); j++)
		{
			T elem1 = getelem(j);
			if (elem == elem1)
			{
				remove(j);
				j--;
			}
		}
	}
}

template<class T>
void Mylist<T>::mergelist(Mylist<T>& list1) {
	if (!isSorted() || !list1.isSorted())
	{
		cout << "输入的链表未排序，无法为当前两个链表合并" << endl;
		return;
	}
	Node<T>* p1 = head;
	Node<T>* p2 = list1.head->next;
	while (p1->next != NULL && p2 != NULL)
	{
		if (p2->data <= p1->next->data)
		{
			Node<T>* temp = p2->next;
			p2->next = p1->next;
			p1->next = p2;
			p1 = p1->next;
			p2 = temp;
			length++;
		}
		else {
			p1 = p1->next;
		}
	}
	if (p1->next == NULL && p2 != NULL) {
		p1->next = p2;
		int len = 0;
		while (p2 != NULL) {
			len++;
			p2 = p2->next;
		}
		length += len;
	}
	remove_duplicate();
}

template<class T>
void Mylist<T>::reverse()
{
	Node<T>* prev = NULL, *cur = head->next, *suc;   
	while (cur) {
		suc = cur->next;  //suc的作用只是为了保存当前节点的后一个节点
		cur->next = prev;  //prev是当前节点的前一个节点，当当前节点是第一个节点时为NULL。这步的作用是将当前节点与上一个节点连接
		prev = cur; //指向前一个节点的指针指向当前节点的指针，相当于往后移动一次
		cur = suc;//指向当前节点的指针指向suc，相当于cur往后移动一次
	}
	head->next = prev;
}

template<class T>
Node<T>* Mylist<T>::findmid()
{
	//快慢指针法
	Node<T>* slow = head, *fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next ? fast->next->next : fast->next;
	}
	return slow;
}

template<class T>
void Mylist<T>::clear()
{
	Node<T>* p = head;
	while (p->next)
		remove(0);
}