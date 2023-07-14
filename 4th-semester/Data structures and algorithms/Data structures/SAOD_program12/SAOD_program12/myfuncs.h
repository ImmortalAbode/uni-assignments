#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "BinarySearchTree.h"

float getRandomNumber(float min, float max);
void MenuOfProgram();
char getChoice();

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();

void searchNodeBST(TreeNode* root_ptr);
void createBST(BinarySearchTree*& ptr_BST);
void AddOneNodeToBST(BinarySearchTree*& ptr_BST);
void BackSymmetricalReadablePrint(TreeNode* current_ptr, const int& level);
void SymmetricalWithCountInLine(TreeNode* current_ptr);
void RemoveNodeFromBST(BinarySearchTree*& ptr_BST);
void DestroyAllTree(TreeNode*& root_ptr);
void clearTreeNodes(TreeNode*& root_ptr);
void clearBinaryTree(BinarySearchTree*& ptr_BST);

char getChoiceAdd();
std::string getUserValueNode();
void searchNode(TreeNode* currentNode, const int& number, bool& isNumber, TreeNode*& foundNode);
void AddNodeRecursive(TreeNode*& current_node, TreeNode* parent_node, const int& new_value);
void AddNodeNonRecursive(BinarySearchTree*& ptr_BST, const int& new_value);
TreeNode* findMinimumSubTree(TreeNode* minimum_node);
void MovingNodes(TreeNode*& ptr_root, TreeNode*& remove_node, TreeNode*& child_node_remove_node);
void RemoveNode(TreeNode*& ptr_root, TreeNode*& remove_node, const int& remove_value);



#endif /*MYFUNCS_H_*/