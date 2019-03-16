#include <iostream>
#include <string.h>
//#include "bitmap.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int EmployeeCode[10000001] = { -1 }; //存储员工代码
typedef int Rank;
class Bitmap { //位图Bitmap类：以空间作为补偿，节省初始化时间（既允许插入，亦支持删除）
private:
	Rank* F; Rank N; //规模为N的向量F，记录[k]被标记的次序（即其在栈T[]中的秩）
	Rank* T; Rank top; //容量为N的栈T，记录被标记各位秩的栈，以及栈顶指针

protected:
	inline bool valid(Rank r) { return (0 <= r) && (r < top); }
	inline bool erased(Rank k) //判断[k]是否曾被标记过，且后来又被清除
	{
		return valid(F[k]) && !(T[F[k]] + 1 + k);
	} //这里约定：T[ F[k] ] = - 1 - k

public:
	Bitmap(Rank n = 8) //按指定（或默认）规模创建比特图（为测试暂时选用较小的默认值）
	{
		N = n; F = new Rank[N]; T = new Rank[N]; top = 0;
	} //在O(1)时间内隐式地初始化
	~Bitmap() { delete[] F; delete[] T; } //析构时释放空间

										  // 接口
	inline void set(Rank k) { //插入
		if (test(k)) return; //忽略已带标记的位
		if (!erased(k)) F[k] = top++; //若系初次标记，则创建新校验环
		T[F[k]] = k; //若系曾经标记后被清除，则恢复原校验环
	}
	inline void clear(Rank k) //删除
	{
		if (test(k)) T[F[k]] = -1 - k;
	} //忽略不带标记的位
	inline bool test(Rank k) //测试
	{
		return valid(F[k]) && (k == T[F[k]]);
	}
	inline void reset() //复位
	{
		top = 0;
	}
};
int main() {
	//#ifndef _OJ_
	//	freopen("input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
	//#endif
	int n, m;
	// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	scanf("%d\n%d", &n, &m);
	Bitmap bitmap(n);
	memset(EmployeeCode, 0xff, (n + 1) * sizeof(int));
	char buf[8];
	int cmd1, cmd2;
	int output = 0;
	int working = 0; //记录正在上班的员工个数
	for (int i = 0; i < m;i++)
	{
		// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
		// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
		scanf("%s", buf);
		switch (buf[0])
		{
		case 'I':
		{
			// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
			// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
			scanf("%d%d", &cmd1, &cmd2);
			if (!bitmap.test(cmd1)) //如果未登录
			{
				bitmap.set(cmd1);
				working++;
			}
			EmployeeCode[cmd1] = cmd2; //无论登录与否皆改变code
			break;
		}
		case 'O':
		{
			// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
			// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
			scanf("%d", &cmd1);
			if (bitmap.test(cmd1)) //如果已登录，则注销
			{
				bitmap.clear(cmd1);
				working--;
				EmployeeCode[cmd1] = -1;
			}
			break;
		}
		case 'C':
		{
			bitmap.reset(); //复位
			working = 0;
			break;
		}
		case 'N':
		{
			output += working;
			break;
		}
		case 'Q':
		{
			// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
			// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
			scanf("%d", &cmd1);
			if (bitmap.test(cmd1))
				output += EmployeeCode[cmd1];
			else
				output += -1;
			break;
		}
		default: break;
		}
	}
	// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	printf("%d", output);
	return 0;
}