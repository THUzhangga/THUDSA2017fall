#pragma once
#define MAXN 50000

struct data {
	int x, y, t; //x坐标,y坐标,温度
	bool operator >= (const data data2) { return (x > data2.x) || ((x == data2.x) && (y >= data2.y)); } //判断大于等于：当x较大时或者x相等但是p大于等于
	bool operator <= (const data data2) { return (x < data2.x) || ((x == data2.x) && (y <= data2.y)); }
	bool operator == (data data2) { return (x == data2.x) && (y == data2.y); }
	bool operator > (data data2) { return (x > data2.x); }
	bool operator < (data data2) { return (x < data2.x); }

} TP[MAXN]; //