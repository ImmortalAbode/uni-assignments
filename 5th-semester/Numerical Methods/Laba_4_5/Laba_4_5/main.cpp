#include <iostream>

#include "myfuncs.h"
#include "Constants.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//����� ���������� � �������.
	prePrint();
	printDash();
	//����� ���� ��������, ������������� ������� [a; b]
	long double user_values_of_X[3]{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//���� ������������� 3-� ��������, ������������� ������� [a; b]
			getValuesXFromUser(user_values_of_X);
			//����� ���������� � ���������� ���������.
			printDash();
			std::cout << "�� ������� [" << a << ";" << b << "] ���� ������� ��������� ��������:" << std::endl;
			std::cout << "������ �������� x: " << user_values_of_X[0] << std::endl;
			std::cout << "������ �������� x: " << user_values_of_X[1] << std::endl;
			std::cout << "������ �������� x: " << user_values_of_X[2] << std::endl;

			//����� ������� ��� ����������������.
			std::cout << std::endl << "����������������" << std::endl;
			printTableInterpolation();
			interpolation_formulas(user_values_of_X);

			std::cout << std::endl;

			//����� ������� ��� ���������� �����������������.
			std::cout << std::endl << "��������� �����������������" << std::endl;
			printTableNumericalDefferentiation();
			numerical_differentation_formulas(user_values_of_X);

			break;
		case '2':
			std::cout << "�������� ��������� . . ." << std::endl;
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	std::system("chcp 866 > nul");
	return 0;
}