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

struct InvEdge
{
	int data;
	int weight;
	int before; //边的下一个顶点
	InvEdge(int const& d, int w, int b) : data(d), weight(w), before(b) {}
};


struct Vertex { //顶点对象（为简化起见，并未严格封装
	int data; int inDegree, outDegree; //数据、出入度数
	List<Edge *> E;
	List<InvEdge *> IE;
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
	GraphList(){n = e = 0;} 
	~GraphList() { //析构
		for (int i = 0; i < n; i++)
		{
			V[i].E.Outclear();
			V[i].IE.Outclear();
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
			InvEdge * ie = new InvEdge(edge, w, i); //相应地，再j的反向边表中插入一条反边
			V[j].IE.insertAsLast(ie);
		}

		if (flag) //找到这条边了，说明反边中也存在这条边，我们可能也需要更新它。
		{
			ListNodePosi(InvEdge*) cursor = V[j].IE.first();
			while (cursor->succ != NULL)
			{
				if (cursor->data->before == i)
				{
					if (cursor->data->weight < w)
						cursor->data->weight = w; //如果边的权重要小，则更新之
					return; //返回
				}
				cursor = cursor->succ;
			}
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
			ListNodePosi(InvEdge*) invcursor = V[i].IE.first();
			while (invcursor->succ != NULL)
			{
				printf("Inverse linked %d", vertex(invcursor->data->before));
				invcursor = invcursor->succ;
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
	//while (!zeroIn.empty())
	//{
	//	int v = zeroIn.pop();
	//	int *dist = new int[n];
	//	memset(dist, -1, sizeof(int)*n);
	//	dist[v] = 0;
	//	ListNodePosi(int) cursor = ts->first();

	//	//Move cursor to the vertex whose inDegree is 0
	//	while (cursor->succ != NULL)
	//	{
	//		if (cursor->data == vertex(v))
	//			break;
	//		cursor = cursor->succ;
	//	}

	//	while (cursor->succ != NULL)
	//	{
	//		int vet = cursor->data - 1;
	//		ListNodePosi(Edge *) edgeCursor = V[vet].E.first();
	//		while(edgeCursor->succ!=NULL)
	//		{
	//			int weight = edgeCursor->data->weight;
	//			int next = edgeCursor->data->next;
	//			if (dist[vet] + weight > dist[next])  
	//				dist[next] = dist[vet] + weight;
	//			edgeCursor = edgeCursor->succ;
	//		}
	//		cursor = cursor->succ;
	//	}
	//	int dist_max = INT_MIN;
	//	for (int i = 0; i < n; i++)
	//		if (dist[i] > dist_max)
	//			dist_max = dist[i];
	//	if (dist_max >= DIST_MAX)
	//		DIST_MAX = dist_max;
	//}
	DIST_MAX = 0;
	printf("%d", DIST_MAX);
	return DIST_MAX;
}

void GraphList::longestPath()
{
	Stack<int> zeroIn;
	Stack<int>* ts = gatSort(zeroIn);
	//zeroIn.print();
	//ts->print();
	Stack<path> P;
	int DIST_MAX = INT_MIN;
	int *DIST;
	//注意，在zeroIn中零入度的点是字典序小的先入栈
	//而我们在更新DIST时是零入度字典序大的先弹出
	//因此最后的DIST一定是在能达到最长路径的零入度点中字典序最小的距离数组
	while (!zeroIn.empty())
	{
		int v = zeroIn.pop();
		int out; //储存从这个入度为0的点所能到达的最长路径的点
		int *dist = new int[n];
		//储存从这个入度为0的点到各个顶点的距离。如果不能到达则是负数，如果能到达则是最大距离。
		//dits[i]表示到顶点i的最长距离。
		memset(dist, -1, sizeof(int)*n); //初始化为-1
		dist[v] = 0;
		int dist_max = -1;
		ListNodePosi(int) cursor = ts->first();

		//将光标移到入度为0的点v
		while (cursor->succ != NULL)
		{
			if (cursor->data == vertex(v))
				break;
			cursor = cursor->succ;
		}

		//从cursor所在点出发不断向下计算dist
		while (cursor->succ != NULL)
		{
			int vet = cursor->data - 1;
			ListNodePosi(Edge *) edgeCursor = V[vet].E.first();
			while (edgeCursor->succ != NULL)
			{
				int weight = edgeCursor->data->weight;
				int next = edgeCursor->data->next;
				if (dist[vet] + weight > dist[next])
				{
					dist[next] = dist[vet] + weight;
					if (dist[next] > dist_max)
						dist_max = dist[next];
				}
				edgeCursor = edgeCursor->succ;
			}
			cursor = cursor->succ;
		}

		if (dist_max >= DIST_MAX) //如果大于等于当前最大距离，存下来入口v，最大距离dist_max以及出口
		{
			DIST_MAX = dist_max;
			DIST = dist;
			for (int i = 0; i < n; i++)
				//遍历距离数组，找到最大值，该值的rank即为当前入度为0点所能到达的最长距离dist_max及其rank i
		//有可能v有两条最长路径，但是这里我们先只需要最长路径的值
				if (dist[i] == dist_max)
					P.push(path(v, dist_max, i));
		}
	}
	//printf("DIST_MAX=%d\n", DIST_MAX);
	//printf("DIST\n");
	//for (int i = 0;i < n;i++)
	//	printf("%d ", DIST[i]);
	//printf("\n");
	ListNodePosi(path) path_cursor = P.first();
	int minZeroIn = n;//在P中找到距离最长且序号最小的0零入度顶点
	while (path_cursor->succ != NULL)
	{
		if (minZeroIn > path_cursor->data.in && path_cursor->data.d == DIST_MAX)
			minZeroIn = path_cursor->data.in;
		path_cursor = path_cursor->succ;
	}
	//printf("minZeroIn=%d\n", minZeroIn);


	//ListNodePosi(int) cursor = ts->first();
	//while (cursor->succ != NULL)
	//{
	//	if (cursor->data == vertex(minZeroIn)) break;
	//	cursor = cursor->succ;
	//}

	//while (cursor->succ != NULL)
	//{
	//	int vet = cursor->data - 1;
	//	ListNodePosi(Edge *) edgeCursor = V[vet].E.first();
	int *DISTINV; //反向距离数组
	path_cursor = P.first();
	Vector<int> longestpath;
	while (path_cursor->succ != NULL)
	{
		if (minZeroIn == path_cursor->data.in)
		{
			int out = path_cursor->data.out;
			Vector<int> path;
			int *distInv = new int[n];
			for (int i = 0;i < n;i++)
				distInv[i] = 100000000;
			//memset(distInv, 100000000, sizeof(int) * n);//总共最多100,000个点，差价不超过1,000，因此最大距离小于100,000,000
			distInv[out] = DIST_MAX;//起始点距离初始化为DIST_MAX
			int dist_min = 100000000;
			//for (int i = 0;i < n;i++)
			//	printf("distInv=%d\n", distInv[i]);
			ListNodePosi(int) cursor = ts->first();
			while (cursor->succ != NULL)//在拓扑排序结果中先找到out
			{
				if (cursor->data == vertex(out)) break;
				cursor = cursor->succ;
			}
			//start = cursor;
			//不断往回更新距离
			while (cursor->pred != NULL)
			{
				int v = cursor->data - 1;
				ListNodePosi(InvEdge *) invEdgeCursor = V[v].IE.first();
				while (invEdgeCursor->succ != NULL)
				{
					int weight = invEdgeCursor->data->weight;
					int before = invEdgeCursor->data->before; //上一个点
					if (distInv[v] - weight < distInv[before])
					{
						distInv[before] = distInv[v] - weight;
						if (distInv[before] < dist_min)
							dist_min = distInv[before];
					}
					invEdgeCursor = invEdgeCursor->succ;
				}
				cursor = cursor->pred;
			}
			
			if (dist_min == 0)
			{
				DISTINV = distInv;
				//printf("have 0: out = %d\n", out);
				//for (int i = 0;i < n;i++)
				//	printf("vertex=%d distinv=%d\n", vertex(i), distInv[i]);
			}
			//接下来，从入度为0的点出发，凡是DIST等于DISTINV的都在最长路径上
			cursor = ts->first();
			while (cursor->succ != NULL)
			{
				if (cursor->data == vertex(minZeroIn)) break;
				cursor = cursor->succ;
			}
			//printf("The longest path: \n");
			int level = 0;
			while (cursor->succ != NULL)
			{
				if (DIST[cursor->data - 1] == DISTINV[cursor->data - 1])
				{
					//printf("%d ", cursor->data);
					path.insert(cursor->data);
				}
				cursor = cursor->succ;
			}

			if (longestpath.empty())
				longestpath = path;
			else
			{
				int msize = longestpath.size() < path.size() ? longestpath.size() : path.size();
				int i = 0;
				while (i < msize)
				{
					if (longestpath[i] > path[i])
						break;
					i++;
				}
				if (i < msize)
					longestpath = path;
			}
		}
		path_cursor = path_cursor->succ;
	}
	longestpath.print();
}