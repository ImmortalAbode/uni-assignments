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
	long double epsilon{};
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//���������� ����������, ��������� � �������.
		case '1':

			PrintDash();
			std::cout << "���������� ��������� ������������-������." << std::endl;
			epsilon = getEpsilon();
			LobachevskyGraeffeAlgorithm(epsilon);
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
