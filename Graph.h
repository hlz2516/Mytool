#pragma once
#include <graphics.h>
#include <math.h>
#include <vector>
#include <queue>
#include "Mytool.h"
#define MAX_CAPACITY 64
#define PI 3.141592654
//#define jt_rad 3 //箭头半径
//#define rad 40
//#define distance 10
typedef enum {undiscovered,discovered,visited} Vstatus;
typedef enum {undetermined,tree,cross,forward,backward} Etype;
struct Vertex;
//struct point {  //圆线上的点
//	int x; int y;
//	point(int _x,int _y):x(_x),y(_y) { }
//};
//point get_random_point(Vertex &v);
//bool exists(Vertex v, int x, int y);
//顶点类
struct Vertex {
	int data;//数据
	//int x, y; //坐标
	//int radius; //半径
	int indegree, outdegree; //入度和出度
	Vstatus status; //状态
	int dtime, ftime;
	int parent; //父亲
	Vertex(int _data = 0):data(_data),indegree(0),outdegree(0),
		status(undiscovered),dtime(-1),ftime(-1),parent(-1) {}
	//Vertex(int _x, int _y, int _data = 0);
	void setdata(int _data) {
		data = _data;
		/*char t[10]; TCHAR tchar[10];
		_gcvt_s(t, data, 3);
		CharToTchar(t, tchar);
		RECT r = { x - rad,y - rad,x + rad,y + rad };
		drawtext(tchar, &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);*/
	}
	//void set_status(Vstatus _status);
	//friend point get_random_point(Vertex &v);
	bool operator==(Vertex &v)
	{
		if (this->data == v.data && this->indegree == v.indegree &&
			this->outdegree == v.outdegree && this->parent == v.parent)
			return true;
		else return false;
	}
};

//Vertex::Vertex(int _x, int _y, double _data):x(_x),y(_y),data(_data),radius(rad),
//indegree(0),outdegree(0),status(undiscovered),dtime(-1),ftime(-1),parent(-1),priority(INT_MAX)
//{
//	setlinecolor(RED);
//	circle(x, y, rad);
//	char t[10]; TCHAR tchar[10];
//	_gcvt_s(t, data, 3);
//	CharToTchar(t, tchar);
//	RECT r = { x - rad,y - rad,x + rad,y + rad };
//	drawtext(tchar, &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
//}

//Vertex::Vertex(double _data):data(_data),radius(rad),indegree(0),outdegree(0), //随机在窗口里生成顶点
//status(undiscovered),dtime(-1),ftime(-1),parent(-1),priority(INT_MAX)
//{
//	start:x =rad + random(getwidth() - rad * 2);
//	y = rad + random(getheight() - rad * 2);
//	if (x < rad || y < rad) goto start;
//    //检查有无顶点重叠，并且控制了两个顶点之间的最小距离，distance越大最小距离越大
//	int cnt = 0, r = rad - 5;
//	while (cnt < distance)
//	{
//		for (int i = x - r; i <= x + r; i++)
//		{
//			double yfang = r * r - (x - i)*(x - i);
//			int y1 = y - sqrt(yfang), y2 = y + sqrt(yfang);
//			if (getpixel(i, y1) != getpixel(i, y2))
//				goto start;
//		}
//		r += 10;
//		cnt++;
//	}
//
//	setlinecolor(RED);
//	circle(x, y, rad);
//	char t[10]; TCHAR tchar[10];
//	_gcvt_s(t, data, 3);
//	CharToTchar(t, tchar);
//	RECT rect = { x - rad,y - rad,x + rad,y + rad };
//	drawtext(tchar, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
//}

//void Vertex::set_status(Vstatus _status)
//{
//	if (_status == visited)
//	{
//		setlinecolor(GREEN);
//		circle(x, y, rad);
//		status = visited;
//	}
//	else if (_status == discovered)
//	{
//		setlinecolor(YELLOW);
//		circle(x, y, rad);
//		status = discovered;
//	}
//	else if (_status == undiscovered)
//	{
//		setlinecolor(RED);
//		circle(x, y, rad);
//		status = undiscovered;
//	}
//}

struct Edge {
	int data;
	int weight;
	Etype type;
	Edge(int _data = 0, int _weight = 0):data(_data),weight(_weight),type(undetermined) { }
	//void set_status(Etype);
	//friend point get_random_point(Vertex &v);
};

