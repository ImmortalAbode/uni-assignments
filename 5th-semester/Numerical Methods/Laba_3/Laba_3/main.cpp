#include <iostream>

#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");

	//����� ���������� � �������.
	prePrint();
	printDash();
	//���������� �������� �������� �������, ������ � �������, ����������� �������� ���������� �����������.
	double epsilon{}, deltha{}, approximate_mass[2]{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//������� �������� ������� pow(10, -3) � ������ pow(10, -3).
			epsilon = 0.001;
			deltha = 0.001;
			std::cout << "�������� ������� �� ���������: " << epsilon << std::endl;
			std::cout << "�������� ������ �� ���������: " << deltha << std::endl;
			//������� ���������� �����������.
			getInitOfApproximation_v2(approximate_mass);
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, deltha, approximate_mass);
			//����� ������� (��).
			NewtonMethod(epsilon, deltha, approximate_mass);
			//���������������� ����� ������� (���).
			modifiedNewtonMethod(epsilon, deltha, approximate_mass);

			printDash();

			//������� �������� ������� pow(10, -5) � ������ pow(10, -5).
			epsilon = 0.00001;
			deltha = 0.00001;
			std::cout << "�������� ������� �� ���������: " << epsilon << std::endl;
			std::cout << "�������� ������ �� ���������: " << epsilon << std::endl;
			//������� ���������� �����������.
			std::cout << "�������� ��������� �����������: " << std::endl;
			std::cout << "x^(0) = " << approximate_mass[0] << std::endl;
			std::cout << "y^(0) = " << approximate_mass[1] << std::endl;
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, deltha, approximate_mass);
			//����� ������� (��).
			NewtonMethod(epsilon, deltha, approximate_mass);
			//���������������� ����� ������� (���).
			modifiedNewtonMethod(epsilon, deltha, approximate_mass);
			break;
		case '2':
			//������� �������� �������.
			epsilon = getEpsilon();
			//������� �������� ������.
			deltha = getDeltha();
			//������� ���������� �����������.
			getInitOfApproximation(approximate_mass);
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, deltha, approximate_mass);
			//����� ������� (��).
			NewtonMethod(epsilon, deltha, approximate_mass);
			//���������������� ����� ������� (���).
			modifiedNewtonMethod(epsilon, deltha, approximate_mass);
			break;
		case '3':
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