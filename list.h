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
	Mylist() { length = 0; head = new Node<T>(T(NULL)); }//���ɿ�����
	Mylist(T* arr, int n) {
		length = 0; head = new Node<T>(T(NULL));
		for (int i = 0; i < n; i++)
			insertAslast(arr[i]);
	}//��������������
	int getLength() { return length; }//�õ�������
	void insertAsfirst(T val);//��Ϊ�׽ڵ����
	void insertAslast(T val);//��Ϊβ�ڵ����
	void insertByindex(int index, T val);//������Ϊindex��Ԫ��ǰ�����ֵΪval��Ԫ��
	int remove(int index);//ɾ������Ϊindex��Ԫ��
	T getelem(int index);//�õ�����Ϊindex��Ԫ��
	void modify(int index, T val);//�޸�����ΪIndex��Ԫ�ص�ֵΪval
	void show();//��ӡ�����������Ԫ��
	void removeMin();//�����Ա���ɾ��������Сֵ��Ԫ�أ��ճ���λ�������һ��Ԫ����� 
	void removeFrom_s_to_t(T s, T t);//�����Ա���ɾ����ֵ�ڸ���ֵs��t֮�������Ԫ�ء� 
	bool isSorted();//�ж��Ƿ��Ѿ�����
	void remove_duplicate();//�����Ա���ɾ������ֵ�ظ���Ԫ�ء�
							//��������������������ϲ�Ϊһ����������������Ҫ����������ʹ��ԭ����������Ĵ洢�ռ䣬������ռ�������Ĵ洢�ռ䡣���в��������ظ������ݡ� 
	void mergelist(Mylist<T>& list1);
	void clear();  //�������
	void reverse();//��ת����
	Node<T>* findmid();//�ҵ��м�Ľڵ㲢����
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
		p = p->next;  //��ʱpָ�����һ���ڵ� 
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
		p = p->next;    //ѭ������ʱpָ��index-1��λ��
	temp->next = p->next;
	p->next = temp;
	length++;
}

template<class T>
int Mylist<T>::remove(int index) {
	if (index < 0 || index > length - 1)
		return -1;   //����������-1ʱͨ��˵��������Ĳ�������
	Node<T>* p = head;
	for (int i = 0; i< index; i++)
		p = p->next;	     //��ʱpָ��Ҫɾ���Ľڵ��ǰһ���ڵ�
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
	//������������СԪ�أ�������β�ڵ��ֵ
	//�����СԪ����β�ڵ㣬ɶҲ������
	//������ǣ�����СԪ�ص�ֵ����Ϊβ�ڵ��ֵ����β�ڵ�ɾȥ
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
		cout << "���������δ�����޷�Ϊ��ǰ��������ϲ�" << endl;
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
		suc = cur->next;  //suc������ֻ��Ϊ�˱��浱ǰ�ڵ�ĺ�һ���ڵ�
		cur->next = prev;  //prev�ǵ�ǰ�ڵ��ǰһ���ڵ㣬����ǰ�ڵ��ǵ�һ���ڵ�ʱΪNULL���ⲽ�������ǽ���ǰ�ڵ�����һ���ڵ�����
		prev = cur; //ָ��ǰһ���ڵ��ָ��ָ��ǰ�ڵ��ָ�룬�൱�������ƶ�һ��
		cur = suc;//ָ��ǰ�ڵ��ָ��ָ��suc���൱��cur�����ƶ�һ��
	}
	head->next = prev;
}

template<class T>
Node<T>* Mylist<T>::findmid()
{
	//����ָ�뷨
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