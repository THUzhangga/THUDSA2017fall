/******************************************************************************************
* Data Structures in C++
* ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
* Junhui DENG, deng@tsinghua.edu.cn
* Computer Science & Technology, Tsinghua University
* Copyright (c) 2006-2013. All rights reserved.
******************************************************************************************/

#pragma once
#include <cstring>
#include "vector.h" //引入向量
#include "stack.h"
#include "release.h"
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)

template <typename Tv> struct Vertex { //顶点对象（为简化起见，并未严格封装）
	Tv data; int inDegree, outDegree;
	Vertex(Tv const& d = (Tv)0) : //构造新顶点
		data(d), inDegree(0), outDegree(0){} //暂不考虑权重溢出
};

template <typename Te> struct Edge { //边对象（为简化起见，并未严格封装）
	Te data; int weight;
	Edge(Te const& d, int w) : data(d), weight(w) {} //构造
};


template <typename Tv, typename Te> //顶点类型、边类型
class GraphMatrix { //基于向量，以邻接矩阵形式实现的图
private:
	Vector< Vertex< Tv > > V; //顶点集（向量）
	Vector< Vector< Edge< Te > * > > E; //边集（邻接矩阵）
public:
	GraphMatrix() { n = e = 0; } //构造
	~GraphMatrix() { //析构
		for (int j = 0; j < n; j++) //所有动态创建的
			for (int k = 0; k < n; k++) //边记录
				delete E[j][k]; //逐条清除
	}
	int n;
	// 顶点的基本操作：查询第i个顶点（0 <= i < n）
	Tv& vertex(int i) { return V[i].data; } //数据
	int inDegree(int i) { return V[i].inDegree; } //入度
	int outDegree(int i) { return V[i].outDegree; } //出度
	int firstNbr(int i) { return nextNbr(i, n); } //首个邻接顶点
	int nextNbr(int i, int j) //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
	{
		while ((-1 < j) && (!exists(i, --j))); return j;
	} //逆向线性试探

	int lastNbr(int i) { return nextNbrClock(i, -1); }
	int nextNbrClock(int i, int j)
	{
		while (j < n && !exists(i, ++j)); return j;
	}

	int firstInvNbr(int i) { return nextInvNbr(i, n); } //首个邻接顶点
	int nextInvNbr(int i, int j)
	{
		while ((-1 < j) && (!exists(--j, i))); return j;
	}

	int e; //边总数
		   // 顶点的动态操作
	int insert(Tv const& vertex) { //插入顶点，返回编号
		for (int j = 0; j < n; j++) E[j].insert(NULL); n++; //各顶点预留一条潜在的关联边
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL)); //创建新顶点对应的边向量
		return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
	}
	Tv remove(int i) { //删除第i个顶点及其关联边（0 <= i < n）
		for (int j = 0; j < n; j++) //所有出边
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; } //逐条删除
		E.remove(i); n--; //删除第i行
		Tv vBak = vertex(i); V.remove(i); //删除顶点i
		for (int j = 0; j < n; j++) //所有入边
			if (Edge<Te> * e = E[j].remove(i)) { delete e; V[j].outDegree--; } //逐条删除
		return vBak; //返回被删除顶点的信息
	}
	// 边的确认操作
	bool exists(int i, int j) //边(i, j)是否存在
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	// 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
	Te& edge(int i, int j) { return E[i][j]->data; } //边(i, j)的数据
	int& weight(int i, int j) { return E[i][j]->weight; } //边(i, j)的权重
														  // 边的动态操作
	void insert(Te const& edge, int w, int i, int j) { //插入权重为w的边e = (i, j)
		if (exists(i, j) && E[i][j]->weight >= w) return;
		else if (exists(i, j) && E[i][j]->weight < w) { E[i][j]->weight = w; return; }
		E[i][j] = new Edge<Te>(edge, w); //创建新边
		e++; V[i].outDegree++; V[j].inDegree++; //更新边计数与关联顶点的度数
												//printf("%d %d\n", E[i][j]->data, E[i][j]->weight);
	}
	Te remove(int i, int j) { //删除顶点i和j之间的联边（exists(i, j)）
		Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL; //备份后删除边记录
		e--; V[i].outDegree--; V[j].inDegree--; //更新边计数与关联顶点的度数
		return eBak; //返回被删除边的信息
	}

	void printedge() {
		for (int j = 0; j < n; j++) //所有动态创建的
			for (int k = 0; k < n; k++) //边记录
				printf("%d %d", E[j][k]->data, E[j][k]->weight);
	}

	void printedge(int i, int j) {
		printf("%d %d", E[i][j]->data, E[i][j]->weight);
	}
	void printvertex() {
		for (int j = 0; j < n; j++) //所有动态创建的
			printf("%d ", V[j].data);
	}
	void longestPath(); //最长路径
	void longestValue(Stack<Tv> &ts);
	Stack<Tv>* tSort(int); //基于DFS的拓扑排序算法
	void gatSort(Stack<Tv> &); //玍哥的拓扑排序
};

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::gatSort(Stack<Tv>& ts)
{
	Stack<Tv> ad; //辅助栈，用于储存入度为0的结点
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0)
			ad.push(i);
	while (!ad.empty())
	{
		Tv v = ad.pop();
		ts.push(vertex(v));
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //枚举v的所有邻居u
			if (--V[u].inDegree == 0)
				ad.push(u);
	}
}


