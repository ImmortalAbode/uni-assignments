#include <iostream>
#include <string>
#include <ctime>

#include "BinaryTree.h"
#include "myfuncs.h"
#include "stack.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//Привязка ГПСЧ (rand()) к календарному времени для создания неповторяющихся последовательностей случайных чисел
	srand(static_cast<unsigned int>(time(0)));

	BinaryTree* PBT = new BinaryTree{};
	Stack* sup_stack_ptr = new Stack{};

	bool create{ false };
	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			clearTreeNodes(PBT->root);
			getNumOfNodes(PBT);
			break;
		case '2':
			if (PBT->N > 0)
			{
				create = true;
				BuildPBT(PBT);
			}
			else
				std::cout << "Сначала зайдайте количество вершин ИСД." << std::endl;
			break;
		case '3':
			if (create)
			{
				std::cout << "Построчный вывод дерева на основе процедуры обхода в прямом порядке:" << std::endl;
				Forward(PBT->root, 0);
			}
			else std::cout << "Сначала нужно создать идеально сбалансированное дерево." << std::endl;
			break;
		case '4':
			if (create) 
			{
				std::cout << "Построчный вывод дерева на основе процедуры обхода в симметричном порядке рекурсивным алгоритмом:" << std::endl;
				Symmetrical(PBT->root, 0);
			}
			else std::cout << "Сначала нужно создать идеально сбалансированное дерево." << std::endl;
			break;
		case '5':
			if (create)
			{
				std::cout << "Построчный вывод дерева на основе процедуры обхода в симметричном порядке нерекурсивным алгоритмом:" << std::endl;
				NonRecursiveSymmetrical(PBT, sup_stack_ptr);
			}
			else std::cout << "Сначала нужно создать идеально сбалансированное дерево." << std::endl;
			break;
		case '6':
			if (create)
			{
				std::cout << "Построчный вывод дерева на основе процедуры обхода в обратно-симметричном порядке:" << std::endl;
				BackSymmetrical(PBT->root, 0);
			}
			else std::cout << "Сначала нужно создать идеально сбалансированное дерево." << std::endl;
			break;
		case '7':
			clearBinaryTree(PBT);
			delete sup_stack_ptr;
			cycle = false;
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}