//Edge::Edge(Vertex &_v1, Vertex &_v2, int _weight, double _data):v1(_v1),v2(_v2),weight(_weight),data(_data),type(undetermined)
//{
	//_v1.vp.push_back(get_random_point(_v1)); _v1.outdegree++;
	//_v2.vp.push_back(get_random_point(_v2)); _v2.indegree++;
	//POINT p1, p2;
	//p1.x = _v1.vp.back().x; p1.y = _v1.vp.back().y;
	//p2.x = _v2.vp.back().x; p2.y = _v2.vp.back().y;
	//setlinecolor(WHITE);
	//line(p1.x, p1.y, p2.x, p2.y);
	//setfillcolor(WHITE);
	//fillcircle(p2.x, p2.y, jt_rad);
	//	//字符处理及权重表示
	//char str[10]; itoa(weight, str, 10);
	//TCHAR _tchar[10];CharToTchar(str, _tchar);
	//RECT rect;
	//if (abs(p1.x - p2.x) < 5)
	//	rect = { p1.x,p1.y,p2.x + 10,p2.y };
	//else if (abs(p1.y - p2.y) <5)
	//	rect = { p1.x,p1.y,p2.x,p2.y + 10 };
	//else 
	//	rect = { p1.x,p1.y,p2.x,p2.y };
	//drawtext(_tchar, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//}

//void Edge::set_status(Etype _type)
//{//undetermined,tree,cross,forward,backward
//	if (_type == undetermined)
//	{
//		setlinecolor(WHITE);
//		type = undetermined;
//	}
//	else if (_type == tree)
//	{
//		setlinecolor(YELLOW);
//		type = tree;
//	}
//	else if (_type == cross)
//	{
//		setlinecolor(BLUE);
//		type = cross;
//	}
//	else if (_type == Etype::forward)
//	{
//		setlinecolor(CYAN);
//		type = Etype::forward;
//	}
//	else if (_type == backward)
//	{
//		setlinecolor(BROWN);
//		type = backward;
//	}
//}

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
	int insert_v(int data);  //插入顶点，返回编号
	int remove_v(int i);  //删除第i个顶点及其关联边
	void insert_e(int data, int weight, int i, int j); //插入权重为w，从顶点i到j的边
	int remove_e(int i, int j);
	void bfs(Vertex &v1);
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
//point get_random_point(Vertex &v)
//{
//	int x, y;
//	int i = 0;
//	x = v.x - rad + random(2 * rad);
//	int gene = random(2) ? 1 : -1;
//	y = v.y + gene * sqrt(rad*rad - (v.x - x)*(v.x - x));
//	if (v.vp.size() == 0)
//	{
//		point temp(x, y);
//		return temp;
//	}
//	else {
//		while (exists(v, x, y))
//		{
//			x = v.x - rad + random(2 * rad);
//			int gene = random(2) ? 1 : -1;
//			y = v.y + gene * sqrt(rad*rad - (v.x - x)*(v.x - x));
//		}
//		point temp(x, y);
//		return temp;
//	}
//}

//bool exists(Vertex v,int x, int y)//检验点是否存在重叠，如果重叠返回是
//{
//	for (int i = 0; i < v.vp.size(); i++)
//		if (x > v.vp[i].x-5 && x<v.vp[i].x+5 &&  y > v.vp[i].y -5 && y < v.vp[i].y + 5)
//			return true;
//	return false;
//}

void GraphMatrix::bfs(Vertex &v1)
{
	int index=0;
	for (int i = 0; i < n; i++)
		if (V[i].data == v1.data)
		{
			index = i;
			break;
		}

	queue<Vertex> Q;
	//v1.set_status(discovered); Q.push(v1);
	while (!Q.empty())
	{
		Vertex v = Q.front();
		Q.pop();
		for (int i = 0; i < n; i++)
			if (V[i].data == v.data)
			{
				index = i;
				break;
			}

		for(int i=0;i<V.size();i++)
			if (E[index][i] != NULL)
			{
				if (V[i].status == undiscovered)
				{
					//V[i].set_status(discovered);
					Q.push(V[i]);
					//E[index][i]->set_status(tree);
					//V[i].parent =index;
				}
				else
				{
					//E[index][i]->set_status(cross);
				}
				Sleep(1000);
			}
		//v.set_status(visited);
	}
}