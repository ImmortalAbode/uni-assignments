#include <iostream>

#include "constants.h"
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//����� ���������� � �������.
	prePrint();
	printDash();
	//���������� �������� �������� �������, ������ � ���������� ����������� x0.
	double epsilon{}, deltha{}, approximate_x0{};
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
			getInitOfApproximation(approximate_x0);
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, deltha, approximate_x0);
			//����� ������� (��).
			NewtonMethod(epsilon, deltha, approximate_x0);
			//���������������� ����� ������� (���).
			modifiedNewtonMethod(epsilon, deltha, approximate_x0);

			printDash();

			//������� �������� ������� pow(10, -5) � ������ pow(10, -5).
			epsilon = 0.00001;
			deltha = 0.00001;
			std::cout << "�������� ������� �� ���������: " << epsilon << std::endl;
			std::cout << "�������� ������ �� ���������: " << epsilon << std::endl;
			//������� ���������� �����������.
			std::cout << "�������� ��������� �����������: " << std::endl;
			std::cout << "x_(0) = " << approximate_x0 << std::endl;
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, deltha, approximate_x0);
			//����� ������� (��).
			NewtonMethod(epsilon, deltha, approximate_x0);
			//���������������� ����� ������� (���).
			modifiedNewtonMethod(epsilon, deltha, approximate_x0);
			break;
		case '2':
			//������� �������� �������.
			epsilon = getEpsilon();
			//������� �������� ������.
			deltha = getDeltha();
			//������� ���������� �����������.
			getInitOfApproximation(approximate_x0);
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, deltha, approximate_x0);
			//����� ������� (��).
			NewtonMethod(epsilon, deltha, approximate_x0);
			//���������������� ����� ������� (���).
			modifiedNewtonMethod(epsilon, deltha, approximate_x0);
			break;
		case '3':
			std::cout << "�������� ��������� . . ." << std::endl;
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}