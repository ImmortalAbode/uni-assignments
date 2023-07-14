#include <iostream>
#include "QueueFuncs.h"
#include "Queue.h"
#include <cstdlib> //��� rand() � srand()
#include <ctime> //��� time()
#include <Windows.h>//��� Sleep()

int main()
{
	std::setlocale(LC_ALL, "Rus");

	//�������� ���� (rand()) � ������������ ������� ��� �������� ��������������� ������������������� ��������� �����
	srand(static_cast<unsigned int>(time(0)));
	std::cout << "������ �������������� ����� ��� �����������." << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;

	int number_operation{ 1 };
	Queue qp{};
	while (true)
	{
		std::cout << number_operation << ": ";
		int push_pop_choice{ getRandomNumber(1, 100) };
		int count_push_pop{ getRandomNumber(1, 3) };
		bool even_choice{};
		push_pop_choice % 2 == 0 ? even_choice = true : even_choice = false;
		
		switch (even_choice)
		{
		case true:
			std::cout << "� ����� ������� ����� �������� (-�) " << count_push_pop << " ����� (-��) ������� (-�)." << std::endl;
			for (int i{}; i < count_push_pop;i++)
			{
				char ASCII{ static_cast<char>(getRandomNumber(65, 90)) };
				push_queue(qp, ASCII);
			}
			break;
		case false:
			std::cout << "�� ������ ������� ����� ������ (-�) " << count_push_pop << " ������� (-a)(-��)." << std::endl;
			for (int i{}; i < count_push_pop;i++)
			{
				if (!IsEmpty(qp))
					pop_queue(qp);
				else
				{
					std::cout << count_push_pop - i << "-�� �������� �������� � ���������� ����������, ��� ��� ������� ����� �����!" << std::endl;
					break;
				}
			}
			break;
		}
		print_queue(qp);
		if (isSymbolQ())
			break;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		number_operation++;
		Sleep(60000);
	}
	clear(qp);
	return 0;
}