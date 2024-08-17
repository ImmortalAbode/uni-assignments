#include <iostream>
#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//����� ���������� � �������� �������.
	prePrint();
	printDash();
	int n_values[3]{}, m_values[3]{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			//��������� �������� n � m (3 �������� ���).
			for (int i{}; i < 3; i++)
			{
				n_values[i] = get_n_m_values('n', i);
				m_values[i] = get_n_m_values('m', i);
				std::cout << std::endl;
			}
			//����� �������.
			printTable();
			for (int i{}; i < 3; i++)
				simpsonFormula(n_values[i], m_values[i]);
			break;
			//����� �� ���������.
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	std::system("chcp 866 > nul");
	return 0;
}