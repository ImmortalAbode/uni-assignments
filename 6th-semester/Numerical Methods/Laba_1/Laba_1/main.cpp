#include <iostream>

#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	std::system("color F0");
	//����� ���������� � �������� �������.
	PrePrint();
	PrintDash();
	double epsilon{};
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
			std::cout << "������������ ������� ������ ���� ������� ������, �����-����� 4-��� ������� �������� � ������� ������." << std::endl;
			std::cout << "�������� ����������� ��� n = 10 ��� �������� ��������� � ������ �����-�����." << std::endl;
			PrintFirstSecondTable(10);

			PrintDash();
			std::cout << "������������ ������� ������ ���� ������� ������, �����-����� 4-��� ������� �������� � ������� ������." << std::endl;
			std::cout << "�������� ����������� ��� n = 20 ��� �������� ��������� � ������ �����-�����." << std::endl;
			PrintFirstSecondTable(20);

			PrintDash();
			epsilon = getEpsilon();
			PrintDash();
			std::cout << "������������ ������� ������ ���� ������� �����-����� 4-��� ������� ��������." << std::endl;
			std::cout << "�������� ����������� ��� n = 10 � ������� ���������� � ��������� ��������� epsilon = " << epsilon << "." << std::endl;
			PrintThirdFourthTable(10, epsilon);

			PrintDash();
			epsilon = getEpsilon();
			PrintDash();
			std::cout << "������������ ������� ������ ���� ������� �����-����� 4-��� ������� ��������." << std::endl;
			std::cout << "�������� ����������� ��� n = 20 � ������� ���������� � ��������� ��������� epsilon = " << epsilon << "." << std::endl;
			PrintThirdFourthTable(20, epsilon);

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