template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::longestPath()
{
	Vector<int> In; //用于储存能产生当前全局最长路径的入度为0的点
	Vector<int> D;//用于储存能当前全局最长路径
	Vector<int> Out;//用于储存能产生全局最长路径的出度为0的点
	Stack<Tv> ts;
	gatSort(ts);
	int DIST_MAX = INT_MIN; //当前全局最长路径的值
	int *DIST;
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0) //对于入度为0的点，进行路径长度计算
		{
			int *dist = new int[n];
			int out; //out用于临时储存从本次入度为0的点所能到达的终点
			for (int i = 0; i < n; i++)
				dist[i] = INT_MIN; //所有距离初始化为负无穷大
								   //起始点距离初始化为0
			dist[i] = 0; //结点i的dist为0
						 //在拓扑排序结果中先找到入度为0的点
			ListNodePosi(Tv) cursor = ts->last();
			for (int j = 0; j < n; j++)
				if (vertex(i) == cursor->data)
					break;
			//不断往下计算最长距离
			while (cursor->pred != NULL)
			{
				int v = cursor->data - 1;
				for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
					if (dist[v] + weight(v, u) > dist[u])  dist[u] = dist[v] + weight(v, u);
				cursor = cursor->pred;
			}
			int dist_max = INT_MIN; //最大距离初始化为负无穷大
			for (int i = 0; i < n; i++)
				if (dist[i] > dist_max)
				{
					dist_max = dist[i];
					out = i;
				}
			if (dist_max >= DIST_MAX)
			{
				DIST_MAX = dist_max;
				DIST = dist;
				In.insert(i); D.insert(dist_max); Out.insert(out);
			}
		}

	int v = n; //全局最长路径对应的结点的最小编号
	int flag;
	for (int i = 0; i < In.size(); i++)
	{
		if (D[i] == DIST_MAX && In[i] <= v)
		{
			v = In[i];
			flag = i;
		}
	}
	int *DISTINV;
	for (int i = 0; i < Out.size(); i++)
	{
		if (In[i] == v)
		{
			int out = Out[i];
			int *distInv = new int[n];
			for (int i = 0; i < n; i++)
				distInv[i] = INT_MAX; //所有距离初始化为正无穷大
									  //起始点距离初始化为0
			distInv[out] = DIST_MAX;
			//在拓扑排序结果中先找到out
			ListNodePosi(Tv) cursor = ts->first();
			while (cursor->succ != NULL)
			{
				if (cursor->data == vertex(out)) break;
				cursor = cursor->succ;
			}
			//不断往上更新距离（取小者）
			while (cursor->succ != NULL)
			{
				int v = cursor->data - 1;
				for (int u = firstInvNbr(v); -1 < u; u = nextInvNbr(v, u))
					if (distInv[v] - weight(u, v) < distInv[u])  distInv[u] = distInv[v] - weight(u, v);
				cursor = cursor->succ;
			}
			for (int j = 0; j < n; j++)
			{
				if (distInv[j] == 0)
					DISTINV = distInv;
			}
		}
	}
	for (int i = 0; i < Out.size(); i++)
	{
		if (In[i] == v)
		{
			printf("%d ", vertex(v));
			int now = v;
			while (V[now].outDegree != 0)
			{
				for (int u = lastNbr(now); u < n; u = nextNbrClock(now, u))
				{
					if (DIST[u] == DISTINV[u])
					{
						now = u; printf("%d ", vertex(u));
					}
				}
			}
		}
	}
}

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::longestValue(Stack<Tv> &ts)
{
	gatSort(ts);
	int DIST_MAX = INT_MIN; //当前全局最长路径的值
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0) //对于入度为0的点，进行路径长度计算
		{
			int *dist = new int[n];
			int out; //out用于临时储存从本次入度为0的点所能到达的终点
			memset(dist, 0, sizeof(int)*n);
			//for (int i = 0; i < n; i++)
			//	dist[i] = INT_MIN; //所有距离初始化为负无穷大
			//					   //起始点距离初始化为0
			//dist[i] = 0; //结点i的dist为0
			//			 //在拓扑排序结果中先找到入度为0的点
			ListNodePosi(Tv) cursor = ts.first();
			while (cursor->succ != NULL)
			{
				if (cursor->data == vertex(i)) break;
				cursor = cursor->succ;
			}
			//不断往下计算最长距离
			while (cursor->succ != NULL)
			{
				int v = cursor->data - 1;
				for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
					if (dist[v] + weight(v, u) > dist[u])  dist[u] = dist[v] + weight(v, u);
				cursor = cursor->succ;
			}
			int dist_max = INT_MIN; //最大距离初始化为负无穷大
			for (int i = 0; i < n; i++)
				if (dist[i] > dist_max)
				{
					dist_max = dist[i];
					out = i;
				}
			if (dist_max >= DIST_MAX)
			{
				DIST_MAX = dist_max;
			}
		}
	printf("%d", DIST_MAX);
	return;
}