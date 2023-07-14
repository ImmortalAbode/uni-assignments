#ifndef STACK_H_
#define STACK_H_

#include "BinaryTree.h"

struct Node
{
	int level{ -1 };
	TreeNode* passed_point{ nullptr };
	Node* next{ nullptr };
};

struct Stack
{
	Node* head_ptr{ nullptr };
};

#endif /*STACK_H*/