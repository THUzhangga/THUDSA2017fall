#include <iostream>
//#include "Bitmap.h"
#define Posi(T) ListNode<T>*
typedef int Rank;
template <typename T>
struct ListNode
{
	T data;
	Posi(T) pred;
	Posi(T) succ;
	ListNode() {}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		:data(e), pred(p), succ(s) {}
	Posi(T) insertAsPred(T const& e);
	Posi(T) insertAsSucc(T const& e);
};
template <typename T> //将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
Posi(T) ListNode<T>::insertAsPred(T const& e) {
	Posi(T) x = new ListNode(e, pred, this); //创建新节点
	pred->succ = x; pred = x; //设置正向链接
	return x; //返回新节点的位置
}

template <typename T> //将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
Posi(T) ListNode<T>::insertAsSucc(T const& e) {
	Posi(T) x = new ListNode(e, this, succ); //创建新节点
	succ->pred = x; succ = x; //设置逆向链接
	return x; //返回新节点的位置
}


template <typename T> class List {
private:
	int _size;
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init();
	int clear();

public:
	List() { init(); } //默认
	T remove(Posi(T) p); //删除合法位置p处的节点,返回被删除节点
	~List();
	Rank size() const { return _size; } //规模
	Posi(T) first() const { return header->succ; }
	Posi(T) last() const { return trailer->pred; }
	Posi(T) insertAsFirst(T const& e);
	Posi(T) insertAsLast(T const& e);
	Posi(T) insertA(Posi(T) p, T const& e);
	Posi(T) insertB(Posi(T) p, T const& e);
	Posi(T) insertm(T const& e, Rank m, Posi(T) p); // 隔m个插入
	//T& operater[](Rank r) const;
	void printlist() const;
	void inverseprint(Posi(T) p) const;
};
template <typename T> void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}
template <typename T> int List<T>::clear() { //清空列表
	int oldSize = _size;
	while (0 < _size) 
		remove(header->succ); //反复删除首节点，直至列表变空
	return oldSize;
}
template <typename T> Posi(T) List<T>::insertAsFirst(T const& e)
{
	_size++; return header->insertAsSucc(e);
};//e当作首节点插入

template <typename T> Posi(T) List<T>::insertAsLast(T const& e)
{
	_size++; return trailer->insertAsPred(e);
} //e当作末节点插入

template <typename T> Posi(T) List<T>::insertA(Posi(T) p, T const& e)
{
	_size++; return p->insertAsSucc(e);
} //e当作p的后继插入（After）

template <typename T> Posi(T) List<T>::insertB(Posi(T) p, T const& e)
{
	_size++; return p->insertAsPred(e);
} //e当作p的前驱插入（Before)

template <typename T> Posi(T) List<T>::insertm(T const& e, Rank m, Posi(T) p)
{
	//printf("%d insertm\n", e);
	// 考虑特殊情况：没有人及有1个人时
	if (_size == 0) p = insertAsFirst(e); //插为首节点
	else if (_size == 1) p = insertAsLast(e); //插为末节点
	else
	{
		//printf("当前节点data=%d\n", p->data);
		int walked = 1; //已走过人数
		while (walked < m)
		{
			//printf("walked=%d p=%d\n", walked, p->data);
			if (p->succ->succ == NULL)//到末节点返回开头，且已经走过的人 + 1
			{
				//printf("回到first\n");
				p = first();
			}
			else
			{
				//printf("往下\n");
				p = p->succ;//从上个节点开始走
			}
			walked++;
		}
		return insertA(p, e);
	}
	return p;
}

template <typename T> T List<T>::remove(Posi(T) p) { //删除合法节点p，返回其数值
	T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
	p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
	delete p; _size--; //释放节点，更新规模
	return e; //返回备份的数值
}

template<typename T>
List<T>::~List()
{
	clear(); delete header; delete trailer;
}

template<typename T>
void List<T>::printlist() const
{
	printf("打印list\n");
	Posi(T) sp = first(); //从首节点出发
	int i = 0;
	while (i<_size)
	{
		printf("%d ", sp->data);
		sp = sp->succ;
		i++;
	}
	printf("\n");
}
template<typename T>
void List<T>::inverseprint(Posi(T) p) const
{
	int count = 0;
	while (p->pred != NULL) //非头节点，则继续逆序打印
	{
		printf("%d ", p->data);
		p = p->pred;
		count++;
	}
	//打印完后p变为首节点
	p = last(); //从末尾开始
	while (count < _size)
	{
		printf("%d ", p->data);
		count++;
		p = p->pred;
	}
}
int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n, m;
	if (scanf("%d %d", &n, &m) == EOF)
		return 0;
	List<int> listman;
	int num;
	Posi(int) p = NULL;
	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &num) == EOF)
			return 0;
		p = listman.insertm(num, m, p);
		//listman.printlist();
	}
	//printf("逆序打印前，data=%d ", p->data);
	listman.inverseprint(p);
	return 0;
}