#include <iostream>
#include <cstring>

//#include "AVL.h"
#include "final.h" //这里实际上是AVL树。
#include "fastio.h"

#define MAXN 350000
#define MAXM 500000
struct data {
	int p, v; //价格、美化度
	bool operator >= (const data data2){return (v > data2.v) || ((v == data2.v) && (p >= data2.p));} //判断大于等于：当v较大时或者v相等但是p大于等于
	bool operator <= (const data data2) { return (v < data2.v) || ((v == data2.v) && (p <= data2.p)); }
	bool operator == (data data2) { return (v == data2.v) && (p == data2.p); }
	bool operator < (data data2) {
		return (v < data2.v) || ((v == data2.v) && (p < data2.p));
	}
	bool operator > (data data2) { return (v >= data2.v) && (p >= data2.p); }
	void print() { printf("v=%d, p=%d\n", v, p); }
} bri[MAXN], mat[MAXM]; //bridge and material

void quicksort(int left, int right, struct data *a) //按照美化度由大到小快速排序。假如美化度相等，则比较价格（判断器已在结构体中实现）
{
	int i, j;
	struct data t, temp;
	if (left>right)
		return;
	temp = a[left]; //temp中存的就是基准数 
	i = left;
	j = right;
	while (i != j)
	{
		//顺序很重要，要先从右边开始找 
		while (a[j] <= temp && i < j) j--;
		//再找右边的 
		while ( temp <= a[i] && i<j) i++;
		//交换两个数在数组中的位置 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//最终将基准数归位 
	a[left] = a[i];
	a[i] = temp;
	quicksort(left, i - 1, a);//继续处理左边的，这里是一个递归的过程 
	quicksort(i + 1, right, a);//继续处理右边的 ，这里是一个递归的过程 
}

int main()
{
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
//#ifndef _OJ_
//	freopen("input.txt", "r", stdin);
//	//	freopen("output.txt", "w", stdout);
//#endif
	int n = GetInt(), m = GetInt();
	//int n, m;
	//scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		//scanf("%d %d", &bri[i].p, &bri[i].v);
		bri[i].p = GetInt(), bri[i].v = GetInt();
	}
	for (int i = 0; i < m; i++)
	{
		//scanf("%d %d", &mat[i].p, &mat[i].v);
		mat[i].p = GetInt(), mat[i].v = GetInt();
	}
	quicksort(0, n - 1, bri);
	quicksort(0, m - 1, mat);

	AVL<int> tr;

//	for (int i = 0; i < n; i++) bri[i].print();
//	//AVLTree<int> tr;
	long long ans = 0;
	int j = 0;

	for (int i = 0; i < n; i++)
	{
		//printf("i=%d ", i);
		//bri[i].print();
		while ((j < m) && (/*(mat[j].p >= bri[i].p) &&*/ (mat[j].v >= bri[i].v))) 
			//第j种材料可以修理第i个桥（注意，排序后，如果第j种材料能修理第i桥，必定能修理第i+1桥）
		//这个地方我很疑惑，因为题目中已经说了对于第 i 种修理材料能成功修理第 j 个石桥的条件是：当且仅当 hi ≥ pj，di ≥ vj。但是我现在只要美化度能满足要求我就加到树里面了。
		//这让我debug很久，50%测试只有一个正确。后来群里的北极光同学说有的测例比较特殊，会出现石桥全在材料右下角的情况。
		//我想我正确的那个应该恰好对应这种情况，进而推断出我的条件太强了，于是我分别试着去掉一个条件。
		//后来发现只要美化度满足要求就行了。真是有点奇怪。
		{
			//printf("insert: v=%d p=%d\n", mat[j].v, mat[j].p);
			tr.insert(mat[j].p);//插入AVL树中。注意，AVL的insert算法有改动，即找到了之后该节点的num+1，否则插入新节点
			//printf("insert%d num=%d\n", mat[j].p, in->num);
			j++;
		}
		//接下来在当前树中找到可以修理i桥的材料中p最小的材料
		ans += (long long) tr.take(bri[i].p);
	}
	printf("%lld", ans);

}
