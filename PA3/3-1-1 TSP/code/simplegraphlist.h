/******************************************************************************************
* Data Structures in C++
* ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
* Junhui DENG, deng@tsinghua.edu.cn
* Computer Science & Technology, Tsinghua University
* Copyright (c) 2006-2013. All rights reserved.
******************************************************************************************/

#pragma once
#include <iostream>
#include "vector.h" //引入向量
#include "list.h"
#include "stack.h"
#define INT_MAX 2147483647
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状�?
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型

struct Edge { //边对象（为简化起见，并未严格封装�?
	int data; int weight; EType type; //数据、权重、类�?
	int next; //边的下一个顶�?
	Edge(int const& d, int w, int n) : data(d), weight(w), type(UNDETERMINED), next(n) {} //构�?
};

struct Vertex { //顶点对象（为简化起见，并未严格封装�?
	int data; int inDegree, outDegree; VStatus status; //数据、出入度数、状�?
	int dTime, fTime; //时间标签
	int parent; int priority; //在遍历树中的父节点、优先级�?
	List<Edge *> E;
	Vertex(int const& d = (int)0) : //构造新顶点
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX), E() {} //暂不考虑权重溢出
};

class GraphList{ //基于向量，以邻接表形式实现的�?
private:
	Vector< Vertex> V; //顶点集（向量�?
public:
	int n; //顶点�?
	int e; //边数
	GraphList()
	{
		n = e = 0;
	} //构�?
	~GraphList() { //析构
		for (int i = 0; i < n; i++)
		{
			V[i].E.~List();
			/*ListNodePosi(Edge*) cursor = V[i].E.first();
			while(cursor->succ->succ!=NULL)*/
		}
	}
	// 顶点的基本操作：查询第i个顶点（0 <= i < n�?
	int& vertex(int i) { return V[i].data; } //数据
	int inDegree(int i) { return V[i].inDegree; } //入度
	int outDegree(int i) { return V[i].outDegree; } //出度

	int firstNbr(int i) { return V[i].E.first()->data->next; } //首个邻接顶点
	int nextNbr(int i, int j) //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
	{
		ListNodePosi(Edge*) cursor = V[i].E.first();
		while (cursor->succ->succ != NULL)
		{
			if (cursor->data->next == j)
				return cursor->succ->data->next;
			cursor = cursor->succ;
		}
	} //逆向线性试�?

	VStatus& status(int i) { return V[i].status; } //状�?
	int& dTime(int i) { return V[i].dTime; } //时间标签dTime
	int& fTime(int i) { return V[i].fTime; } //时间标签fTime
	int& parent(int i) { return V[i].parent; } //在遍历树中的父亲
	int& priority(int i) { return V[i].priority; } //在遍历树中的优先级数
														   // 顶点的动态操�?
	int insert(int const& vertex) { //插入顶点，返回编�?
		printf("insert\n");
		n++;
		return V.insert(Vertex(vertex)); //顶点向量增加一个顶�?
	}
	/*int remove(int i) { //删除第i个顶点及其关联边�? <= i < n�?
		ListNodePosi(Edge*) cursor = V[i].E.first();
		while (cursor->succ->succ != NULL)
		{
			V[cursor->data->next].inDegree--;
			cursor = cursor->succ;
		}
		V[i].E.~List();
		//E[i];
		//V[i].E.remove(i);
		n--;
		int vBak = vertex(i); V.remove(i); //删除顶点i
		for (int j = 0; j < n; j++) //所有入�?
		{
			ListNodePosi(Edge*) cursor = V[j].E.first();
			while (cursor->succ->succ != NULL)
			{
				if (cursor->data->next == i)
				{
					V[j].E.remove(cursor);
					delete cursor->data;
					V[j].outDegree--;
				}
			}
		}
		return vBak; //返回被删除顶点的信息
	}*/
	// 边的确认操作
	bool exists(int i, int j) //�?i, j)是否存在
	{
		if ((0 <= i) && (i < n))
		{
			ListNodePosi(Edge*) cursor = V[i].E.first();
			while (cursor->succ->succ != NULL)
			{
				if (cursor->data->next == j)
					return true;
				cursor = cursor->succ;
			}
		}
		return false;
	}
	// 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)�?
	EType & type(int i, int j)
	{
		if ((0 <= i) && (i < n))
		{
			ListNodePosi(Edge*) cursor = V[i].E.first();
			while (cursor->succ->succ != NULL)
			{
				if (cursor->data->next == j)
					return cursor->data->type;
				cursor = cursor->succ;
			}
		}
	} //�?i, j)的类�?
	int& edge(int i, int j)
	{
		if ((0 <= i) && (i < n))
		{
			ListNodePosi(Edge*) cursor = V[i].E.first();
			while (cursor->succ->succ != NULL)
			{
				if (cursor->data->next == j)
					return cursor->data->data;
				cursor = cursor->succ;
			}
		}
	} //�?i, j)的数�?
	int& weight(int i, int j)
	{
		if ((0 <= i) && (i < n))
		{
			ListNodePosi(Edge*) cursor = V[i].E.first();
			while (cursor->succ->succ != NULL)
			{
				if (cursor->data->next == j)
					return cursor->data->weight;
				cursor = cursor->succ;
			}
		}
	} //�?i, j)的权�?
	  // 边的动态操�?
	void insert(int const& edge, int w, int i, int j) { //插入权重为w的边e = (i, j)
		ListNodePosi(Edge*) cursor = V[i].E.first();
		while (cursor->succ->succ != NULL)
		{
			if (cursor->data->next == j)
				return; //边存在，返回
			cursor = cursor->succ;
		}
		Edge * ei = new Edge(edge, w, j);
		V[i].E.insertAsLast(ei);
		e++; V[i].outDegree++; V[j].inDegree++; //更新边计数与关联顶点的度�?
	}
	/*
	int remove(int i, int j) {
		int eBak = edge(i, j);
		ListNodePosi(Edge*) cursor = V[i].E.first();
		while (cursor->succ->succ != NULL)
		{
			if (cursor->data->next == j)
			{
				V[i].E.remove(cursor);
				e--; V[i].outDegree--; V[j].inDegree--; //更新边计数与关联顶点的度�?
				return eBak; //返回被删除边的信�?
			}
			cursor = cursor->succ;
		}
	}
	*/
};