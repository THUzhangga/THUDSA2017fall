#pragma once
#include "vector.h"
#include "DataHead.h"
#define BinNodePosi(T) BinNode<T> *
template <typename T> struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
   T data; //数值
   BinNodePosi(T) lc; BinNodePosi(T) rc; //父节点及左、右孩子
   int left, right; //区间的左右
   bool isExternal; //是否是叶节点
   Vector<int> Y; //存的是总的储存点和温度信息的数组的rank
   //Vector<>
// 构造函数
   BinNode() :
       lc ( NULL ), rc ( NULL ){ } //默认构造函数
   BinNode(T e, int l, int r, bool isExternal, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL) :
	   data(e), left(l), right(r), isExternal(isExternal), lc(lc), rc(rc) { } //默认构造函数


// 操作接口
   BinNodePosi(T) insertAsLC ( T const& ); //作为当前节点的左孩子插入新节点
   BinNodePosi(T) insertAsRC ( T const& ); //作为当前节点的右孩子插入新节点

   BinNodePosi(T) insertAsLC(T const&, int, int, bool); //作为当前节点的左孩子插入新节点(重载)
   BinNodePosi(T) insertAsRC(T const&, int, int, bool); //作为当前节点的右孩子插入新节点(重载)

   BinNodePosi(T) succ(); //取当前节点的直接后继
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e )
{ return lc = new BinNode ( e, this ); } //将e作为当前节点的左孩子插入二叉树

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e )
{ return rc = new BinNode ( e, this ); } //将e作为当前节点的右孩子插入二叉树


template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e, int ln, int rn, bool isEx) // 重载
{
	return lc = new BinNode(e, ln, rn, isEx, this);
} //将e作为当前节点的左孩子插入二叉树

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e, int ln, int rn, bool isEx) // 重载
{
	return rc = new BinNode(e, ln, rn, isEx, this);
} //将e作为当前节点的右孩子插入二叉树

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //定位节点v的直接后继
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

