#include <iostream>
#include <string>

#include "myfuncs.h"
#include "BinarySearchTree.h"

//����.
float getRandomNumber(float min, float max) //��������� ���������� ����� ����� ��������� min � max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//������� ��� ������ �������� � �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� � �������� ������� ������?" << std::endl;
	std::cout << "1 - �������� ������ � �������� ������ ������ �� ���������� �������.\n"
		<< "2 - ���������� � ������ ����� ������� � �������� ������������� ��������� �����.\n"
		<< "3 - ����� � ������ ������� � �������� ������.\n"
		<< "4 - ���������� ����� ������ � ��������� ���� (�������-������������ ������).\n"
		<< "5 - ����� ���� ������ � ���� ������ � ������� ����������� �� ������ (������������ ������).\n"
		<< "6 - �������� ������� � �������� ������.\n"
		<< "7 - ���������� ��� �������� ������ ������.\n"
		<< "8 - ����� �� ���������.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
			return choice[0];
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 8. ��������� ����. " << std::endl;
	}
}

//������� ��������� � �������� ����������������� �����.
int convertStrToInt(std::string const& convertStr)
{
	int number{};
	for (int i{}; i < convertStr.length();i++)
	{
		number += static_cast<int>((convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i));
	}
	return number;
}
bool checkStrIsNumeric(std::string const& userStr)
{
	for (int i{}; i < userStr.length();i++)
		if (userStr[i] < '0' || userStr[i] > '9')
			return false;
	return true;
}
std::string getUserInput()
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

