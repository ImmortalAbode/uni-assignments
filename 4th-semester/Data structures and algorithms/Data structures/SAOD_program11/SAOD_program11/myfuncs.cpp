#include <iostream>
#include <string>

#include "myfuncs.h"
#include "BinaryTree.h"

//������� ��� ������ �������� � �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� � �������?" << std::endl;
	std::cout << "1 - �������� ������� � �������� ������.\n"
		<< "2 - ���������� ����� ������ �� ������ ��������� ������ � ������ �������.\n"
		<< "3 - ���������� ����� ������ �� ������ ��������� ������ � ������������ �������.\n"
		<< "4 - ���������� ����� ������ �� ������ ��������� ������ � �������-������������ �������.\n"
		<< "5 - ����� ��������� �������� ����� ������ ��������� ������.\n"
		<< "6 - ��������� ���������� ������.\n"
		<< "7 - ����� �� ���������.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
			return choice[0];
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 7. ��������� ����. " << std::endl;
	}
}

//������� ��������� � �������� ����������������� �����.
int convertStrToInt(std::string const& convertStr)
{
	int number{};
	for (int i{}; i < convertStr.length();i++)
	{
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i);
	}
	return number;
}
bool checkStrIsNumeric(std::string const& userStr)
{
	for (int i{}; i < userStr.length();i++)
	{
		if ((i == 0) && (userStr[i] == '0'))
			return false;
		if (userStr[i] < '0' || userStr[i] > '9')
			return false;
	}
	return true;
}
std::string getUserInput()
{
	std::cout << "������� ���������� ������ �������� ����������������� ������: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����������� �����: ";
		else if (checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "������ �����. ������� ����������� �����: ";
	}
}

//������� ������ ���.
//� ������ �������.
void Forward(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		Forward(root_ptr->left, level + 1);
		Forward(root_ptr->right, level + 1);
	}
}
//� ������������ �������.
void Symmetrical(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		Symmetrical(root_ptr->left, level + 1);
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		Symmetrical(root_ptr->right, level + 1);
	}
}
//� �������-������������ �������.
void BackSymmetrical(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		BackSymmetrical(root_ptr->right, level + 1);
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		BackSymmetrical(root_ptr->left, level + 1);
	}
}

//������� ���������� ������ � ����.
void clearTreeNodes(TreeNode*& root_ptr)
{
	if (root_ptr != nullptr)
	{
		clearTreeNodes(root_ptr->left);
		clearTreeNodes(root_ptr->right);
		delete root_ptr;
	}
}
void clearBinaryTree(BinaryTree*& ABT)
{
	clearTreeNodes(ABT->root);
	delete ABT;
	std::cout << "��� ���������� ������ ���� ���������� � ����. �������� ���������..." << std::endl;
}

void searchNodeABT(TreeNode* root_ptr)
{
	TreeNode* parentNode{ nullptr };
	bool isNumber = false;
	Forward(root_ptr, 0);
	std::cout << "������� �������� �������, ������� ������ ����� � ������������ �������� ������: ";
	std::string userStr{ getUserValueNode() };
	searchNode(root_ptr, convertStrToInt(userStr), isNumber, parentNode);
	TreeNode* desired_point{ parentNode };
	if (desired_point != nullptr)
		std::cout << "�������� ���� ������� �� ��������� " << desired_point->value << " ���� ������� �� ������ " << desired_point->level << "." << std::endl;
	else
		std::cout << "� ������� ������������ �������� ������ ��� ������ � ������ �������������� ������." << std::endl;
}
void searchNode(TreeNode* currentNode, const int& number, bool& isNumber, TreeNode*& parentNode)
{
	if (!isNumber)
	{
		if (currentNode != nullptr)
		{
			if (currentNode->value == number)
			{
				isNumber = true;
				parentNode = currentNode;
			}
			else
			{
				searchNode(currentNode->left, number, isNumber, parentNode);
				searchNode(currentNode->right, number, isNumber, parentNode);
			}
		}
	}
}
std::string getUserValueNode()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����������� �����: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0)
			return userStr;
		else
			std::cout << "������ �����. ������� ����������� �����: ";
	}
}
std::string getUserChoice()
{
	std::cout << "�� ������ �������� ������ (l) ��� ������� (r) ������� ������� �������? ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� 'l' ��� 'r': ";
		else if (userStr == "l" || userStr == "r")
			return userStr;
		else
			std::cout << "������ �����. ������� 'l' ��� 'r': ";
	}
}
void createNewNode(BinaryTree*& ABT)
{	
	if (ABT->root != nullptr)
	{
		TreeNode* parentNode{ nullptr };
		bool flag = false;
		Forward(ABT->root, 0);
		std::cout << "������� ������� ��������� ������, ����� ������� ������ �������� �������: ";
		std::string userValue{ getUserValueNode() };
		searchNode(ABT->root, convertStrToInt(userValue), flag, parentNode);
		TreeNode* desired_point{ parentNode }; 
		if (desired_point != nullptr)
		{
			std::cout << "������� �������� ���� ������� � ������� " << desired_point->value << " �� ������ " << desired_point->level << "." << std::endl;
			if (desired_point->left != nullptr && desired_point->right != nullptr)
			{
				std::cout << "�������� ���� ������� ��� ����� ���� ��������. ���������� ����� ����������." << std::endl;
			}
			else
			{
				TreeNode* new_point = new TreeNode{};
				std::cout << "������� ������� ��������� ������ - �������: ";
				std::string new_value{ getUserValueNode() };
				new_point->level = desired_point->level + 1;
				new_point->value = convertStrToInt(new_value);
				ABT->N++;

				if (desired_point->left == nullptr && desired_point->right == nullptr)
				{
					std::string userChoice{ getUserChoice() };
					if (userChoice == "l")
						desired_point->left = new_point;
					else if (userChoice == "r")
						desired_point->right = new_point;
				}
				else if (desired_point->left == nullptr) desired_point->left = new_point;
				else desired_point->right = new_point;
				std::cout << "����� ������� "<< new_point->value << " ���� ������� ��������� � �������� ������." << std::endl;
			}
		}
		else
			std::cout << "� ������� ������������ �������� ������ ��� �������� �������� �������." << std::endl;
	}
	else
	{
		std::cout << "���� �������� ������ �� ������ ������ ������, �������� �������� �������: ";
		std::string userRoot{ getUserValueNode() };
		ABT->root = new TreeNode{};
		ABT->root->level = 0;
		ABT->root->value = convertStrToInt(userRoot);
		ABT->N++;
		std::cout << "������ ������ �� ��������� " << ABT->root->value << " ��� ������� ������." << std::endl;
	}
}
void DestroyAllTree(TreeNode*& root_ptr)
{
	if (root_ptr != nullptr)
	{
		DestroyAllTree(root_ptr->left);
		DestroyAllTree(root_ptr->right);
		std::cout << "������� " << root_ptr->value << " ���� ������� �������." << std::endl;
		delete root_ptr;
	}
}