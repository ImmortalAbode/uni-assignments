#include <iostream>

#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//����� ���������� � �������.
	prePrint();
	printDash();
	//���������� �������� �������� ������� � �������, ����������� �������� ���������� �����������.
	double epsilon{}, approximate_mass[3]{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//������� �������� ������� pow(10, -3).
			epsilon = 0.001;
			std::cout << "�������� ������� �� ���������: " << epsilon << std::endl;
			//������� ���������� �����������.
			getInitOfApproximation(approximate_mass);
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, approximate_mass);
			//����� ������� (��).
			seidelMethod(epsilon, approximate_mass);
			//����� ���������� (����������).
			relaxationMethod(epsilon, approximate_mass);

			printDash();

			//������� �������� ������� pow(10, -5).
			epsilon = 0.00001;
			std::cout << "�������� ������� �� ���������: " << epsilon << std::endl;
			//������� ���������� �����������.
			std::cout << "�������� ��������� �����������: " << std::endl;
			std::cout << "x_(0) = " << approximate_mass[0] << std::endl;
			std::cout << "y_(0) = " << approximate_mass[1] << std::endl;
			std::cout << "z_(0) = " << approximate_mass[2] << std::endl;
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, approximate_mass);
			//����� ������� (��).
			seidelMethod(epsilon, approximate_mass);
			//����� ���������� (����������).
			relaxationMethod(epsilon, approximate_mass);
			break;
		case '2':
			//������� �������� �������.
			epsilon = getEpsilon();
			//������� ���������� �����������.
			getInitOfApproximation(approximate_mass);
			/*��������� ������*/
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, approximate_mass);
			//����� ������� (��).
			seidelMethod(epsilon, approximate_mass);
			//����� ���������� (����������).
			relaxationMethod(epsilon, approximate_mass);
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