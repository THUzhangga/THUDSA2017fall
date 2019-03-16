#pragma once
#include "list.h" //以列表为基类，派生出栈模板类
template <typename T> class Stack : public List<T> { //将列表的首/末端作为栈顶/底
public: //size()、empty()以及其它开放接口，均可直接沿用
	void push(T const& e) { this->insertAsLast(e); } //入栈：等效于将新元素作为列表的首元素插入
	T pop() { return this->remove(this->last()); } //出栈：等效于删除列表的首元素
	T& top() { return this->last()->data; } //取顶：直接返回列表的首元素
};
