#include <iostream>
#include <string>
#include <iomanip>

#include "constants.h";
#include "myfuncs.h"

/*������� ������ ���������� �� �������*/
//����� �������������� ����������.
void prePrint()
{
	std::cout << std::setw(210) << "������� ������ ��������," << std::setw(210) << "������ 4312" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 3." << std::endl << std::endl;
	std::cout << "�������� ������������ ��������:\n";
	std::cout << "�������� �� " << a << " �� " << b << " ������� y(x) = 3 * sqtr(x) * (1 + sqrt(x)) �� dx." << std::endl;
	std::cout << "������ �������:\n";
	std::cout << "�������������: F(x) = 2 * x * sqrt(x) + 3 / 2 * x ^ 2." << std::endl;
	std::cout << "F(b) - F(a) = (2 * b * sqrt(b) + 3.0 / 2.0 * b * b) - (2 * a * sqrt(a) + 3.0 / 2.0 * a * a) ~ " <<
		(2 * b * sqrt(b) + 3.0 / 2.0 * b * b) - (2 * a * sqrt(a) + 3.0 / 2.0 * a * a) << "." << std::endl;
}
//�������������� �����.
void printDash()
{
	std::cout << std::string(210, '-') << std::endl;
}
//����� ���� �� �������.
void printMenu()
{
	std::cout << "��� �� ������ ������� � ���������?" << std::endl;
	std::cout << "1. ��������� ���������.\n"
		<< "2. ����� �� ���������." << std::endl;
}

/*��������������� �������*/
//������� ������ �������� � ����.
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
		{
			printDash();
			return choice[0];
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 2. ��������� ����. " << std::endl;
	}
}

