/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once
#include "release.h"
#include "DataHead.h"
typedef int Rank; //秩
#define DEFAULT_CAPACITY  8 //默认的初始容量（实际应用中可设置为更大）
template <typename T> class Vector { //向量模板类
protected:
   Rank _size; int _capacity;  T* _elem; //规模、容量、数据区
   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand(); //空间不足时扩容
   void shrink(); //装填因子过小时压缩
public:
// 构造函数
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
// 析构函数
   ~Vector() { delete[] _elem; } //释放内部空间
// 只读访问接口
   Rank size() const { return _size; } //规模
   bool empty() const { return !_size; } //判空
   T& operator[] (Rank r) const { return _elem[r]; } //重载下标操作符，可以类似于数组形式引用各元素
   Vector<T> & operator= (Vector<T> const& x);//重载赋值操作符，以便直接克隆向量
// 可写访问接口
   T remove ( Rank r ); //删除秩为r的元素
   int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
   Rank insert ( Rank r, T const& e ); //插入元素
   Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
// 遍历
   void print() { for (int i = 0;i < _size;i++) printf("%d ", _elem[i]); printf("\n"); }
   void printy() { for (int i = 0;i < _size;i++) printf("%d ", TP[_elem[i]].y); printf("\n"); }

}; //Vector

template <typename T> //元素类型
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //以数组区间A[lo, hi)为蓝本复制向量
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0; //分配空间，规模清零
	while (lo < hi) //A[lo, hi)内的元素逐一
		_elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
}

template <typename T> void Vector<T>::expand() { //向量空间不足时扩容
	if (_size < _capacity) return; //尚未满员时，不必扩容
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //不低于最小容量
	T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
							   /*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
	delete[] oldElem; //释放原空间
}

template <typename T> void Vector<T>::shrink() { //装填因子过小时压缩向量所占空间
	if (_capacity < DEFAULT_CAPACITY << 1) return; //不致收缩到DEFAULT_CAPACITY以下
	if (_size << 2 > _capacity) return; //以25%为界
	T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //容量减半
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制原向量内容
	delete[] oldElem; //释放原空间
}

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V) { //重载
	if (_elem) delete[] _elem; //释放原有内容
	copyFrom(V._elem, 0, V.size()); //整体复制
	return *this; //返回当前对象的引用，以便链式赋值
}

template <typename T> T Vector<T>::remove(Rank r) { //删除向量中秩为r的元素，0 <= r < size
	T e = _elem[r]; //备份被删除元素
	remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
	return e; //返回被删除元素
}

template <typename T> int Vector<T>::remove(Rank lo, Rank hi) { //删除区间[lo, hi)
	if (lo == hi) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0)
	while (hi < _size) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元
	_size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
	shrink(); //若有必要，则缩容
	return hi - lo; //返回被删除元素的数目
}

template <typename T> //将e作为秩为r元素插入
Rank Vector<T>::insert(Rank r, T const& e) { //assert: 0 <= r <= size
	expand(); //若有必要，扩容
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1]; //自后向前，后继元素顺次后移一个单元
	_elem[r] = e; _size++; //置入新元素并更新容量
	return r; //返回秩
}
