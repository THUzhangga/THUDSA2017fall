#include <iostream>
static int binSearch(int *alarm_x, int *alarm_y, int px, int py, int lo, int hi)
{
	while (lo < hi)
	{
		int mi = (hi + lo) >> 1; //中间
		int ax = alarm_x[mi];
		int ay = alarm_y[mi];
		//为防止溢出用long long
		//先计算减法，再算乘法应该更快
		//应当注意mi直线上对应的是mi+1区域
		//judgeSide < 0时，point严格在直线左侧，也即point属于[lo, mi]
		//judgeSide < 0时, point属于[mi+1, hi]
		//注意本函数的二分查找对应的是左闭右闭区间
		long long judegSide = ((long long)px * (long long)py - (long long)(ax - px) * (long long)(ay - py)); 
		if (judegSide > 0)
			lo = mi + 1;
		else if (judegSide < 0)
			hi = mi;
		else return mi+1;//必须让在直线时跳出来，应为它不是严格左侧，归于右侧


		//printf("judgeSide=%d\n", judegSide);
		//printf("	ax ay=%d %d\n", ax, ay);
		//printf("	ay*px + ax*py - ax*ay= %d\n", ay*px + ax*py - ax*ay);
		//printf("	mi=%d hi=%d low=%d\n",mi, hi, lo);
	}
	return lo;
	//while (1 < hi - lo)
	//{
	//	int mi = (hi + lo) >> 1; //中间
	//	int ax = alarm_x[mi];
	//	int ay = alarm_y[mi];
	//	long long judegSide = ((long long)px * (long long)py - (long long)(ax - px) * (long long)(ay - py));
	//	if (judegSide < 0)
	//		hi = mi;
	//	else
	//		lo = mi;
	//	//else return mi+1;//必须让在直线时跳出来，应为它不是严格左侧，归于右侧

	//	//(judegSide < 0) ? lo = mi + 1 : hi = mi;

	//	//printf("judgeSide=%d\n", judegSide);
	//	//printf("	ax ay=%d %d\n", ax, ay);
	//	//printf("	ay*px + ax*py - ax*ay= %d\n", ay*px + ax*py - ax*ay);
	//	//printf("	mi=%d hi=%d low=%d\n", mi, hi, lo);
	//}
	//return ++lo;
}
int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	int *alarm_x = new int[n];
	int *alarm_y = new int[n];
	int *point_x = new int[m];
	int *point_y = new int[m];
	for (int i = 0; i < n; i++)
	{
		if (scanf("%d %d", &alarm_x[i], &alarm_y[i]) == EOF)
			return 0;
	}
	for (int i = 0; i < m; i++)
	{
		if (scanf("%d %d", &point_x[i], &point_y[i]) == EOF)
			return 0;
	}
	for (int i = 0; i < m; i++)
	{
		int area = binSearch(alarm_x, alarm_y, point_x[i], point_y[i], 0, n);
		printf("%d\n", area);
	}
}
