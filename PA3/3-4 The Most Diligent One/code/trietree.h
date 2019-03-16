#include <iostream>
#include "vector.h"
int max_num = 0; //记录最大出现次数，每当num发生变化即用之更新max_num，以免最后全局搜索
char* max_str = new char[8];
int len;
//void strcopy(string *a, string b)
//{
//	string *a = new string();
//	for (int i = 0; i < b.length(); i++)
//	{
//		a[i] = b[i];
//	}
//}
class Node {
private:
	char mContent; //储存的字符
	bool mMarker;//标记词语
	Vector<Node*> mChildren;  //下一层字符结点，注意是向量类型
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}
	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; } 
	Node* findChild(char c);
	void appendChild(Node* child) { mChildren.insert(child); }
	Vector<Node*> children() { return mChildren;}
	int num; //记录词语个数
};

class Trie {
public:
	Trie() {root = new Node();}
	~Trie() {} //析构函数
	void addWord(char* s, int length);
	//bool searchWord(string s);
	//void deleteWord(string s);
private:
	Node* root;
};

Node* Node::findChild(char c)
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		Node* tmp = mChildren[i];
		if (tmp->content() == c) { return tmp; }
	}
	return NULL;
}

void Trie::addWord(char* s, int length)
{
	Node* current = root;
	if (s[0] == 0) //字符为空
	{
		current->setWordMarker(); // an empty word
		return;
	}
	for(int i=0;i<length;i++)
	{
		Node* child = current->findChild(s[i]);
		if (child != NULL) { current = child; } //找到第i个字符，深入下一个（层）
		else //否则在孩子里面加一个字符
		{
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
		if (i == length - 1)
		{
			if (current->wordMarker()) //如果已经有该词语
			{
				current->num++;//次数+1
				if (current->num > max_num)
				{
					for (int i = 0; i < length; i++)
					{
						max_str[i] = s[i];
					}
					max_num =current->num;
					len = length;
				}
			}
			else
			{
				current->setWordMarker();
				current->num = 1;
				if (current->num > max_num)
				{
					for (int i = 0; i < length; i++)
					{
						max_str[i] = s[i];
					}
					max_num = current->num;
					len = length;
				}
			}//否则标记该词语，出现次数为1
		}
	}
}

//bool Trie::searchWord(string s)
//{
//	Node* current = root;
//	while (current != NULL)
//	{
//		for (int i = 0; i < s.length(); i++)
//		{
//			Node* tmp = current->findChild(s[i]);
//			if (tmp == NULL)
//				return false;
//			current = tmp;
//		}
//		//如能继续，current到了最后一层
//		printf("num=%d\n", current->num);
//		return current->wordMarker();
//	}
//	return false;
//}