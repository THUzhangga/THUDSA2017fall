#include <iostream>
#include "stack.h"
int n, m;
struct movement { //移动结构体
	int code; //移动的列车的代码
	char move; //移动的列车的动作类型
} temp;

int move1step(int t, Stack<int> &A, Stack<int> &S, Stack<movement> &trainmove)
// -1代表继续移动（寻找同列车）
// 1代表移动成功
// 0代表移动失败
{
	/*if (S.empty() || t != S.top())//应该从A中取
	{
		if (A.empty() || (t != A.top() && S.getsize() == m)) return 0;
		if (t == A.top())
		{
			temp.code = A.pop(); temp.move = 'P';
			trainmove.push(temp);
			return 1;
		}
		else
		{
			S.push(A.pop()); //将A的头弹出，然后压入S
			temp.code = S.top(); temp.move = 'I';
			trainmove.push(temp);
			return -1; //应该继续移动
		}
	}
	temp.code = S.pop(); temp.move = 'O';
	trainmove.push(temp);
	return 1;*/
	if((!A.empty()) && A.top()==t){
		temp.code = A.pop(); temp.move = 'P';
		trainmove.push(temp);
		return 1;
	} 
	else if((!S.empty()) && S.top() == t){
		temp.code = S.pop(); temp.move = 'O';
		trainmove.push(temp);
		return 1;
	}
	else{
		if(A.empty() || S.getsize()>=m) return 0;
		S.push(A.pop()); //将A的头弹出，然后压入S
		temp.code = S.top(); temp.move = 'I';
		trainmove.push(temp);
		return -1; //应该继续移动
	}
}
void printmove(Stack<movement> &A)
{
	ListNodePosi(movement) tm = A.first();
	int j = 0;
	while (j < A.getsize())
	{
		printf("%d %c\n", tm->data.code, tm->data.move);
		tm = tm->succ;
		j++;
	}
}
int main()
{
//#ifndef _OJ_
//	freopen("input1.txt", "r", stdin);
//	//freopen("output1.txt", "w", stdout);
//#endif
	
	scanf("%d %d", &n, &m);
	Stack<int> S; Stack<int> A;
	Stack<movement> trainmove;
	int tr;
	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &tr) != EOF)
			A.insertAsFirst(tr);
	}
	int flag;
	int i = 1;
	for (int i = 1; i <= n; i++)
	{
		//printf("%d\n", i);
		//S.printStack();
		flag = move1step(i, A, S, trainmove);
		while (flag == -1)
			flag = move1step(i, A, S, trainmove);
		if (flag == 0) break;
	}

	if (flag == 0)
		printf("No\n");
	else
		printmove(trainmove);
}	

