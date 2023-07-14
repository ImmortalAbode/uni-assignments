#include <iostream>
#include <string>
#include <cstdlib>

#include "myfuncs.h"
#include "BinaryTree.h"

//Функции для выбора операции с деревом.
void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать с деревом?" << std::endl;
	std::cout << "1 - Задать количество вершин идеально сбалансированного дерева.\n"
		<< "2 - Построить идеально сбалансированное дерево.\n"
		<< "3 - Построчный вывод дерева на основе процедуры обхода в прямом порядке.\n"
		<< "4 - Построчный вывод дерева на основе процедуры обхода в симметричном порядке.\n"
		<< "5 - Построчный вывод дерева на основе процедуры обхода в обратно-симметричном порядке.\n"
		<< "6 - Выход из программы.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
			return choice[0];
		else
			std::cout << "Вы должны ввести целое число от 1 до 6. Повторите ввод. " << std::endl;
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
//ГПСЧ.
int getRandomNumber(float min, float max) //Генерация случайного числа между заданными min и max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<int>((rand() * fraction * (max - min + 1) + min));
}

//Функции вывода ИСД.
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
//Функция создания ИСД.
void getNumOfNodes(BinaryTree*& PBT)
{
	std::string userStr{ getUserInput() };
	PBT->N = convertStrToInt(userStr);
}
void BuildPBT(BinaryTree*& PBT)
{
	AddNode(PBT->root, PBT->N);
	std::cout << "Идеально сбалансированное дерево с числом вершин " << PBT->N << " было успешно создано." << std::endl;
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
void clearBinaryTree(BinaryTree*& PBT)
{
	clearTreeNodes(PBT->root);
	delete PBT;
	std::cout << "Вся выделенная память была возвращена в кучу. Закрытие программы..." << std::endl;
}