//���������� ������� ������ � �������� ������� ������.
void searchNodeBST(TreeNode* root_ptr)
{
	TreeNode* foundNode{ nullptr };
	bool isNumber = false;
	std::cout << "���� �������� ������ ������ � ��������� ���� �������-������������ ��������: " << std::endl;
	BackSymmetricalReadablePrint(root_ptr, 0);
	std::cout << "������� �������� ����� �������, ������� ������ ����� � �������� ������ ������: ";
	std::string userStr{ getUserValueNode() };
	searchNode(root_ptr, convertStrToInt(userStr), isNumber, foundNode);
	if (foundNode != nullptr)
		std::cout << "�������� ���� ������� �� ��������� ����� " << foundNode->value << "(" << foundNode->count_of_appearances << ")" << " ���� ������� ������� � �������� ������ ������." << std::endl;
	else
		std::cout << "� ������� �������� ������ ������ ��� ������ � ������ ������." << std::endl;
}
void createBST(BinarySearchTree*& ptr_BST)
{
	std::cout << "������� ���������� ������ � �������� ������ ������: ";
	std::string UserStr{ getUserInput() };
	std::cout << "�� ������ �������� ������� ���������� (1) ��� ��-���������� (2)?: ";
	char TypeOfAddition{ getChoiceAdd() };
	if (TypeOfAddition == '1')
	{
		for (int i{};i < convertStrToInt(UserStr);i++)
		{
			int new_value{ static_cast<int>(getRandomNumber(0,99)) };
			if (ptr_BST->root == nullptr)
			{
				try
				{
					ptr_BST->root = new TreeNode{};
					ptr_BST->root->value = static_cast<int>(new_value); //new_value. ��������� ���������.
					ptr_BST->root->count_of_appearances = 1;
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
					std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
					DestroyAllTree(ptr_BST->root);
					exit(-1);
				}
			}
			else
				AddNodeRecursive(ptr_BST->root, nullptr, new_value);
			ptr_BST->N++;
		}
	}
	else
	{
		for (int i{};i < convertStrToInt(UserStr);i++)
		{
			int new_value{ static_cast<int>(getRandomNumber(0,99)) };
			AddNodeNonRecursive(ptr_BST, new_value);
		}
	}
	std::cout << "�������� ������ ������ � ����������� ������ " << ptr_BST->N << " ���� ������� �������." << std::endl;
}
void AddOneNodeToBST(BinarySearchTree*& ptr_BST)
{
	std::cout << "������� ���� �������, ������� �� ������ �������� � �������� ������ ������: ";
	std::string userValueNode{ getUserValueNode() };
	std::cout << "�� ������ ����������� ����������� (1) ��� ��-����������� (2) ���������� �������?: ";
	char TypeOfAddition{ getChoiceAdd() };
	if (TypeOfAddition == '1')
	{
		AddNodeRecursive(ptr_BST->root, nullptr, convertStrToInt(userValueNode));
		ptr_BST->N++;
	}
	else
		AddNodeNonRecursive(ptr_BST, convertStrToInt(userValueNode));
}
void BackSymmetricalReadablePrint(TreeNode* current_ptr, const int& level)
{
	if (current_ptr != nullptr)
	{
		BackSymmetricalReadablePrint(current_ptr->right, level + 1);
		std::cout << std::string(level * 5, ' ') << current_ptr->value << std::endl;
		BackSymmetricalReadablePrint(current_ptr->left, level + 1);
	}
}
void SymmetricalWithCountInLine(TreeNode* current_ptr)
{
	if (current_ptr != nullptr)
	{
		SymmetricalWithCountInLine(current_ptr->left);
		std::cout << current_ptr->value << "(" << current_ptr->count_of_appearances << ")" << " ";
		SymmetricalWithCountInLine(current_ptr->right);
	}
}
void RemoveNodeFromBST(BinarySearchTree*& ptr_BST)
{
	std::cout << "������� �������� ����� �������, ������� �� ������ ������� �� ��������� ������ ������: ";
	std::string userValueNode{ getUserValueNode() };
	TreeNode* found_node{ nullptr };
	bool flag{ false };
	searchNode(ptr_BST->root, convertStrToInt(userValueNode), flag, found_node);
	if (found_node != nullptr)
	{
		int value_remove_node{ found_node->value };
		int count_of_appearances_remove_node{ found_node->count_of_appearances };
		RemoveNode(ptr_BST->root, found_node, convertStrToInt(userValueNode));
		ptr_BST->N--;
		std::cout << "������� " << value_remove_node << "(" << count_of_appearances_remove_node << ")" << " ��������� ������ ������ ���� ������� �������." << std::endl;
	}
	else
		std::cout << "� ����� �������� ������ ������ ��� ������ � ������ ������." << std::endl;
}
void DestroyAllTree(TreeNode*& root_ptr)
{
	if (root_ptr != nullptr)
	{
		DestroyAllTree(root_ptr->left);
		DestroyAllTree(root_ptr->right);
		std::cout << "������� " << root_ptr->value << "(" << root_ptr->count_of_appearances << ")" << "���� ������� �������." << std::endl;
		delete root_ptr;
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
void clearBinaryTree(BinarySearchTree*& ptr_BST)
{
	clearTreeNodes(ptr_BST->root);
	delete ptr_BST;
	std::cout << "��� ���������� ������ ���� ���������� � ����. �������� ���������..." << std::endl;
}

//�������� ������� ��� ������ � �������� ������� ������.
char getChoiceAdd()
{
	while (true)
	{
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
			return choice[0];
		else
			std::cout << "�� ������ ������ 1 (����������� ����������) ��� 2 (��-����������� ����������). ��������� ����: ";
	}
}
std::string getUserValueNode()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����������� ����� �� 0 �� 99: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) >= 0 && convertStrToInt(userStr) <= 99)
			return userStr;
		else
			std::cout << "������ �����. ������� ����������� ����� �� 0 �� 99: ";
	}
}
void searchNode(TreeNode* currentNode, const int& number, bool& isNumber, TreeNode*& foundNode)
{
	if (!isNumber)
	{
		if (currentNode != nullptr)
		{
			if (currentNode->value == number)
			{
				isNumber = true;
				foundNode = currentNode;
			}
			else
			{
				if (number < currentNode->value)
					searchNode(currentNode->left, number, isNumber, foundNode);
				else
					searchNode(currentNode->right, number, isNumber, foundNode);
			}
		}
	}
}
void AddNodeRecursive(TreeNode*& current_node, TreeNode* parent_node, const int& new_value)
{
	if (current_node == nullptr)
	{
		try
		{
			current_node = new TreeNode{};
			current_node->value = new_value;
			current_node->count_of_appearances = 1;
			current_node->parent = parent_node;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
			while (current_node->parent != nullptr)
				current_node = current_node->parent;
			DestroyAllTree(current_node);
			exit(-1);
		}
	}
	else
	{
		if (new_value < current_node->value)
			AddNodeRecursive(current_node->left, current_node, new_value);
		else if (new_value > current_node->value)
			AddNodeRecursive(current_node->right, current_node, new_value);
		else
			current_node->count_of_appearances++;
	}
}
void AddNodeNonRecursive(BinarySearchTree*& ptr_BST, const int& new_value)
{
	if (ptr_BST->root != nullptr)
	{
		TreeNode* parent_node{ nullptr };
		TreeNode* current_node{ ptr_BST->root };

		while (current_node != nullptr)
		{
			parent_node = current_node;
			if (new_value < current_node->value)
				current_node = current_node->left;
			else if (new_value > current_node->value)
				current_node = current_node->right;
			else
			{
				current_node->count_of_appearances++;
				ptr_BST->N++;
				return;
			}
		}

		try
		{
			current_node = new TreeNode{};
			current_node->value = new_value;
			current_node->count_of_appearances = 1;
			current_node->parent = parent_node;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
			DestroyAllTree(ptr_BST->root);
			exit(-1);
		}

		ptr_BST->N++;

		if (current_node->value < parent_node->value)
			parent_node->left = current_node;
		else
			parent_node->right = current_node;
	}
	else
	{
		try
		{
			ptr_BST->root = new TreeNode{};
			ptr_BST->root->value = new_value;
			ptr_BST->root->count_of_appearances = 1;
			ptr_BST->N++;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
			DestroyAllTree(ptr_BST->root);
			exit(-1);
		}
	}
}
TreeNode* findMinimumSubTree(TreeNode* minimum_node)
{
	while (minimum_node->left != nullptr)
		minimum_node = minimum_node->left;
	return minimum_node;
}
void MovingNodes(TreeNode*& ptr_root, TreeNode*& remove_node, TreeNode*& child_node_remove_node)
{
	if (remove_node->parent == nullptr)
		ptr_root = child_node_remove_node;
	else if (remove_node == remove_node->parent->left)
		remove_node->parent->left = child_node_remove_node;
	else
		remove_node->parent->right = child_node_remove_node;

	if (child_node_remove_node != nullptr)
		child_node_remove_node->parent = remove_node->parent;
}
void RemoveNode(TreeNode*& ptr_root, TreeNode*& remove_node, const int& remove_value)
{
	if (remove_node->left == nullptr)
		MovingNodes(ptr_root, remove_node, remove_node->right);
	else if (remove_node->right == nullptr)
		MovingNodes(ptr_root, remove_node, remove_node->left);
	else
	{
		TreeNode* remove_node_successor{ findMinimumSubTree(remove_node->right) };

		if (remove_node_successor->parent != remove_node)
		{
			MovingNodes(ptr_root, remove_node_successor, remove_node_successor->right);
			remove_node_successor->right = remove_node->right;
			remove_node_successor->right->parent = remove_node_successor;
		}

		MovingNodes(ptr_root, remove_node, remove_node_successor);
		remove_node_successor->left = remove_node->left;
		remove_node_successor->left->parent = remove_node_successor;
	}
	delete remove_node;
}