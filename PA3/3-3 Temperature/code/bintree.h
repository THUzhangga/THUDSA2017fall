#pragma once

#include "binnode.h" //引入二叉树节点类
#include "release.h"

using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}
template <typename T> class BinTree { //二叉树模板类
protected:
   int _size; BinNodePosi(T) _root; //规模、根节点
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //构造函数
   ~BinTree() { /*if ( 0 < _size ) remove ( _root );*/ } //析构函数
   int size() const { return _size; } //规模
   bool empty() const { return !_root; } //判空
   BinNodePosi(T) getroot() const { return _root; } //树根
   BinNodePosi(T) insertAsRoot ( T const& e ); //插入根节点
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e作为x的左孩子（原无）插入
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e作为x的右孩子（原无）插入

   BinNodePosi(T) insertAsRoot(T const& e, int ln, int rn, bool isEx); //插入根节点（重载为非叶节点类型）
   BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx); //e作为x的左孩子（原无）插入（重载为非叶节点类型）
   BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx); //e作为x的右孩子（原无）插入（重载为非叶节点类型）

   BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S); //T作为x左子树接入
   BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S); //T作为x右子树接入
   int remove(BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
   bool operator< ( BinTree<T> const& t ) //比较器（其余自行补充）
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //判等器
   { return _root && t._root && ( _root == t._root ); }
}; //BinTree


template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e )
{ _size = 1; return _root = new BinNode<T> ( e ); } //将e当作根节点插入空的二叉树

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e )
{ 
	_size++; 
	return x->lc = new BinNode<T> (e); } //e插入为x的左孩子

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e )
{ _size++; return x->rc= new BinNode<T>(e); } //e插入为x的右孩子

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e, int ln, int rn, bool isEx) //重载
{
	_size = 1;
	return _root = new BinNode<T>(e, ln, rn, isEx);
} //将e当作根节点插入空的二叉树

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx)//重载
{
	_size++;
	x->lc = new BinNode<T>(e, ln, rn, isEx);
	return x->lc;
} //e插入为x的左孩子

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx)//重载
{
	_size++; 
	x->rc = new BinNode<T>(e, ln, rn, isEx);
	return x->rc;
} //e插入为x的右孩子



template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
int BinTree<T>::remove(BinNodePosi(T) x) { //assert: x为二叉树中的合法位置
	//FromParentTo(*x) = NULL; //切断来自父节点的指针
	int n = removeAt(x); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
}
template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt(BinNodePosi(T) x) { //assert: x为二叉树中的合法位置
	if (!x) return 0; //递归基：空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左、右子树
	release(x->data); release(x); return n; //释放被摘除节点，并返回删除节点总数
}

template <typename T> //二叉树子树接入算法：将S当作节点x的左子树接入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) { //x->lc == NULL
	if (x->lc = S->_root) x->lc->parent = x; //接入
	_size += S->_size;  //更新全树规模与x所有祖先的高度
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //释放原树，返回接入位置
}

template <typename T> //二叉树子树接入算法：将S当作节点x的右子树接入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) { //x->rc == NULL
	if (x->rc = S->_root) x->rc->parent = x; //接入
	_size += S->_size; //更新全树规模与x所有祖先的高度
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //释放原树，返回接入位置
}

