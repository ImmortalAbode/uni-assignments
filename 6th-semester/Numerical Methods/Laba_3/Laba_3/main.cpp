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
	//�������� S ��� ������� ����� ������ �����.
	double S{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//���������� ����������, ��������� � �������.
		case '1':

			S = getSvalue();
			PrintDash();
			std::cout << std::endl;
			std::cout << "���������� ���������� ��� S = " << S << std::endl;
			std::cout << "����� �����. ����� �����:" << std::endl;
			ExplicitSchema();
			std::cout << std::endl;
			std::cout << "����� �����. ������� �����:" << std::endl;
			ImplicitSchema(S);

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
