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
	//�������� a ��� ������ �����.
	double a{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//���������� ����������, ��������� � �������.
		case '1':

			//a = GetaValue();
			PrintDash();
			std::cout << std::endl;
			//std::cout << "���������� ���������� ��� a = " << a << std::endl;
			std::cout << "����� �����:" << std::endl;
			GridMethod(1);

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
