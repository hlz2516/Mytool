#pragma once
#include <graphics.h>
#include <math.h>
#include <vector>
#include <queue>
#include "Mytool.h"
#define MAX_CAPACITY 64
#define PI 3.141592654
//#define jt_rad 3 //��ͷ�뾶
//#define rad 40
//#define distance 10
typedef enum {undiscovered,discovered,visited} Vstatus;
typedef enum {undetermined,tree,cross,forward,backward} Etype;
struct Vertex;
//struct point {  //Բ���ϵĵ�
//	int x; int y;
//	point(int _x,int _y):x(_x),y(_y) { }
//};
//point get_random_point(Vertex &v);
//bool exists(Vertex v, int x, int y);
//������
struct Vertex {
	int data;//����
	//int x, y; //����
	//int radius; //�뾶
	int indegree, outdegree; //��Ⱥͳ���
	Vstatus status; //״̬
	int dtime, ftime;
	int parent; //����
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

//Vertex::Vertex(double _data):data(_data),radius(rad),indegree(0),outdegree(0), //����ڴ��������ɶ���
//status(undiscovered),dtime(-1),ftime(-1),parent(-1),priority(INT_MAX)
//{
//	start:x =rad + random(getwidth() - rad * 2);
//	y = rad + random(getheight() - rad * 2);
//	if (x < rad || y < rad) goto start;
//    //������޶����ص������ҿ�������������֮�����С���룬distanceԽ����С����Խ��
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
	//	//�ַ�����Ȩ�ر�ʾ
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
	int insert_v(int data);  //���붥�㣬���ر��
	int remove_v(int i);  //ɾ����i�����㼰�������
	void insert_e(int data, int weight, int i, int j); //����Ȩ��Ϊw���Ӷ���i��j�ı�
	int remove_e(int i, int j);
	void bfs(Vertex &v1);
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

//bool exists(Vertex v,int x, int y)//������Ƿ�����ص�������ص�������
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