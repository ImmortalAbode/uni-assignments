#include <iostream>

#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//std::system("color F0");
	//����� ���������� � �������� �������.
	PrePrint();
	PrintDash();
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//���������� ����������, ��������� � �������.
		case '1':

			PrintDash();
			std::cout << "������������ ������� ������� ������ ��� ������������� ����������������� ��������� ������� ������� ������� ��������." << std::endl;
			std::cout << "�������� ����������� ��� n = 10." << std::endl;
			SweepMethod(10);

			PrintDash();
			std::cout << "������������ ������� ������� ������ ��� ������������� ����������������� ��������� ������� ������� ������� ��������." << std::endl;
			std::cout << "�������� ����������� ��� n = 20." << std::endl;
			SweepMethod(20);
			break;
		case '2':
			cycle = false;
			break;
		default:;
		}
		PrintDash();
	}
	std::system("chcp 866 > nul");
	return 0;
}
