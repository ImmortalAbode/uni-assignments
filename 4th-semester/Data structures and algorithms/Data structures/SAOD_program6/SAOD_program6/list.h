#ifndef LIST_H_
#define LIST_H_

struct Node
{
	int data{};
	Node* Next{ nullptr };
};

struct List
{
	int count{};
	Node* Head_ptr{ nullptr };
};

#endif /*LIST_H_*/