#pragma once
#include <iostream>
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)
using namespace std;
#define BinNodePosi(T) BinNode<T>*
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
#define HeightUpdated(x) /*高度更新常规条件*/ ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define EQUAL(e, v)  (!(v) || (e) == (v)->data) //节点v（或假想的通配哨兵）的关键码等于e
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件
#define FromParentTo(x) /*来自父亲的引用*/ \
	( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*左高*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*右高*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
   ) \
   ) \
)

inline int max(int a, int b) {
	return (a > b) ? a : b;
}

template<class T>
class BinNode {
public:
	T data;
	int height;
	int num;
	BinNodePosi(T) parent, *lc, *rc;
	BinNode() :data(NULL), height(0), num(0), parent(NULL), lc(NULL), rc(NULL) {}
	BinNode(T e, BinNodePosi(T) parent = NULL) : data(e), height(0), num(0), parent(parent), lc(NULL), rc(NULL) {}

	//int size() {
	//	int s = 1; //计入本身
	//	if (lc) s += lc->size(); //递归计入左子树规模
	//	if (rc) s += rc->size(); //递归计入右子树规模
	//	return s;
	//}

	BinNodePosi(T) succ()  //取当前节点的直接后继
	{
		BinNodePosi(T) s = this; //记录后继的临时变量
		if (rc) { //若有右孩子，则直接后继必在右子树中，具体地就是
			s = rc; //右子树中
			while (HasLChild(*s)) s = s->lc; //最靠左（最小）的节点
		}
		else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
			while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
			s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
		}
		return s;
	}
};

template<class T>
inline int getHeight(BinNodePosi(T) bn) { return (bn == NULL) ? -1 : bn->height; }

template<class T>
class AVL {
public:
	BinNodePosi(T) _root, *_hot;
	int _size;

	AVL() :_root(NULL), _hot(NULL), _size(0) {}
	//~AVL(): { if (0 < _size) remove(_root); }
	//在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
	static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot) 
	{
		if (EQUAL(e, v)) return v; hot = v; //退化情况：在子树根节点v处命中
		while (1) { //一般地，反复不断地
			BinNodePosi(T) & c = (e < hot->data) ? hot->lc : hot->rc; //确定深入方向
			if (EQUAL(e, c)) return c; hot = c; //命中返回，或者深入一层
		} //hot始终指向最后一个失败节点
	} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）

	BinNodePosi(T) & search(T e)
	{
		return searchIn(_root, e, _hot = NULL);
	}

	int updateHeight(BinNodePosi(T) x) //更新节点x高度
	{
		return x->height = 1 + max(stature(x->lc), stature(x->rc));
	}

	BinNodePosi(T) connect34(
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
	{
		//*DSA*/print(a); print(b); print(c); printf("\n");
		a->lc = T0; if (T0) T0->parent = a;
		a->rc = T1; if (T1) T1->parent = a; updateHeight(a);
		c->lc = T2; if (T2) T2->parent = c;
		c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
		b->lc = a; a->parent = b;
		b->rc = c; c->parent = b; updateHeight(b);
		return b; //该子树新的根节点
	}

	BinNodePosi(T) rotateAt(BinNodePosi(T) v)  //v为非空孙辈节点
	{
		if (!v) { exit(-1); }
		BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
		if (IsLChild(*p)) /* zig */
			if (IsLChild(*v)) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
				p->parent = g->parent; //向上联接
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			}
			else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
				v->parent = g->parent; //向上联接
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			}
		else  /* zag */
			if (IsRChild(*v)) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
				p->parent = g->parent; //向上联接
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			}
			else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
				v->parent = g->parent; //向上联接
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
	}

	void updateHeightAbove(BinNodePosi(T) x) { //更新高度
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}

	BinNodePosi(T) insert(const T& e) //将关键码e插入AVL树中
	{ 
		BinNodePosi(T) & x = search(e);
		if (x) { //如果x存在，那么出现次数+1
			x->num++;
			return x;
		}
		BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
		_size++; //创建新节点x
				 // 此时，x的父亲_hot若增高，则其祖父有可能失衡
		for (BinNodePosi(T) g = _hot; g; g = g->parent) { //从x之父出发向上，逐层检查各代祖先g
			if (!AvlBalanced(*g)) { //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将子树
				BinNodePosi(T)& h = FromParentTo(*g);
				h = rotateAt(tallerChild(tallerChild(g))); //重新接入原树
				break; //g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
			}
			else //否则（g依然平衡），只需简单地
				updateHeight(g); //更新其高度（注意：即便g未失衡，高度亦可能增加）
		} //至多只需一次调整；若果真做过调整，则全树高度必然复原
		return xx; //返回新节点位置
	} //无论e是否存在于原树中，总有AVL::insert(e)->data == e

	BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot) 
	{
		BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
		BinNodePosi(T) succ = NULL; //实际被删除节点的接替者
		if (!HasLChild(*x)) //若*x的左子树为空，则可
			succ = x = x->rc; //直接将*x替换为其右子树
		else if (!HasRChild(*x)) //若右子树为空，则可
			succ = x = x->lc; //对称地处理——注意：此时succ != NULL
		else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
			w = w->succ(); //（在右子树中）找到*x的直接后继*w
			swap(x->data, w->data); //交换*x和*w的数据元素
			swap(x->num, w->num);
			BinNodePosi(T) u = w->parent;
			((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w
		}
		hot = w->parent; //记录实际被删除节点的父亲
		if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
		return succ; //释放被摘除节点，返回接替者
	}

	bool remove(T e) //删除（重写）
	{ 
		_hot = NULL;
		BinNodePosi(T)& x = search(e); if (!x) return false; //确认目标存在（留意_hot的设置）
		if (x->num != 0) { //如果材料次数不为0，那么材料次数-1即可
			x->num--;
			return true;
		}
		//如果材料次数为0，则要删去该材料
		removeAt(x, _hot); _size--; //先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
		for (BinNodePosi(T) g = _hot; g; g = g->parent) { //从_hot出发向上，逐层检查各代祖先g
			if (!AvlBalanced(*g)) { //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至
				BinNodePosi(T)& h = FromParentTo(*g);
				g = rotateAt(tallerChild(tallerChild(g))); //原父亲
				h = g;
			}
			updateHeight(g); //并更新其高度（注意：即便g未失衡，高度亦可能降低）
		} //可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
		return true; //删除成功
	}

	T take(T const e) //取出大于等于目标值的最小值
	{    
		if (!_root) return 0; //如果根节点为空，返回0.当然题目中已经说明每种石桥均能找到修它的材料，因此在寻找某个石桥的材料时，树不可能空。
		if (_root->data == e) {//在根节点找到
			remove(e);
			return e;
		}

		T re = INT_MAX; //re用于存放大于目标值的最小值，初始化为最大整数
		_hot = _root;
		while (1) {
			BinNodePosi(T) c = (e < _hot->data) ? _hot->lc : _hot->rc; //确定深入方向
			if (e <= _hot->data && re >= _hot->data)
				re = _hot->data; //用hot更新re
			if (!c)
				break; 
			else if (e == c->data) 
			{
				re = e;
				break;
			}
			_hot = c;
		}
		remove(re);
		return re;
	}
};