/*������� ������ �������� ������ ���������*/
//����� ����� �������.
void printTable()
{
	std::cout << std::string(136, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "n" <<
		"|" << std::setw(12) << "I" <<
		"|" << std::setw(15) << "I��." <<
		"|" << std::setw(20) << "|I - I��.|    " <<
		"|" << std::setw(15) << "I��.�.�." <<
		"|" << std::setw(20) << "|I - I��.�.�.|  " <<
		"|" << std::setw(15) << "I��.�.�." <<
		"|" << std::setw(20) << "|I - I��.�.�.|  " <<
		"|" << std::endl;
	std::cout << std::string(136, '_') << std::endl;
}

/*�������� ������� ���������*/
//������� ��������, ������������ ������� ��������, ������������ ������� ������ ��� n=4.
void formulas_for_n_4()
{
	//����� ��� ������� �������� � �����. ������� ��������.
	float h{ static_cast<float>((b - a)) / 4 };
	double 
		y0{ 3 * sqrt(a) * (1 + sqrt(a)) },
		y1{ 3 * sqrt(a + h) * (1 + sqrt(a + h)) },
		y2{ 3 * sqrt(a + 2 * h) * (1 + sqrt(a + 2 * h)) },
		y3{ 3 * sqrt(a + 3 * h) * (1 + sqrt(a + 3 * h)) },
		y4{ 3 * sqrt(b) * (1 + sqrt(b)) };
	//������� ��������. 
	double Itr{ h * ((y0 + y4) / 2 + y1 + y2 + y3) };
	//���������� �������.
	std::cout << 
		"|" << std::setw(10) << "4" <<
		"|" << std::setw(12) << std::setprecision(10) << I <<
		"|" << std::setw(15) << std::setprecision(10) << Itr <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Itr);
	//������������ ������� ��������.
	double Ikvfs{ h / 3 * (y0 + y4 + 4 * (y1 + y3) + 2 * y2) };
	//���������� �������.
	std::cout << 
		"|" << std::setw(15) << std::setprecision(10) << Ikvfs <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfs);
	//������������ ������� ������.
	//������������ ��� ������������ ������� ������.
	const double t1{ -0.86113631 }, t2{ -0.33998104 }, t3{ 0.33998104 }, t4{ 0.86113631 };
	const double A1{ 0.34785484 }, A2{ 0.65214516 }, A3{ 0.65214516 }, A4{ 0.34785484 };
	//����������.
	double Ikvfg{ 0.5 * (
		(A1 * 3 * sqrt(1.5 + 0.5 * t1) * (1 + sqrt(1.5 + 0.5 * t1))) +
		(A2 * 3 * sqrt(1.5 + 0.5 * t2) * (1 + sqrt(1.5 + 0.5 * t2))) +
		(A3 * 3 * sqrt(1.5 + 0.5 * t3) * (1 + sqrt(1.5 + 0.5 * t3))) +
		(A4 * 3 * sqrt(1.5 + 0.5 * t4) * (1 + sqrt(1.5 + 0.5 * t4)))
		) };
	//���������� �������.
	std::cout << 
		"|" << std::setw(15) << std::setprecision(10) << Ikvfg <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfg) <<
		"|" << std::endl;
	std::cout << std::string(136, '_') << std::endl;
}
//������� ��������, ������������ ������� ��������, ������������ ������� ������ ��� n=8.
void formulas_for_n_8()
{
	//����� ��� ������� �������� � �����. ������� ��������.
	float h{ static_cast<float>((b - a)) / 8 };
	double
		y0{ 3 * sqrt(a) * (1 + sqrt(a)) },
		y1{ 3 * sqrt(a + h) * (1 + sqrt(a + h)) },
		y2{ 3 * sqrt(a + 2 * h) * (1 + sqrt(a + 2 * h)) },
		y3{ 3 * sqrt(a + 3 * h) * (1 + sqrt(a + 3 * h)) },
		y4{ 3 * sqrt(a + 4 * h) * (1 + sqrt(a + 4 * h)) },
		y5{ 3 * sqrt(a + 5 * h) * (1 + sqrt(a + 5 * h)) },
		y6{ 3 * sqrt(a + 6 * h) * (1 + sqrt(a + 6 * h)) },
		y7{ 3 * sqrt(a + 7 * h) * (1 + sqrt(a + 7 * h)) },
		y8{ 3 * sqrt(b) * (1 + sqrt(b)) };
	//������� ��������. 
	double Itr{ h * ((y0 + y8) / 2 + y1 + y2 + y3 + y4 + y5 + y6 + y7) };
	//���������� �������.
	std::cout <<
		"|" << std::setw(10) << "8" <<
		"|" << std::setw(12) << std::setprecision(10) << I <<
		"|" << std::setw(15) << std::setprecision(10) << Itr <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Itr);
	//������������ ������� ��������.
	double Ikvfs{ h / 3 * (y0 + y8 + 4 * (y1 + y3 + y5 + y7) + 2 * (y2 + y4 + y6)) };
	//���������� �������.
	std::cout <<
		"|" << std::setw(15) << std::setprecision(10) << Ikvfs <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfs);
	//������������ ������� ������.
	//������������ ��� ������������ ������� ������.
	const double t1{ -0.96028986 }, t2{ -0.79666648 }, t3{ -0.52553242 }, t4{ -0.18343464 }, t5{ 0.18343464 }, t6{ 0.52553242 }, t7{ 0.79666648 }, t8{ 0.96028986 };
	const double A1{ 0.10122854 }, A2{ 0.22238104 }, A3{ 0.31370664 }, A4{ 0.36268378 }, A5{ 0.36268378 }, A6{ 0.31370664 }, A7{ 0.22238104 }, A8{ 0.10122854 };
	//����������.
	double Ikvfg{ 0.5 * (
		(A1 * 3 * sqrt(1.5 + 0.5 * t1) * (1 + sqrt(1.5 + 0.5 * t1))) +
		(A2 * 3 * sqrt(1.5 + 0.5 * t2) * (1 + sqrt(1.5 + 0.5 * t2))) +
		(A3 * 3 * sqrt(1.5 + 0.5 * t3) * (1 + sqrt(1.5 + 0.5 * t3))) +
		(A4 * 3 * sqrt(1.5 + 0.5 * t4) * (1 + sqrt(1.5 + 0.5 * t4))) +
		(A5 * 3 * sqrt(1.5 + 0.5 * t5) * (1 + sqrt(1.5 + 0.5 * t5))) +
		(A6 * 3 * sqrt(1.5 + 0.5 * t6) * (1 + sqrt(1.5 + 0.5 * t6))) +
		(A7 * 3 * sqrt(1.5 + 0.5 * t7) * (1 + sqrt(1.5 + 0.5 * t7))) +
		(A8 * 3 * sqrt(1.5 + 0.5 * t8) * (1 + sqrt(1.5 + 0.5 * t8)))
		) };
	//���������� �������.
	std::cout << 
		"|" << std::setw(15) << std::setprecision(10) << Ikvfg <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfg) <<
		"|" << std::endl;
	std::cout << std::string(136, '_') << std::endl;
}