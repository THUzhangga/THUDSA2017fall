#pragma once
#include <iostream>
#include "vector.h"
#include "bintree.h"
#include "DataHead.h"
#include "stack.h"


struct rangeStack //在递归划分子区间的时候用到的栈
{
	BinNodePosi(int) x;
	int left, right;
	rangeStack(BinNodePosi(int) x = NULL) : x(x), left(NULL), right(NULL) {}
	rangeStack(BinNodePosi(int) x, int left, int right) : x(x), left(left), right(right) {}
};

//struct rangeStack
//{
//	int left, right;
//	rangeStack() : left(NULL), right(NULL) {}
//	rangeStack(int left, int right) : left(left), right(right) {}
//};


void quicksort_x(int left, int right, struct data *a) //按照x由小到大快速排序(判断器已在结构体中实现）
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
		while (a[j].x >= temp.x && i < j) j--;
		//再找右边的 
		while (temp.x >= a[i].x && i<j) i++;
		//交换两个数在数组中的位置 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//最终将基准数归位 
	a[left] = a[i];
	a[i] = temp;
	quicksort_x(left, i - 1, a);//继续处理左边的，这里是一个递归的过程 
	quicksort_x(i + 1, right, a);//继续处理右边的 ，这里是一个递归的过程 
}

void quickSort(int left, int right, Vector<int> &a) //按照TP里面的y值由小到大快速排序
{
	int i, j;
	int t, temp;
	if (left>right)
		return;
	temp = a[left]; //temp中存的就是基准数 
	i = left;
	j = right;
	while (i != j)
	{
		//顺序很重要，要先从右边开始找 
		while (TP[a[j]].y >= TP[temp].y && i < j) j--;
		//再找右边的 
		while (TP[temp].y >= TP[a[i]].y && i<j) i++;
		//交换两个数在数组中的位置 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//最终将基准数归位 
	a[left] = a[i];
	a[i] = temp;
	quickSort(left, i - 1, a);//继续处理左边的，这里是一个递归的过程 
	quickSort(i + 1, right, a);//继续处理右边的 ，这里是一个递归的过程 
}

void findSameX(int left, int right, Vector<int> &X, Vector<int> &begin, Vector<int> &end, struct data* a)
{
	int i = 0;
	int x = a[left].x;
	X.insert(x);
	begin.insert(left);
	while (i >= left && i <= right)
	{
		if (a[i].x > x)
		{
			x = a[i].x;
			X.insert(x);
			begin.insert(i);
			if (i > left)
				end.insert(i - 1);
		}
		i++;
	}
	end.insert(right);
}

void quicksort_y(int left, int right, struct data *a) //按照y由小到大快速排序(判断器已在结构体中实现）
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
		while (a[j].y >= temp.y && i < j) j--;
		//再找右边的 
		while (temp.y >= a[i].y && i<j) i++;
		//交换两个数在数组中的位置 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//最终将基准数归位 
	a[left] = a[i];
	a[i] = temp;
	quicksort_y(left, i - 1, a);//继续处理左边的，这里是一个递归的过程 
	quicksort_y(i + 1, right, a);//继续处理右边的 ，这里是一个递归的过程 
}




void rangeBuild(BinTree<int> &tr, BinNodePosi(int) &x, int left, int right, struct data *TP, Vector<int> &X, Vector<int> &begin, Vector<int> &end, Stack<rangeStack> &S)
//请注意，所谓left与right是指的X的边界rank
{
	int mid;
	mid = (left + right) >> 1;
	if (x == NULL) //如果x为空，构造根节点
	{
		x = tr.insertAsRoot(X[(left + right) >> 1], X[left], X[right], false);
		for (int i = begin[left];i <= end[right];i++) //此时i变成了TP(原结构体数组)的rank
			x->Y.insert(i);
		quickSort(0, end[right] - begin[left], x->Y);
		//x->Y.print();
		//x->Y.printy();
		struct rangeStack rightStack(x, mid+1, right);
		struct rangeStack leftStack(x, left, mid);
		S.push(rightStack);
		S.push(leftStack); //左半侧后入先出
		//BinNodePosi(int) tmp = x;

		//rangeBuild(tr, x, left, mid, TP, X, begin, end);
		//rangeBuild(tr, tmp, mid + 1, right, TP, X, begin, end);
		return;
	}

	if (right == left) //如果区间长度为0，插入叶节点
	{
		if (x->data >= X[right])
		{
			tr.insertAsLC(x, X[left], X[left], X[right], true);
			for (int i = begin[left];i <= end[right];i++)
				x->lc->Y.insert(i);
			quickSort(0, end[right] - begin[left], x->lc->Y);
		}
		else
		{
			tr.insertAsRC(x, X[left], X[left], X[right], true);
			for (int i = begin[left];i <= end[right];i++)
				x->rc->Y.insert(i);
			quickSort(0, end[right] - begin[left], x->rc->Y);
		}
		//printf("left=%d, right=%d\n", left, right);x->Y.printy();
		return;
	}

	if (left + 1 <= right) //区间长度>=1
	{
		x = (x->data >= X[mid]) ? tr.insertAsLC(x, X[mid], X[left], X[right], false) : \
			tr.insertAsRC(x, X[mid], X[left], X[right], false);
		for (int i = begin[left];i <= end[right];i++) //此时i变成了TP(原结构体数组)的rank
			x->Y.insert(i);
		quickSort(0, end[right] - begin[left], x->Y);
		struct rangeStack rightStack(x, mid + 1, right);
		struct rangeStack leftStack(x, left, mid);
		S.push(rightStack);
		S.push(leftStack); //左半侧后入先出
		//printf("left=%d, right=%d\n", left, right);x->Y.printy();
		//BinNodePosi(int) tmp = x;
		//rangeBuild(tr, x, left, mid, TP, X, begin, end);
		//rangeBuild(tr, tmp, mid + 1, right, TP, X, begin, end);
	}
}

