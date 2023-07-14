#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct SubNode
{
	int data{};
	SubNode* Next{ nullptr };
	SubNode* Prev{ nullptr };
};

struct Node
{
	int ListData{};
	int count{};
	SubNode* subHead_ptr{ nullptr };
	Node* Next{ nullptr };
	Node* Prev{ nullptr };
};

struct MainList
{
	int count{};
	Node* Head_ptr{ nullptr };
};

#endif /*MYSTRUCT_H_*/