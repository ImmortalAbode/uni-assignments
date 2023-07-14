#ifndef BINARYTREE_H_
#define BINARYTREE_H_

struct TreeNode
{
	int value{};
	TreeNode* left{ nullptr };
	TreeNode* right{ nullptr };
};

struct BinaryTree
{
	int N{};
	TreeNode* root{ nullptr };
};

#endif /*BINARYTREE_H_*/