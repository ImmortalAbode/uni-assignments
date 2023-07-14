#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

struct TreeNode
{
	int count_of_appearances{};
	int value{};
	TreeNode* parent{ nullptr };
	TreeNode* left{ nullptr };
	TreeNode* right{ nullptr };
};

struct BinarySearchTree
{
	int N{};
	TreeNode* root{ nullptr };
};

#endif /*BINARYSEARCHTREE_H_*/