#include <iostream>
#include "QueueFuncs.h"
#include "Queue.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	
	Queue qp{};

	bool cycle{ true };
	while (cycle)
	{
		std::cout << "��� �� ������ ������� � ��������?" << std::endl;
		std::cout << "1 - ��������� ������� �������.\n"
			<< "2 - ��������� ������������� �������.\n"
			<< "3 - �������� ������� � ����� �������.\n"
			<< "4 - ������� ������� �� ������ �������.\n"
			<< "5 - ������� ������� ��������� ������� �� �����.\n"
			<< "6 - ����� �� ���������.";
		std::cout << std::endl;

		int choice{};
		while (true)
		{
			choice = getChoice();
			if (choice >= 1 && choice <= 6)
				break;
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 6. ��������� ����: " << std::endl;
		}

		switch (choice)
		{
		case 1:
			if (IsEmpty(qp))
				std::cout << "���� ������� �����." << std::endl;
			else
			{
				if (qp.front <= qp.rear)
					std::cout << "���� ������� �������� " << qp.rear - qp.front + 1 << " ������� (-��)(-�)." << std::endl;
				else 
					std::cout << "���� ������� �������� " << (qp.size - qp.front) + (qp.rear + 1) << " ������� (-��)(-�)." << std::endl;
			}
			break;
		case 2:
			if (IsFull(qp))
				std::cout << "���� ������� ���������." << std::endl;
			else
				if (qp.front != -1 && qp.rear != -1)
					if (qp.front <= qp.rear)
						std::cout << "� ����� ������� ��� �������� ��� ���������� " << qp.size - (qp.rear - qp.front + 1) << " ���������." << std::endl;
					else
						std::cout << "� ����� ������� ��� �������� ��� ���������� " << qp.size - ((qp.size - qp.front) + (qp.rear + 1)) << " ���������." << std::endl;
				else
					std::cout << "� ����� ������� ��� �������� ��� ���������� " << qp.size << " ���������." << std::endl;
			break;
		case 3:
			push(qp);
			break;
		case 4:
			pop(qp);
			break;
		case 5:
			print_queue(qp);
			break;
		case 6:
			clear();
			cycle = false;
			break;
		default:;
		}
		std::cout << std::endl;
	}
	return 0;
}