#include <iostream>
#include <cstring>
#include "trietree.h"
#include "fastio.h"
int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	Trie *tr = new Trie();
	getchar();
	for (int i = 0; i < n; i++)
	{
		char str[8];
		int length = 0;
		GetString(str, length);

		tr->addWord(str, length);
	}
	for (int i = 0; i < len; i++)
	{
		printf("%c", max_str[i]);
	}
	printf(" %d", max_num);

	return 0;
}