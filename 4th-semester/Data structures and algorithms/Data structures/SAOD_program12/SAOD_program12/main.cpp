#include <iostream>
#include <string>
#include <ctime>

#include "BinarySearchTree.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//�������� ���� (rand()) � ������������ ������� ��� �������� ��������������� ������������������� ��������� �����
	srand(static_cast<unsigned int>(time(0)));

	BinarySearchTree* ptr_BST = new BinarySearchTree{};

	bool create{ false };
	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			if (!create)
			{
				createBST(ptr_BST);
				create = true;
			}
			else
				std::cout << "�������� ������ ������ ��� ���� �������!" << std::endl;
			break;
		case '2':
			if (create)
				AddOneNodeToBST(ptr_BST);
			else 
				std::cout << "������� ����� ������� �������� ������ ������." << std::endl;
			break;
		case '3':
			if (create)
				searchNodeBST(ptr_BST->root);
			else 
				std::cout << "������� ����� ������� �������� ������ ������." << std::endl;
			break;
		case '4':
			if (create)
			{
				std::cout << std::endl;
				BackSymmetricalReadablePrint(ptr_BST->root, 0);
			}
			else 
				std::cout << "������� ����� ������� �������� ������ ������." << std::endl;
			break;
		case '5':
			if (create)
			{
				std::cout << std::endl;
				SymmetricalWithCountInLine(ptr_BST->root);
				std::cout << std::endl;
			}
			else
				std::cout << "������� ����� ������� �������� ������ ������." << std::endl;
			break;
		case '6':
			if (create)
				RemoveNodeFromBST(ptr_BST);
			else
				std::cout << "������� ����� ������� �������� ������ ������." << std::endl;
			break;
		case '7':
			if (create)
			{
				DestroyAllTree(ptr_BST->root);
				ptr_BST->N = 0;
				ptr_BST->root = nullptr;
				std::cout << "������ ���� �������. ������ ������� ������." << std::endl;
				create = false;
			}
			else
				std::cout << "������� ����� ������� �������� ������ ������." << std::endl;
			break;
		case '8':
			if (create) clearBinaryTree(ptr_BST);
			else delete ptr_BST;
			cycle = false;
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}