void RangeBuild(BinTree<int> &tr, BinNodePosi(int) &x, int left, int right, Vector<int> &X, Vector<int> &begin, Vector<int> &end)
{
	struct rangeStack temp;
	Stack<rangeStack> S;
	rangeBuild(tr, x, left, right, TP, X, begin, end, S);
	while (!S.empty())
	{
		temp = S.pop();
		rangeBuild(tr, temp.x, temp.left, temp.right, TP, X, begin, end, S);
	}
}

void query_y(Vector<int> &y, int lo_y, int hi_y, long long &t, int &count)
//查询y的区间。请注意y是TP里面的rank，而且已经按照TP里面的y值从小到大排序
//我们的目标是：查询所有大于等于lo_y且小于等于hi_y的值
//需要针对二分查找做一点微小的改动（很惭愧）
{
	//y.printy();
	int lo = 0;
	int hi = y.size();
	if (TP[y[lo]].y > hi_y || TP[y[hi - 1]].y < lo_y) //无交集
		return;
	int st, ed;
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		lo_y <= TP[y[mi]].y ? hi = mi: lo = mi + 1; //(lo, mi] or (mi, hi]
	} //hi-1是大于等于目标值的最小值的rank
	//printf("lo=%d hi=%d\n", lo, hi);
	//printf("find =%d", y[hi]);
	st = hi;
	lo = 0;
	hi = y.size();
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		hi_y < TP[y[mi]].y ? hi = mi : lo = mi + 1; //[lo, mi) or [mi, hi)
	}//lo-1是小于等于目标值的最大值的rank
	ed = lo - 1;

	//记录温度和及个数
	for (int i = st;i <= ed;i++)
	{
		//printf("%d %d %d\n", TP[y[i]].x, TP[y[i]].y, TP[y[i]].t);
		t += TP[y[i]].t;
		count++;
	}
}

void query(BinTree<int> &tr, BinNodePosi(int) x, int lo_x, int hi_x, int lo_y, int hi_y, long long &sum_t, int &count, Stack<BinNodePosi(int)> &temp)
{
	int x_mid = x->data; //中位数
	int x_left = x->left; //左边界
	int x_right = x->right; //right boundary
	if (x_left > hi_x || x_right < lo_x)
		return; //没有交集
	if (x->isExternal) //到达叶节点
	{
		if (x->data >= lo_x && x->data <= hi_x)//叶节点在区间内
			query_y(x->Y, lo_y, hi_y, sum_t, count);
		return;
	}
	if ((x_left >= lo_x && x_right <= hi_x)) //当前x区间被包含于查询的x区间
	{
		query_y(x->Y, lo_y, hi_y, sum_t, count);
		return; //结束
	}

	if (x_mid >= lo_x && x_mid < hi_x) //当前x区间中位数包含在待查询区间中（注意mid本身是归于左孩子的）
	{
		temp.push(x->rc);
		temp.push(x->lc);
	}
	else if (x_mid >= hi_x)
		temp.push(x->lc);
	else if (x_mid < lo_x)
		temp.push(x->rc);
}

int Query(BinTree<int> &tr, int lo_x, int hi_x, int lo_y, int hi_y)
{
	int re;
	long long sum_t = 0;
	int count = 0;
	BinNodePosi(int) x = tr.getroot();
	Stack<BinNodePosi(int)> temp;
	BinNodePosi(int) c;
	query(tr, x, lo_x, hi_x, lo_y, hi_y, sum_t, count, temp);
	while (!temp.empty())
	{
		c = temp.pop();
		query(tr, c, lo_x, hi_x, lo_y, hi_y, sum_t, count, temp);
	}
	//printf("%lld %d\n", sum_t, count);
	return re = (count == 0) ? 0 : (int)(sum_t / (long long)count);
}