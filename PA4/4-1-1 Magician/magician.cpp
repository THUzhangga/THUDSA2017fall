#pragma once
#include<iostream>
#include<cstring>
#include <cstdio>  
typedef long long LL;
const int maxn = 1000005;
using namespace std;


LL sum[maxn << 2], add[maxn << 2], mul[maxn << 2], p;

void pushUp(int o)
{
	sum[o] = (sum[o << 1] + sum[o << 1 | 1]);
}

void build(int o, int l, int r)
{
	mul[o] = 1;
	if (l == r)
	{
		sum[o] = 1;
		return;
	}
	int m = (l + r) >> 1;
	build(o << 1, l, m);
	build(o << 1 | 1, m + 1, r);
	pushUp(o);
}

void pushDown(int o)
{
	if (mul[o] != 1)
	{
		mul[o << 1] = mul[o << 1] * mul[o];
		mul[o << 1 | 1] = mul[o << 1 | 1] * mul[o];
		sum[o << 1] = sum[o << 1] * mul[o];
		sum[o << 1 | 1] = sum[o << 1 | 1] * mul[o];
		mul[o] = 1;
	}
}

void update(int o, int l, int r, int tl, int tr)
//l, r为当前区间
//tl, tr为更新区间
{
	if (tl <= l && r <= tr)
	{
		mul[o] = mul[o] * (-1);
		sum[o] = sum[o] * (-1);
		return;
	}
	pushDown(o);
	int m = (l + r) >> 1;
	if (tl <= m) update(o << 1, l, m, tl, tr);
	if (m < tr) update(o << 1 | 1, m + 1, r, tl, tr);
	pushUp(o);
}

LL query(int o, int l, int r, int tl, int tr)
{
	if (tl <= l && r <= tr)
		return sum[o];
	pushDown(o);
	int m = (l + r) >> 1;
	LL ans = 0;
	if (tl <= m) ans += query(o << 1, l, m, tl, tr);
	if (m < tr) ans += query(o << 1 | 1, m + 1, r, tl, tr);
	return ans;
}
int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	//for (int i = 1; i <= n; i++) printf("%lld ", sum[i]);
	char op[2];

	for (int i = 1;i <= m;i++)
	{
		int l, r;
		scanf("%s", op);
		if (op[0] == 'H')
		{

			scanf("%d%d", &l, &r);
			update(1, 1, n, l, r);
		}
		else if (op[0] == 'Q')
		{
			scanf("%d%d", &l, &r);
			int que = query(1, 1, n, l, r);
			int re = (r - l + 1 + query(1, 1, n, l, r)) >> 1;
			printf("%d\n", re);
		}
	}
	return 0;
}