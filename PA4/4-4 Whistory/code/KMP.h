#pragma once
/*K看M毛P片算法*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define printString(s) { for (size_t m = strlen(s), k = 0; k < m; k++) printf("%c", (s)[k]); printf("\n"); }

int* buildNext(char const* P) { //构造模式串P的next表（改进版本）. P is pattern
	size_t m = strlen(P), j = 0; //“主”串指针
	int* N = new int[m]; //next表
	int t = N[0] = -1; //模式串指针
	while (j < m - 1)
		if (0 > t || P[j] == P[t]) { //匹配
			N[j] = (P[++j] != P[++t] ? t : N[t]); //注意此句与未改进之前的区别
		}
		else //失配
			t = N[t];
	return N;
}

int match(char const* P, char* T)
{
	int *next = buildNext(P);
	int n = (int)strlen(T), i = 0;
	int m = (int)strlen(P), j = 0;
	while (j < m && i < n)
	{
		if (0 > j || T[i] == P[j])
		{
			i++;
			j++;
		}
		else j = next[j];
	}
	delete[] next;
	return i - j;
}