#include <iostream>
#include "queue.h"
//template <typename T> class Queap : public Queue<T> {
//public:
//	void enqueue(T const & e) { insertAsLast(e); }
//	T dequeue() { return remove(first()); }
//	T & front() { return first()->data; }
//};
int max(int x, int y)
{
	return (x > y) ? x : y;
}
int main() 
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n;
	//setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	//setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	scanf("%d", &n);
	Queue<int> soldier;
	Queue<int> shadow; //影子栈
	char buf[8];
	int add; //假如队尾的人
	for (int i = 0; i < n; i++)
	{
		//setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
		//setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
		scanf("%s", buf);
		switch (buf[0])
		{
		case 'E': //enqueue
		{
			scanf("%d", &add);
			//printf("E %d\n", add);
			soldier.enqueue(add);
			shadow.enqueue(add);
			ListNodePosi(int) x = shadow.last()->pred;
			int count = 1;
			while (count<shadow.getsize() && x->data < add)
			{
				x->data = add;
				x = x->pred;
				count++;
			}
			//soldier.print();
			//printf("shaddow\n");
			//shadow.print();
			break;
		}
		case 'D': //dequeue
		{
			if (!soldier.empty())
			{
				printf("%d\n", soldier.dequeue());
				shadow.dequeue();
			}
			break;
		}
		case 'M': //max
		{

			printf("%d\n", shadow.front());
			break;
		}
		default: break;
		}
	}
}