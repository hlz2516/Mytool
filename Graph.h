#pragma once
#include <graphics.h>
#include <math.h>
#include <vector>
#include <queue>
#include "Mytool.h"
#define MAX_CAPACITY 64
typedef enum {undiscovered,discovered,visited} Vstatus;  //顶点状态
//undiscovered 未被发现的		discovered 已被发现但还没出队列的  visited  已被发现并出了队列的
typedef enum {undetermined,tree,cross,forward,backward} Etype;   //边状态
//undetermined 还没被走过的边  tree 是属于树的一条边  cross 无法构成树的边
//顶点类
struct Vertex {
	int data;//数据
	int indegree, outdegree; //入度和出度
	Vstatus status; //状态
	int dtime, ftime;
	int parent; //父亲
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
	int n;//顶点总数
	int e;//边总数
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
	bool exists(int i, int j) {  //边（i，j）是否存在
		return ((i >= 0) && (i < n) && (j >= 0) && (j < n) && E[i][j] != (Edge*)NULL);
	}
	int& dTime(int i) { return V[i].dtime; } //返回vector<vertex>中指定索引为i的顶点的dtime
	int& fTime(int i) { return V[i].ftime; }
	Vstatus& status(int i) { return V[i].status; }
	int& parent(int i) { return V[i].parent; }
	int insert_v(int data);  //插入顶点，返回编号
	int remove_v(int i);  //删除第i个顶点及其关联边
	void insert_e(int data, int weight, int i, int j); //插入权重为w，从顶点i到j的边
	int remove_e(int i, int j);
	int nextNbr(int i,int j) {
		while ((-1 < j) && (!exists(i, --j)));  //只要i与j顶点之间没有边或者j没有出界，循环继续
		return j;                 //换句话说，只要在j逐渐减小到0的过程中找到了一条与i相连的边，就返回j
	}
	int firstNbr(int i) { return nextNbr(i, n); }
	Etype& etype(int i, int j) { return E[i][j]->type; }
	void bfs(int i,int& clock);//仅对单连通域有效，clock初始为0
};

int GraphMatrix::insert_v(int data)
{
	for (int j = 0; j < n; j++) E[j].push_back((Edge*)NULL);  //在当前矩阵的每一行尾都插入一个空的边
	n++;
	E.push_back(vector<Edge*>(n, (Edge*)NULL));  //在当前矩阵尾插入一行全为空的边
	Vertex temp(data);  //构造新节点
	V.push_back(temp);  //将新节点加入向量
	return V.size()-1;  //返回该节点编号
}

int GraphMatrix::remove_v(int i)
{
	for (int j = 0; j < n; j++){
		if (exists(i, j)) { //如果存在从第i个顶点到第j个顶点的边
			remove_e(i, j);  //删除该边
		}
	}
	E.erase(E.begin() + i); n--;   //删除当前矩阵中第i行空间，顶点数-1
	int temp = V[i].data; V.erase(V.begin() + i);//保存并删除向量中的第i个顶点
	for (int j = 0; j < n; j++)
	{
		if (exists(j,i)) {  //如果存在从第j个顶点到第i个顶点的边
			delete E[j][i];
			E[j][i] = (Edge*)NULL; e--;
			V[j].outdegree--;   //这两步与上面的同理
		}
		E[j].erase(E[j].begin() + i);   //删除当前行的第i个空间
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
	status(i) = discovered; Q.push(i);  //将第i个顶点的状态设置为被发现，然后入队
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();  //保存当前队列头的数据v然后pop
		dTime(v) = ++clock;  //dtime代表第几轮
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) //从v的第一个邻居顶点开始到最后一个
		{
			if (undiscovered == status(u))  //如果发现当前的邻居是没被发现的
			{
				status(u) = discovered; Q.push(u); //将其状态置为被发现的并入队
				etype(u, v) = tree; parent(u) = v; //因为当前的边算树里的一条边，所以置为tree。将该邻居的父亲设为v
			}
			else etype(u, v) = cross; //其他的情况（一种是邻居被发现了但还在队列中，一种是邻居是已经出了队列的）都置为跨边
		}
		status(v) = visited; 
	}
}