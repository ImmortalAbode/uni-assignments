#include <iostream>
#include <string>
#include <ctime>

#include "BinaryTree.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//�������� ���� (rand()) � ������������ ������� ��� �������� ��������������� ������������������� ��������� �����
	srand(static_cast<unsigned int>(time(0)));

	BinaryTree* ABT = new BinaryTree{};

	bool create{ false };
	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			createNewNode(ABT);
			create = true;
			break;
		case '2':
			if (create)
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � ������ �������:" << std::endl;
				Forward(ABT->root, 0);
			}
			else std::cout << "������� ����� ������� ������������ �������� ������." << std::endl;
			break;
		case '3':
			if (create)
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � ������������ �������:" << std::endl;
				Symmetrical(ABT->root, 0);
			}
			else std::cout << "������� ����� ������� ������������ �������� ������." << std::endl;
			break;
		case '4':
			if (create)
			{
				std::cout << "���������� ����� ������ �� ������ ��������� ������ � �������-������������ �������:" << std::endl;
				BackSymmetrical(ABT->root, 0);
			}
			else std::cout << "������� ����� ������� ������������ �������� ������." << std::endl;
			break;
		case '5':
			if (create)
			{
				searchNodeABT(ABT->root);
			}
			else std::cout << "������� ����� ������� ������������ �������� ������." << std::endl;
			break;
		case '6':
			if (!create) 
				std::cout << "������ ��� �� ���� �������, ����� ���� ����������� ��� ����������." << std::endl;
			else
			{
				DestroyAllTree(ABT->root);
				ABT->N = 0;
				ABT->root = nullptr;
				std::cout << "������ ���� �������. ������ ������� ������." << std::endl;
				create = false;
			}
			break;
		case '7':
			if (create) clearBinaryTree(ABT);
			else delete ABT;
			cycle = false;
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}