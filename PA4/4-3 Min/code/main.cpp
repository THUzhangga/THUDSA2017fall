#include <iostream>
//#include "pq_min.h"
#include "pq.h"
#define MAXK 50000
#define maxarray 50000 //本程序最大开500000的数组

int main()
{
	int n, k;
	fread(&n, sizeof(int), 1, stdin);
	fread(&k, sizeof(int), 1, stdin);
	int *A = new int[k];
	fread(A, sizeof(int), k, stdin);
	PQ_ComplHeap<int> pq;
	for (int i = 0; i < k; i++)
		pq.insert(A[i]);
	delete[] A;
	int remain = n - k; //剩余数的个数
	while (remain > maxarray)
	{
		int *data = new int[maxarray];
		fread(data, sizeof(int), maxarray, stdin);
		for (int i = 0; i < maxarray; i++)
		{
			if (data[i] < pq.getMax())
			{
				pq.delMax();
				pq.insert(data[i]);
			}
		}
		remain -= maxarray;
		delete[] data;
	}

	int *data = new int[remain];
	fread(data, sizeof(int), remain, stdin);
	for (int i = 0; i < remain; i++)
	{
		if (data[i] < pq.getMax())
		{
			pq.delMax();
			pq.insert(data[i]);
		}
	}
	delete[] data;
	printf("%d", pq.getMax());
	return 0;



	//int n, k;
	//fread(&n, sizeof(int), 1, stdin);
	//fread(&k, sizeof(int), 1, stdin);
	//int *A = new int[k];
	//fread(A, sizeof(int), k, stdin);
	//PQ_ComplHeap<int> pq(A, k);
	//for (int i = 0; i < n - k; i++)
	//{
	//	int x;
	//	fread(&x, sizeof(int), 1, stdin);
	//	int maxElemRank = pq.getMaxRank();
	//	if (x < pq.getElem(maxElemRank))
	//	{
	//		pq.replaceMax(x, maxElemRank);
	//	}
	//}
	//printf("%d", pq.getElem(pq.getMaxRank()));
	//return 0;


	//#ifndef _OJ_
	//	freopen("input.txt", "r", stdin);
	//#endif _OJ_
	//int n, k;
	//scanf("%d %d", &n, &k);
	//int A[MAXK];
	//for (int i = 0; i < k; i++)
	//	scanf("%d", &A[i]);
	//PQ_ComplHeap<int> pq(A, k);
	//for (int i = 0; i < n - k; i++)
	//{
	//	int x;
	//	scanf("%d", &x);
	//	int maxElemRank = pq.getMaxRank();
	//	//printf("max = %d\n", pq.getElem(maxElemRank));
	//	if (x < pq.getElem(maxElemRank))
	//	{
	//		//pq.delMin();
	//		//pq.insert(x);
	//		pq.replaceMax(x, maxElemRank);
	//	}
	//}

	//printf("%d", pq.getElem(pq.getMaxRank()));
	//return 0;

//#ifndef _OJ_
//	freopen("input.txt", "r", stdin);
//#endif _OJ_
//	int n, k;
//	scanf("%d %d", &n, &k);
//	int A[MAXK];
//	for (int i = 0; i < k; i++)
//		scanf("%d", &A[i]);
//	PQ_ComplHeap<int> pq(A, k);
//	for (int i = 0; i < n - k; i++)
//	{
//		int x;
//		scanf("%d", &x);
//		//printf("max=%d\n", pq.getMax());
//		if (x < pq.getMax())
//		{
//			pq.delMax();
//			pq.insert(x);
//		}
//	}
//
//	printf("%d", pq.getMax());
//	return 0;
}