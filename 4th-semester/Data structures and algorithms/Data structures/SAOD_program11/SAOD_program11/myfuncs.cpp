#include <iostream>
#include <string>

#include "myfuncs.h"
#include "BinaryTree.h"

//Функции для выбора операции с деревом.
void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать с деревом?" << std::endl;
	std::cout << "1 - Добавить вершину в двоичное дерево.\n"
		<< "2 - Построчный вывод дерева на основе процедуры обхода в прямом порядке.\n"
		<< "3 - Построчный вывод дерева на основе процедуры обхода в симметричном порядке.\n"
		<< "4 - Построчный вывод дерева на основе процедуры обхода в обратно-симметричном порядке.\n"
		<< "5 - Поиск заданного значения среди вершин двоичного дерева.\n"
		<< "6 - Полностью уничтожить дерево.\n"
		<< "7 - Выход из программы.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
			return choice[0];
		else
			std::cout << "Вы должны ввести целое число от 1 до 7. Повторите ввод. " << std::endl;
	}
}

//Функции получения и проверки пользовательского ввода.
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
	std::cout << "Введите количество вершин идеально сбалансированного дерева: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите натуральное число: ";
		else if (checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите натуральное число: ";
	}
}

//Функции вывода ПСД.
//В прямом порядке.
void Forward(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		Forward(root_ptr->left, level + 1);
		Forward(root_ptr->right, level + 1);
	}
}
//В симметричном порядке.
void Symmetrical(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		Symmetrical(root_ptr->left, level + 1);
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		Symmetrical(root_ptr->right, level + 1);
	}
}
//В обратно-симметричном порядке.
void BackSymmetrical(TreeNode* root_ptr, const int& level)
{
	if (root_ptr != nullptr)
	{
		BackSymmetrical(root_ptr->right, level + 1);
		std::cout << std::string(level * 5, ' ') << root_ptr->value << std::endl;
		BackSymmetrical(root_ptr->left, level + 1);
	}
}

//Возврат выделенной памяти в кучу.
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
	std::cout << "Вся выделенная память была возвращена в кучу. Закрытие программы..." << std::endl;
}

void searchNodeABT(TreeNode* root_ptr)
{
	TreeNode* parentNode{ nullptr };
	bool isNumber = false;
	Forward(root_ptr, 0);
	std::cout << "Задайте значение вершины, которое хотите найти в произвольном двоичном дереве: ";
	std::string userStr{ getUserValueNode() };
	searchNode(root_ptr, convertStrToInt(userStr), isNumber, parentNode);
	TreeNode* desired_point{ parentNode };
	if (desired_point != nullptr)
		std::cout << "Заданная вами вершина со значением " << desired_point->value << " была найдена на уровне " << desired_point->level << "." << std::endl;
	else
		std::cout << "В текущем произвольном двоичном дереве нет вершин с данной информационной частью." << std::endl;
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
			std::cout << "Ошибка ввода. Введите натуральное число: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0)
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите натуральное число: ";
	}
}
std::string getUserChoice()
{
	std::cout << "Вы хотите добавить левого (l) или правого (r) потомка текущей вершины? ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите 'l' или 'r': ";
		else if (userStr == "l" || userStr == "r")
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите 'l' или 'r': ";
	}
}
void createNewNode(BinaryTree*& ABT)
{	
	if (ABT->root != nullptr)
	{
		TreeNode* parentNode{ nullptr };
		bool flag = false;
		Forward(ABT->root, 0);
		std::cout << "Задайте вершину двоичного дерева, после которой хотите добавить потомка: ";
		std::string userValue{ getUserValueNode() };
		searchNode(ABT->root, convertStrToInt(userValue), flag, parentNode);
		TreeNode* desired_point{ parentNode }; 
		if (desired_point != nullptr)
		{
			std::cout << "Искомое значение было найдено в вершине " << desired_point->value << " на уровне " << desired_point->level << "." << std::endl;
			if (desired_point->left != nullptr && desired_point->right != nullptr)
			{
				std::cout << "Желаемая вами вершина уже имеет двух потомков. Добавление новых невозможно." << std::endl;
			}
			else
			{
				TreeNode* new_point = new TreeNode{};
				std::cout << "Задайте вершину двоичного дерева - потомка: ";
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
				std::cout << "Новая вершина "<< new_point->value << " была успешно добавлена в двоичное дерево." << std::endl;
			}
		}
		else
			std::cout << "В текущем произвольном двоичном дереве нет искомого значения вершины." << std::endl;
	}
	else
	{
		std::cout << "Ваше двоичное дерево на данный момент пустое, добавьте корневую вершину: ";
		std::string userRoot{ getUserValueNode() };
		ABT->root = new TreeNode{};
		ABT->root->level = 0;
		ABT->root->value = convertStrToInt(userRoot);
		ABT->N++;
		std::cout << "Корень дерева со значением " << ABT->root->value << " был успешно создан." << std::endl;
	}
}
void DestroyAllTree(TreeNode*& root_ptr)
{
	if (root_ptr != nullptr)
	{
		DestroyAllTree(root_ptr->left);
		DestroyAllTree(root_ptr->right);
		std::cout << "Вершина " << root_ptr->value << " была успешно удалена." << std::endl;
		delete root_ptr;
	}
}