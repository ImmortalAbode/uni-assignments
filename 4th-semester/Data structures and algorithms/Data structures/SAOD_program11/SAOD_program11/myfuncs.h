#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "BinaryTree.h"

void MenuOfProgram();
char getChoice();

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();

void Forward(TreeNode* root_ptr, const int& level);
void Symmetrical(TreeNode* root_ptr, const int& level);
void BackSymmetrical(TreeNode* root_ptr, const int& level);
void clearTreeNodes(TreeNode*& root_ptr);
void clearBinaryTree(BinaryTree*& PBT);

void searchNodeABT(TreeNode* root_ptr);
void searchNode(TreeNode* currentNode, const int& number, bool& isNumber, TreeNode*& parentNode);
std::string getUserValueNode();
std::string getUserChoice();
void createNewNode(BinaryTree*& ABT);
void DestroyAllTree(TreeNode*& ABT);

#endif /*MYFUNCS_H_*/