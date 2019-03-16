#pragma once
#pragma once
#include <iostream>
#include "vector.h" //引入向量
#include "list.h"
#include "stack.h"
#include <cstring>
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)
//INT_MIN
struct Edge { //边对象（为简化起见，并未严格封装
	int data;
	int weight;
	int next; //边的下一个顶点
	Edge(int const& d, int w, int n) : data(d), weight(w), next(n) {}
};


struct Vertex { //顶点对象（为简化起见，并未严格封装
	int data; int inDegree, outDegree; //数据、出入度数
	List<Edge *> E;
	Vertex(int const& d = (int)0) : //构造新顶点
		data(d), inDegree(0), outDegree(0), E() {} //暂不考虑权重溢出
};

struct path
{
	int in, d, out;
	path() : in(NULL), d(NULL), out(NULL) {}
	path(int i, int d, int o) :
		in(i), d(d), out(o) {}
};

class GraphList { //基于向量，以邻接表形式实现的图
private:
	Vector< Vertex> V; //顶点集（向量）
public:
	int n; //顶点数
	int e; //边数
	GraphList() { n = e = 0; }
	~GraphList() { //析构
		for (int i = 0; i < n; i++)
		{
			V[i].E.Outclear();
		}
	}
	// 顶点的基本操作：查询第i个顶点（0 <= i < n)
	int& vertex(int i) { return V[i].data; } //数据
	int inDegree(int i) { return V[i].inDegree; } //入度
	int outDegree(int i) { return V[i].outDegree; } //出度
													// 顶点的动态操作
	int insert(int const& vertex) { //插入顶点，返回编号
		n++;
		return V.insert(Vertex(vertex)); //顶点向量增加一个顶点
	}
	// 边的动态操作
	void insert(int const& edge, int w, int i, int j)
	{ //插入权重为w的边e = (i, j)
		ListNodePosi(Edge*) cursor = V[i].E.first();
		bool flag = false;//True: （i,j）存在
		while (cursor->succ != NULL)
		{
			if (cursor->data->next == j)
			{
				flag = true; //找到这条边了
				if (cursor->data->weight < w)
					cursor->data->weight = w; //如果边的权重要小，则更新之
				break; //退出
			}
			cursor = cursor->succ;
		}
		if (!flag) //如果没有找到
		{
			Edge * ei = new Edge(edge, w, j);
			V[i].E.insertAsLast(ei);
			e++; V[i].outDegree++; V[j].inDegree++; //更新边计数与关联顶点度数
		}
	}
	void print()
	{
		for (int i = 0; i < n; i++)
		{
			printf("data=%d \n", V[i].data);
			ListNodePosi(Edge*) cursor = V[i].E.first();
			while (cursor->succ != NULL)
			{
				printf("linked %d", vertex(cursor->data->next));
				cursor = cursor->succ;
			}
			printf("\n");
		}
	}

	Stack<int>* gatSort(Stack<int> &zeroIn);
	int longestValue();
	void longestPath();
};
Stack<int>* GraphList::gatSort(Stack<int> &zeroIn) //玍哥的拓扑排序算法
{
	Stack<int> *ts = new Stack<int>;
	Stack<int> ad;
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0)
		{
			ad.push(i);
			zeroIn.push(i);
		}
	while (!ad.empty())
	{
		int v = ad.pop();
		ts->push(vertex(v));
		ListNodePosi(Edge *) cursor = V[v].E.first();
		while (cursor->succ != NULL)
		{
			if (--V[cursor->data->next].inDegree == 0)
				ad.push(cursor->data->next);
			cursor = cursor->succ;
		}
	}
	return ts;
}

int GraphList::longestValue()
{
	Stack<int> zeroIn; //存储初始状态时所有入度为0的点
	Stack<int>* ts = gatSort(zeroIn);
	//zeroIn.print();
	//ts->print();
	int DIST_MAX = INT_MIN;
	while (!zeroIn.empty())
	{
		int v = zeroIn.pop();
		int *dist = new int[n];
		memset(dist, -1, sizeof(int)*n);
		dist[v] = 0;
		ListNodePosi(int) cursor = ts->first();

		//Move cursor to the vertex whose inDegree is 0
		while (cursor->succ != NULL)
		{
			if (cursor->data == vertex(v))
				break;
			cursor = cursor->succ;
		}

		while (cursor->succ != NULL)
		{
			int vet = cursor->data - 1;
			ListNodePosi(Edge *) edgeCursor = V[vet].E.first();
			while(edgeCursor->succ!=NULL)
			{
				int weight = edgeCursor->data->weight;
				int next = edgeCursor->data->next;
				if (dist[vet] + weight > dist[next])  
					dist[next] = dist[vet] + weight;
				edgeCursor = edgeCursor->succ;
			}
			cursor = cursor->succ;
		}
		int dist_max = INT_MIN;
		for (int i = 0; i < n; i++)
			if (dist[i] > dist_max)
				dist_max = dist[i];
		if (dist_max >= DIST_MAX)
			DIST_MAX = dist_max;
	}
	printf("%d", DIST_MAX);
	return DIST_MAX;
}