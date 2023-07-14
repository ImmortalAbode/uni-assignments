#include <iostream>
#include <string>
#include <cstdlib>

#include "myfuncs.h"
#include "BinaryTree.h"

//������� ��� ������ �������� � �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� � �������?" << std::endl;
	std::cout << "1 - ������ ���������� ������ �������� ����������������� ������.\n"
		<< "2 - ��������� �������� ���������������� ������.\n"
		<< "3 - ���������� ����� ������ �� ������ ��������� ������ � ������ �������.\n"
		<< "4 - ���������� ����� ������ �� ������ ��������� ������ � ������������ ������� ����������� ����������.\n"
		<< "5 - ���������� ����� ������ �� ������ ��������� ������ � ������������ ������� ������������� ����������.\n"
		<< "6 - ���������� ����� ������ �� ������ ��������� ������ � �������-������������ �������.\n"
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
//����.
int getRandomNumber(float min, float max) //��������� ���������� ����� ����� ��������� min � max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<int>((rand() * fraction * (max - min + 1) + min));
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
//� ������������ ������� ����������� ����������.
void Symmetrical(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		Symmetrical(root_ptr->left, level + 1);
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		Symmetrical(root_ptr->right, level + 1);
	}
}
//� ������������ ������� ������������� ����������.
void NonRecursiveSymmetrical(BinaryTree*& PBT, Stack*& sup_stack_ptr)
{
	TreeNode* current_point{ PBT->root };
	int level{};

	while (true)
	{
		while (current_point != nullptr)
		{
			try
			{
				Node* new_node = new Node{};
				new_node->level = level;
				new_node->passed_point = current_point;
				new_node->next = sup_stack_ptr->head_ptr;
				sup_stack_ptr->head_ptr = new_node;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
				clearBinaryTree(PBT);
				clearStack(sup_stack_ptr);
				exit(-1);
			}
			current_point = current_point->left;
			level++;
		}
		if (sup_stack_ptr->head_ptr == nullptr)
			break;
		else
		{
			current_point = sup_stack_ptr->head_ptr->passed_point;
			level = sup_stack_ptr->head_ptr->level;
			std::cout << std::string(level * 5, ' ') << current_point->value << std::endl;
			Node* del_node{ sup_stack_ptr->head_ptr };
			sup_stack_ptr->head_ptr = sup_stack_ptr->head_ptr->next;
			delete del_node;

			current_point = current_point->right;
			level++;
		}
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
//������� �������� ���.
void getNumOfNodes(BinaryTree*& PBT)
{
	std::string userStr{ getUserInput() };
	PBT->N = convertStrToInt(userStr);
}
void BuildPBT(BinaryTree*& PBT)
{
	AddNode(PBT->root, PBT->N);
	std::cout << "�������� ���������������� ������ � ������ ������ " << PBT->N << " ���� ������� �������." << std::endl;
}
void AddNode(TreeNode*& root_ptr, const int& N)
{
	if (N != 0)
	{
		root_ptr = new TreeNode{};
		root_ptr->value = getRandomNumber(0, 99);
		AddNode(root_ptr->left, N / 2);
		AddNode(root_ptr->right, N - N / 2 - 1);
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
void clearBinaryTree(BinaryTree*& PBT)
{
	clearTreeNodes(PBT->root);
	delete PBT;
	std::cout << "��� ���������� ������ ���� ���������� � ����. �������� ���������..." << std::endl;
}
void clearStack(Stack*& sup_stack_ptr)
{
	while (sup_stack_ptr->head_ptr != nullptr)
	{
		Node* temp{ sup_stack_ptr->head_ptr };
		sup_stack_ptr->head_ptr = sup_stack_ptr->head_ptr->next;
		delete temp;
	}
	delete sup_stack_ptr;
}