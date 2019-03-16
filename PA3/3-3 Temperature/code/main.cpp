#include <iostream>
//#include "AVL.h"
#include "Data.h"
#include "binnode.h"
#include "bintree.h"
#include "stack.h"
#include "temperature.h"
int n;
void cycle() //大的循环用于在oj里测试，加入后比较运行时间
{
	long long ha = 0;//蛤的寿命
	for (int i = 0;i < 100000;i++)
		for (int j = 0;j < 100000;j++)
			ha++;
}

int main()
{
	//int* temp, *temp1;
	//temp = new int[3 * n];
	//temp1 = temp;
	//for (int i = 0; i < n; i++) {
	//	GetStationInfo(i, temp1, temp1 + 1, temp1 + 2);
	//	temp1 += 3;
	//}
	//temp1 = temp;
	//for (int i = 0; i < n; i++) {
	//	TP[i].x = temp1[0];
	//	TP[i].y = temp1[1];
	//	TP[i].t = temp1[2];
	//	temp1 += 3;
	//}
	//delete[] temp;

	//n = GetNumOfStation();
	//for (int i = 0; i < n;i++)
	//	GetStationInfo(i, &TP[i].x, &TP[i].y, &TP[i].t);
	//quicksort_x(0, n - 1, TP);
	//Vector<int> X;
	//Vector<int> begin;
	//Vector<int> end;
	//findSameX(0, n - 1, X, begin, end, TP);
	//BinTree<int> tr;
	//BinNodePosi(int) x = tr.getroot();
	//RangeBuild(tr, x, 0, X.size() - 1, X, begin, end);
	//int state;
	//int lo_x, lo_y, hi_x, hi_y;
	//int queryResult;
	//x = tr.getroot();
	//do {
	//	state = GetQuery(&lo_x, &lo_y, &hi_x, &hi_y);
	//	queryResult = Query(tr, x, lo_x, hi_x, lo_y, hi_x);
	//	//re = /*(count == 0) ? 0 : */
	//	// 计算 [x1, y1]-[x2, y2]范围内温度平均值, 存储到queryResult
	//	//printf("%d \n", queryResult);
	//	Response(queryResult);
	//} while (state);


//#ifndef _OJ_
//	freopen("input50000.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//#endif
//	int m;
//	scanf("%d %d", &n, &m);
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d %d %d", &TP[i].x, &TP[i].y, &TP[i].t);
//	}
//	quicksort_x(0, n - 1, TP);
//	//for (int i = 0; i < n; i++)
//	//	printf("%d %d %d", TP[i].x, TP[i].y, TP[i].t);
//	Vector<int> X;
//	Vector<int> begin;
//	Vector<int> end;
//	findSameX(0, n - 1, X, begin, end, TP);
//	BinTree<int> tr;
//	BinNodePosi(int) x = tr.getroot();
//	RangeBuild(tr, x, 0, X.size() - 1, X, begin, end);
//	x = tr.getroot();
//	long long sum_t = 0;
//	int count = 0;
//	Query(tr, x, 2000, 15000, 13000, 40000);
//	return 0;

	int state;
	n = GetNumOfStation();
	int* temp, *temp1;
	temp = new int[3 * n];
	temp1 = temp;
	for (int i = 0; i < n; i++) {
		GetStationInfo(i, temp1, temp1 + 1, temp1 + 2);
		temp1 += 3;
	}

	temp1 = temp;

	for (int i = 0; i < n; i++) {
		TP[i].x = temp1[0];
		TP[i].y = temp1[1];
		TP[i].t = temp1[2];
		temp1 += 3;
	}
	delete[] temp;
	quicksort_x(0, n - 1, TP);
	Vector<int> X;
	Vector<int> begin;
	Vector<int> end;
	findSameX(0, n - 1, X, begin, end, TP);
	BinTree<int> tr;
	BinNodePosi(int) x = tr.getroot();
	RangeBuild(tr, x, 0, X.size() - 1, X, begin, end);

	int x1, x2, y1, y2;
	int QueryResult = 0;
	do {
		state = GetQuery(&x1, &y1, &x2, &y2);
		QueryResult = Query(tr, x1, x2, y1, y2);
		Response(QueryResult);
	} while (state);
}