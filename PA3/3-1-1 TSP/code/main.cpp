#include <iostream>
#define MAXLINE 1000000
//#include "graphmatrix.h"
//#include "simplegraphlist.h"
//#include "test.h"
#include "value.h"
int main()
{
	//setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	//setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	#ifndef _OJ_
		freopen("input1.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
	#endif
	int n, m;

	//char *tempchar = new char [4];
	//fread(tempchar, sizeof(char), 4, stdin);
	//n = tempchar[0] - 48;
	//m = tempchar[2] - 48;

	scanf("%d %d", &n, &m);
	GraphList pricemap;
	for (int i = 1; i < n + 1; i++)
		pricemap.insert(i);

	int a, b, p;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &p);
		pricemap.insert(i + 1, p, a - 1, b - 1);
	}
	//pricemap.print();
	//pricemap.longestPath();
	pricemap.longestValue();
	//char *temparr = new char[6 * m -1];
	//fread(temparr, sizeof(char), 6 * m - 1, stdin);
	//int a, b, p;
	//for (int i = 0; i < m; i++)
	//{
	//	a = temparr[i * 6] - 48;
	//	b = temparr[i * 6 + 2] - 48;
	//	p = temparr[i * 6 + 4] - 48;
	//	//printf("%d %d %d\n",a, b, p );
	//	//pricemap.insert(i + 1, p, a - 1, b - 1); //注意这里a, b要减1！因为顶点i对应的data为i+1
	//}

	//int a, b, p;
	//for (int i = 0; i < m; i++)
	//{
	//	scanf("%d %d %d", &a, &b, &p);
	//	//pricemap.insert(i+1, p, a-1, b-1); //注意这里a, b要减1！因为顶点i对应的data为i+1
	//}
	//pricemap.longestPath();
	//Stack<int> *ts = pricemap.gatSort();
	//ts->print();
	//pricemap.longestValue();
	return 0;
}