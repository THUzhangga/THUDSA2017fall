#include <iostream>
//#include <cstring>
#include "hashtable.h"
//#include "KMP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#define MAXN 1000
#define printString(s) { for (size_t m = strlen(s), k = 0; k < m; k++) printf("%c", (s)[k]); printf("\n"); }

int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	scanf("%d%d", &n, &m);
	Hashtable<int, int> ht;
	Hashtable<int, int> ht2;

	for (int i = 1; i <= m;i++)
	{
		char *wheel = new char[n];
		char *Wheel = new char[2 * n];
		scanf("%s", wheel);
		sprintf(Wheel, "%s%s", wheel, wheel); //将小车轮拼接成大车轮
		int toprint = NULL;
		bool iszero = NULL;

		int st = 1;
		LL code = hashCode(Wheel, n);
		if (ht.get((int)code))
		{
			toprint = *ht.get((int)code);
			printf("%d\n", *ht.get((int)code));
		}
		else
		{
			ht.put((int)code, i);
			while (st < n)
			{
				code = (mul((code - (LL)Wheel[st - 1] * Pow(base, n - 1)), (LL)base) % mod + Wheel[st + n - 1]) % mod;
				if (code < 0)
					code += mod;
				ht.put((int)code, i);
				st++;
			}
			printf("0\n");
		}
	}
}