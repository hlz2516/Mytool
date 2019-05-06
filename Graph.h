#pragma once
#include <graphics.h>
#include <math.h>
#include <vector>
#include <queue>
#include "Mytool.h"
#define MAX_CAPACITY 64
typedef enum {undiscovered,discovered,visited} Vstatus;  //����״̬
//undiscovered δ�����ֵ�		discovered �ѱ����ֵ���û�����е�  visited  �ѱ����ֲ����˶��е�
typedef enum {undetermined,tree,cross,forward,backward} Etype;   //��״̬
//undetermined ��û���߹��ı�  tree ����������һ����  cross �޷��������ı�
//������
struct Vertex {
	int data;//����
	int indegree, outdegree; //��Ⱥͳ���
	Vstatus status; //״̬
	int dtime, ftime;
	int parent; //����
	Vertex(int _data = 0):data(_data),indegree(0),outdegree(0),
		status(undiscovered),dtime(-1),ftime(-1),parent(-1) {}
	//Vertex(int _x, int _y, int _data = 0);
	bool operator==(Vertex &v)
	{
		if (this->data == v.data && this->indegree == v.indegree &&
			this->outdegree == v.outdegree && this->parent == v.parent)
			return true;
		else return false;
	}
};

struct Edge {
	int data;
	int weight;
	Etype type;
	Edge(int _data = 0, int _weight = 0):data(_data),weight(_weight),type(undetermined) { }
};

class GraphMatrix {
private:
	int n;//��������
	int e;//������
	vector<Vertex> V;
	vector<vector<Edge*>> E;
public:
	GraphMatrix() {
		n = e = 0;
		E.reserve(MAX_CAPACITY);
	}
	~GraphMatrix() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (E[i][j] != NULL)
				{
					delete E[i][j];
					E[i][j] = (Edge*)NULL;
				}
	}
	bool exists(int i, int j) {  //�ߣ�i��j���Ƿ����
		return ((i >= 0) && (i < n) && (j >= 0) && (j < n) && E[i][j] != (Edge*)NULL);
	}
	int& dTime(int i) { return V[i].dtime; } //����vector<vertex>��ָ������Ϊi�Ķ����dtime
	int& fTime(int i) { return V[i].ftime; }
	Vstatus& status(int i) { return V[i].status; }
	int& parent(int i) { return V[i].parent; }
	int insert_v(int data);  //���붥�㣬���ر��
	int remove_v(int i);  //ɾ����i�����㼰�������
	void insert_e(int data, int weight, int i, int j); //����Ȩ��Ϊw���Ӷ���i��j�ı�
	int remove_e(int i, int j);
	int nextNbr(int i,int j) {
		while ((-1 < j) && (!exists(i, --j)));  //ֻҪi��j����֮��û�б߻���jû�г��磬ѭ������
		return j;                 //���仰˵��ֻҪ��j�𽥼�С��0�Ĺ������ҵ���һ����i�����ıߣ��ͷ���j
	}
	int firstNbr(int i) { return nextNbr(i, n); }
	Etype& etype(int i, int j) { return E[i][j]->type; }
	void bfs(int i,int& clock);//���Ե���ͨ����Ч��clock��ʼΪ0
};

int GraphMatrix::insert_v(int data)
{
	for (int j = 0; j < n; j++) E[j].push_back((Edge*)NULL);  //�ڵ�ǰ�����ÿһ��β������һ���յı�
	n++;
	E.push_back(vector<Edge*>(n, (Edge*)NULL));  //�ڵ�ǰ����β����һ��ȫΪ�յı�
	Vertex temp(data);  //�����½ڵ�
	V.push_back(temp);  //���½ڵ��������
	return V.size()-1;  //���ظýڵ���
}

int GraphMatrix::remove_v(int i)
{
	for (int j = 0; j < n; j++){
		if (exists(i, j)) { //������ڴӵ�i�����㵽��j������ı�
			remove_e(i, j);  //ɾ���ñ�
		}
	}
	E.erase(E.begin() + i); n--;   //ɾ����ǰ�����е�i�пռ䣬������-1
	int temp = V[i].data; V.erase(V.begin() + i);//���沢ɾ�������еĵ�i������
	for (int j = 0; j < n; j++)
	{
		if (exists(j,i)) {  //������ڴӵ�j�����㵽��i������ı�
			delete E[j][i];
			E[j][i] = (Edge*)NULL; e--;
			V[j].outdegree--;   //�������������ͬ��
		}
		E[j].erase(E[j].begin() + i);   //ɾ����ǰ�еĵ�i���ռ�
	}
	return temp;
}

void GraphMatrix::insert_e(int data, int weight, int i, int j)
{
	if (exists(i, j)) return;
	Edge* temp = new Edge(data, weight);
	E[i][j] = temp;
	e++; V[i].outdegree++; V[j].indegree++;
}

int GraphMatrix::remove_e(int i, int j)
{
	if (!exists(i, j)) return -1;
	int temp = E[i][j]->data; delete E[i][j]; E[i][j] = (Edge*)NULL;
	e--; V[i].outdegree--; V[j].indegree--;
	return temp;
}

void GraphMatrix::bfs(int i,int& clock)
{
	queue<int> Q;
	status(i) = discovered; Q.push(i);  //����i�������״̬����Ϊ�����֣�Ȼ�����
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();  //���浱ǰ����ͷ������vȻ��pop
		dTime(v) = ++clock;  //dtime����ڼ���
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) //��v�ĵ�һ���ھӶ��㿪ʼ�����һ��
		{
			if (undiscovered == status(u))  //������ֵ�ǰ���ھ���û�����ֵ�
			{
				status(u) = discovered; Q.push(u); //����״̬��Ϊ�����ֵĲ����
				etype(u, v) = tree; parent(u) = v; //��Ϊ��ǰ�ı��������һ���ߣ�������Ϊtree�������ھӵĸ�����Ϊv
			}
			else etype(u, v) = cross; //�����������һ�����ھӱ������˵����ڶ����У�һ�����ھ����Ѿ����˶��еģ�����Ϊ���
		}
		status(v) = visited; 
	}
}