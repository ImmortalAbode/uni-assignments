#include <iostream>

#include "StackFuncs.h"
#include "Stack.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	Stack* sp{ nullptr };
	Stack* dopsp{ nullptr };

	bool cycle{ true };
	while (cycle)
	{
		std::cout << "��� �� ������ ������� �� ������?" << std::endl;
		std::cout << "1 - �������� ������� �����.\n"
			<< "2 - ���������� �������� � ������� ��������� �����.\n"
			<< "3 - ���������� ����� ���������� ��������� � �������� ����.\n"
			<< "4 - �������� �������� �� ��������� �����.\n"
			<< "5 - ����� �������� ��������� ����� �� �����.\n"
			<< "6 - ����� ����������� ���������������� ����� ��������� ���������.\n"
			<< "7 - ����� �� ���������.";
		std::cout << std::endl;

		int choice{};
		while (true)
		{
			choice = getChoice();
			if (choice >= 1 && choice <= 7)
				break;
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 7. ��������� ����: " << std::endl;
		}

		switch (choice)
		{
		case 1:
			if (IsEmpty(sp))
				std::cout << "��� ���� ����." << std::endl;
			else
			{
				int count{};
				Stack* temp{ sp };
				while (temp != nullptr)
				{
					count += 1;
					temp = temp->next;
				}
				std::cout << "��� ���� �������� " << count-1 << " ��������� (-�)." << std::endl;
			}
			break;
		case 2:
			push(sp, dopsp);
			break;
		case 3:
			push_random(sp);
			break;
		case 4:
			pop(sp, dopsp);
			break;
		case 5:
			print_stack(sp);
			break;
		case 6:
			print_dopstack(dopsp);
			break;
		case 7:
			clear(sp, dopsp);
			cycle = false;
			break;
		default:;
		}
		std::cout << std::endl;
	}
	return 0;
}