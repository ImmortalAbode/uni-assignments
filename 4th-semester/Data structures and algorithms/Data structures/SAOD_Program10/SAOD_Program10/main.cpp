#include <iostream>
#include <string>
#include <ctime>

#include "BinaryTree.h"
#include "myfuncs.h"
#include "stack.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//�������� ���� (rand()) � ������������ ������� ��� �������� ��������������� ������������������� ��������� �����
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
				std::cout << "������� �������� ���������� ������ ���." << std::endl;
			break;
		case '3':
			if (create)
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � ������ �������:" << std::endl;
				Forward(PBT->root, 0);
			}
			else std::cout << "������� ����� ������� �������� ���������������� ������." << std::endl;
			break;
		case '4':
			if (create) 
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � ������������ ������� ����������� ����������:" << std::endl;
				Symmetrical(PBT->root, 0);
			}
			else std::cout << "������� ����� ������� �������� ���������������� ������." << std::endl;
			break;
		case '5':
			if (create)
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � ������������ ������� ������������� ����������:" << std::endl;
				NonRecursiveSymmetrical(PBT, sup_stack_ptr);
			}
			else std::cout << "������� ����� ������� �������� ���������������� ������." << std::endl;
			break;
		case '6':
			if (create)
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � �������-������������ �������:" << std::endl;
				BackSymmetrical(PBT->root, 0);
			}
			else std::cout << "������� ����� ������� �������� ���������������� ������." << std::endl;
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