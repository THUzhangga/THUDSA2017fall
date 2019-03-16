#pragma once
#include <iostream>
#define MAX_DIGIT 8
int GetInt() {
	int x = 0, F = 1; char C = getchar();
	while (C < '0' || C > '9') { if (C == '-') F = -F; C = getchar(); }
	while (C >= '0' && C <= '9') { x = x * 10 - '0' + C, C = getchar(); }
	return x * F;
}

void PutInt(int x)
{
	char buf[MAX_DIGIT];
	int n = 0;
	while (x / 10 > 0)
	{
		buf[n] = x % 10 + '0';
		n++;
		x /= 10;
	}
	buf[n] = x + '0';
	for (int i = n; i >= 0; i--)
		putchar(buf[i]);
}

void GetString(char *str)
{
	char C = getchar();
	int length = 0;
	while (C != '\n' && C!=EOF)
	{
		str[length] = C;
		C = getchar();
		length++;
	}
}

void printString(char *str, int n)
{
	//printf("%d\n", i);
	for (int j = 0; j < n; j++)
	{
		printf("%c", str[j]);
	}
	printf("\n");
}
