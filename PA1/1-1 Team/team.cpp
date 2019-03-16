#include <iostream>
#include <string.h>
int n;
int k;
void alloc(int *team, int *people, bool &flag)
{
	int cursor = team[n] + 1; // cursor move to the next number of last selection

	for (int i = cursor; i < n;i++)
	{
		if (people[team[i] - 1] != 0)
		{
			if (k == people[team[i] - 1])
			{
				flag = true;
				break;
			}
			memset(&people[team[i] - 1], 0, 4);
			team[n] = i;
			break;
		}
	}
}
int main()
{
	scanf("%d", &n);
	int *people = new int[n];
	int *A = new int[n+1];
	int *B = new int[n+1];
	int *C = new int[n+1];
	for (int i = 0; i < n;i++)
		people[i] = i+1;
	for (int i = 0; i < n;i++)
		scanf("%d", &A[i]);
	for (int i = 0; i < n;i++)
		scanf("%d", &B[i]);
	for (int i = 0; i < n;i++)
		scanf("%d", &C[i]);
	scanf("%d", &k);

	// the last one in the array is for saving the order number in the previous selection
	// with an initial number as -1
	A[n] = -1;
	B[n] = -1;
	C[n] = -1;
	bool flag = false;
	while (true)
	{
		alloc(A, people, flag);
		if (flag == true)
		{
			printf("%c", 'A');
			break;
		}
		alloc(B, people, flag);
		if (flag == true)
		{
			printf("%c", 'B');
			break;
		}
		alloc(C, people, flag);
		if (flag == true)
		{
			printf("%c", 'C');
			break;
		}
	}
	return 0;
}