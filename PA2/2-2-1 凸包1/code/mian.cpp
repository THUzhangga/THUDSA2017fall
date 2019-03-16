#include <iostream>
#include "list.h"
#define MAX_COORDINATE 33554432
#define MIN_COORDINATE -33554432
struct node {
	int x;
	int y;
};
bool isSamePoint(struct node node1, struct node node2)
{
	return (node1.x == node2.x && node1.y == node2.y);
}

bool collinear(struct node node1, struct node node2, struct node node3)
{
	long long judegSide = (long long)(node2.x - node1.x) * (long long)(node3.y - node1.y) -
		(long long)(node3.x - node1.x) * (long long)(node2.y - node1.y);
	return judegSide == 0; //向量叉积的z方向分量为0，则向量共线
}
int main()
{
//#ifndef _OJ_
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//#endif
	int n;
	fread(&n, sizeof(int), 1, stdin);
	struct node *P = new struct node[n];
for (int i=0; i<n; i++) {
    fread(&P[i].x, sizeof(int), 1, stdin);
    fread(&P[i].y, sizeof(int), 1, stdin);
}
	List<struct node> pointOnHull;
	//第一步找到最下的点（如果有多个最下的点也没有关系，只要找到的那个是最下即可）
	struct node lowestPoint;
	lowestPoint.y = MAX_COORDINATE; //最下点初始化为最大int
	lowestPoint.x = MAX_COORDINATE;
	for (int i = 0; i < n; i++)
		if (P[i].y < lowestPoint.y || (P[i].y == lowestPoint.y && P[i].x < lowestPoint.x)) 
			lowestPoint = P[i];
			
	pointOnHull.push(lowestPoint);
	//第二步，循环连接到下一点
	//若某一点为pi，下一点为pi+1，应保证pi->pi+1能使得所有的点都在他们的左方（即逆时针寻找）
	//所谓右方，即pi->pi+1和pi->其他任意一点的叉积指向z轴正向，即第三分量大于0
	//进行乘法时用long long类型
	while (isSamePoint(pointOnHull.top(), lowestPoint) == false || pointOnHull.size() == 1)
	//循环结束条件：回到起始点而且大小超过1
	{
		struct node top = pointOnHull.top();
		struct node endPoint = P[0];
		for (int i = 1; i < n; i++) //P[0]已被选取
		{
			long long judegSide = (long long)(endPoint.x - top.x) * (long long)(P[i].y - top.y) -
				(long long)(P[i].x - top.x) * (long long)(endPoint.y - top.y);
			if (isSamePoint(endPoint, top) == true || judegSide < 0)//找到一个在右方的需要将其作为新的endPoint，这样旧的endPoint在它与top连线左方
				endPoint = P[i];
		}
		//经过上面的循环已经找到待加入的一点endPoint，此时看endPoint,top,top->prec是否共线
		//如果共线，pop()
		if (pointOnHull.size() >= 2 && collinear(pointOnHull.last()->pred->data, top, endPoint) == true)
			pointOnHull.pop();
		pointOnHull.push(endPoint);
	}
	//printf("%d", pointOnHull.size());
	ListNodePosi(struct node) anode = pointOnHull.first();
	for (int i = 0; i < pointOnHull.size() - 1; i++)
	{
		printf("%d %d\n", anode->data.x, anode->data.y);
		anode = anode->succ;
	}
}
