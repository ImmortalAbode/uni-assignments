#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int data{};
	Node* Next{ nullptr };
	Node* Prev{ nullptr };
};

struct List
{
	int count{};
	Node* Head_ptr{ nullptr };
};

#endif /*MYSTRUCT_H_*/