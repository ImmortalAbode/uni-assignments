#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "BinaryTree.h"

void MenuOfProgram();
char getChoice();

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();
int getRandomNumber(float min, float max);

void Forward(TreeNode* root_ptr, const int& level);
void Symmetrical(TreeNode* root_ptr, const int& level);
void BackSymmetrical(TreeNode* root_ptr, const int& level);
void getNumOfNodes(BinaryTree*& PBT);
void BuildPBT(BinaryTree*& PBT);
void AddNode(TreeNode*& root_ptr, const int& N);
void clearTreeNodes(TreeNode*& root_ptr);
void clearBinaryTree(BinaryTree*& PBT);

#endif /*MYFUNCS_H_*/