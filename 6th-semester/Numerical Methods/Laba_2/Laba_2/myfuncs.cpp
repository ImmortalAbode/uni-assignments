#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>

#include "constants.h"
#include "myfuncs.h"

/*����� ������� ����� � ������*/
//����� �������������� �����.
void PrintDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//����� ���������� �� ������, �������� � �������.
void PrePrint()
{
	std::cout << std::setw(210) << "������� ������ ��������," << std::endl << std::setw(209) << "������ 4312" << std::endl;
	PrintDash();
	std::cout << "������� ��������������� �������: 10.\n" << std::endl;
	std::cout << "������� ������:\n" << std::endl;
	std::cout << " �������� ���������������� ���������:\n\n\ty'' + 2xy' + 2y = 2(5 - 2x)\n" << std::endl;
	std::cout << " �������� ������� (���������) �������:\n  _\n | -y'(0) + y(0) = 0\n<\n |_ y(1) = 1.38" << std::endl;
}
//���������������� ����.
void PrintMenu()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1. ��������� ���������." << std::endl <<
		"2. ����� �� ���������." << std::endl;
}


/*������� �������� ����������������� �����*/
//������ �������� � ������������.
char GetChoice()
{
	while (true)
	{
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
			return choice[0];
		else
			std::cout << std::endl << "������ �����! ��� ����� ������ ����� ������ ������ � ����������� � ������������������ �������� (�� 1 �� 2). ��������� ����." << std::endl;
	}
}


/*��������������� ������*/
//��������� ������� mass_x �� ���������� x_i.
double* get_mass_x(const int& n, const double& h)
{
	double* mass_x{ new double[n + 1]{} };
	mass_x[0] = a;
	for (int i{ 1 }; i < n + 1;i++)
		mass_x[i] = mass_x[i - 1] + h;
	return mass_x;
}
//��������� ������� mass_p �� ���������� p_i.
double* get_mass_p(const double* const mass_x, const int& n, const double& h)
{
	double* mass_p{ new double[n + 1]{} };
	for (int i{};i < n + 1;i++)
		mass_p[i] = 2 * mass_x[i];
	return mass_p;
}
//��������� ������� mass_q �� ���������� q_i.
double* get_mass_q(const double* const mass_x, const int& n, const double& h)
{
	double* mass_q{ new double[n + 1]{} };
	for (int i{};i < n + 1;i++)
		mass_q[i] = 2;
	return mass_q;
}
//��������� ������� mass_f �� ���������� f_i.
double* get_mass_f(const double* const mass_x, const int& n, const double& h)
{
	double* mass_f{ new double[n + 1]{} };
	for (int i{};i < n + 1;i++)
		mass_f[i] = 2 * (5 - 2 * mass_x[i]);
	return mass_f;
}
//��������� ������� mass_m �� ���������� m_i.
double* get_mass_m(const double* const mass_p, const double* const mass_q, const int& n, const double& h)
{
	double* mass_m{ new double[n + 1]{} };
	mass_m[0] = 0;
	mass_m[n] = 0;
	for (int i{ 1 };i < n;i++)
		mass_m[i] = (2 * pow(h, 2) * mass_q[i] - 4) / (2 + h * mass_p[i]);
	return mass_m;
}
//��������� ������� mass_r �� ���������� r_i.
double* get_mass_r(const double* const mass_p, const int& n, const double& h)
{
	double* mass_r{ new double[n + 1]{} };
	mass_r[0] = 0;
	mass_r[n] = 0;
	for (int i{ 1 };i < n;i++)
		mass_r[i] = (2 - h * mass_p[i]) / (2 + h * mass_p[i]);
	return mass_r;
}
//��������� ������� mass_fi �� ���������� fi_i.
double* get_mass_fi(const double* const mass_p, const double* const mass_f, const int& n, const double& h)
{
	double* mass_fi{ new double[n + 1]{} };
	mass_fi[0] = 0;
	mass_fi[n] = 0;
	for (int i{ 1 };i < n;i++)
		mass_fi[i] = (2 * pow(h, 2) * mass_f[i]) / (2 + h * mass_p[i]);
	return mass_fi;
}
//��������� ������� mass_c �� ���������� c_i.
double* get_mass_c(const double* const mass_m, const double* const mass_r, const int& n, const double& h)
{
	double* mass_c{ new double[n + 1]{} };
	mass_c[0] = alpha_0 / (alpha_1 * h - alpha_0);
	mass_c[n] = 0;
	for (int i{ 1 };i < n;i++)
		mass_c[i] = 1 / (mass_m[i] - mass_r[i] * mass_c[i - 1]);
	return mass_c;
}
//��������� ������� mass_d �� ���������� d_i.
double* get_mass_d(const double* const mass_fi, const double* const mass_r, const double* const mass_c, const int& n, const double& h)
{
	double* mass_d{ new double[n + 1]{} };
	mass_d[0] = ((A * h / alpha_0) == 0.0f) ? 0.0f : A * h / alpha_0;
	mass_d[n] = 0;
	for (int i{ 1 };i < n;i++)
		mass_d[i] = mass_fi[i] - mass_r[i] * mass_c[i - 1] * mass_d[i - 1];
	return mass_d;
}
//��������� ������� mass_y �� ���������� y_i.
double* get_mass_y(const double* const mass_c, const double* const mass_d, const int& n, const double& h)
{
	double* mass_y{ new double[n + 1]{} };
	mass_y[n] = (B * h + beta_0 * mass_c[n - 1] * mass_d[n - 1]) / (beta_0 * (1 + mass_c[n - 1]) + beta_1 * h);
	for (int i{ n - 1 };i >= 0;i--)
		mass_y[i] = mass_c[i] * (mass_d[i] - mass_y[i + 1]);
	return mass_y;
}


/*�������� �������*/
//����� ����� �������.
void PrintTable()
{
	std::cout << std::string(116, '_') << std::endl;
	std::cout << "|" << std::setw(2) << "n " <<
		"|" << std::setw(15) << "x_i      " <<
		"|" << std::setw(15) << "y_i      " <<
		"|" << std::setw(15) << "m_i      " <<
		"|" << std::setw(15) << "r_i      " <<
		"|" << std::setw(15) << "fi_i      " <<
		"|" << std::setw(15) << "c_i      " <<
		"|" << std::setw(15) << "d_i      " <<
		"|" << std::endl;
	std::cout << std::string(116, '_') << std::endl;
}
//����� ��������.
void SweepMethod(const int& n)
{
	//����� �������.
	PrintTable();
	//���������� ���� h.
	double h{ static_cast<double>((b - a) / n) };
	//���������� ����������� ��������.
	double
		/*������ ��� ������ ��������*/
		//������������ ������� x_i.
		* mass_x{ get_mass_x(n, h) },
		//������������ �������� ������������� p_i, q_i, f_i, m_i, r_i, fi_i.
		* mass_p{ get_mass_p(mass_x, n, h) },
		* mass_q{ get_mass_q(mass_x, n, h) },
		* mass_f{ get_mass_f(mass_x, n, h) },
		* mass_m{ get_mass_m(mass_p, mass_q, n, h) },
		* mass_r{ get_mass_r(mass_p, n, h) },
		* mass_fi{ get_mass_fi(mass_p, mass_f, n, h) },
		//������������ �������� ������������� c_i, d_i.
		* mass_c{ get_mass_c(mass_m, mass_r, n, h) },
		* mass_d{ get_mass_d(mass_fi, mass_r, mass_c, n, h) },
		/*�������� ��� ������ ��������*/
		//������������ ������� y_i.
		* mass_y{ get_mass_y(mass_c, mass_d, n, h) };

	//���������� y_0 �� �������.
	double y0{ (A * h - alpha_0 * mass_y[1]) / (alpha_1 * h - alpha_0) };

	/*����� �����������*/
	for (int i{}; i < n + 1;i++)
	{
		std::cout <<
			"|" << std::setw(2) << std::left << i <<
			"|" << std::setw(5) << "" << std::left << std::setw(5) << mass_x[i] << std::setw(5) << "";
		if (i == n)
			std::cout << std::right << "|" << std::setw(15) << std::fixed << std::setprecision(2) << mass_y[i] << std::defaultfloat;
		else
			std::cout << std::right << "|" << std::setw(15) << std::setprecision(10) << mass_y[i];
		if (i == 0 || i == n)
		{
			std::cout << std::right <<
				"|" << std::setw(15) << std::setprecision(10) << "" <<
				"|" << std::setw(15) << std::setprecision(10) << "" <<
				"|" << std::setw(15) << std::setprecision(10) << "";
		}
		else
		{
			std::cout << std::right <<
				"|" << std::setw(15) << std::setprecision(10) << mass_m[i] <<
				"|" << std::setw(15) << std::setprecision(10) << mass_r[i] <<
				"|" << std::setw(15) << std::setprecision(10) << mass_fi[i];
		}
		if (i == n)
		{
			std::cout << std::right <<
				"|" << std::setw(15) << std::setprecision(10) << "";
		}
		else
		{
			std::cout << std::right <<
				"|" << std::setw(15) << std::setprecision(10) << mass_c[i];
		}
		if (i == n)
		{
			std::cout << std::right <<
				"|" << std::setw(15) << std::setprecision(10) << "";
		}
		else
		{
			std::cout << std::right <<
				"|" << std::setw(15) << std::setprecision(10) << mass_d[i];
		}
			std::cout << 
				"|" << std::endl;
		std::cout << std::string(116, '_') << std::endl;
	}

	//��������� y0 (�� �������) � y_i[0] (�� ��������� ���� ������ ��������).
	std::cout << std::endl << "��������� �������� y0 (���������� �� ������� �� ������� �������� �������) � y_i[0] (���������� �� ��������� ���� ������ ��������):" << std::endl;
	std::cout << 
		"y0 = " << std::setprecision(10) << y0 << "\t" << 
		"y_i[0] = " << std::setprecision(10) << mass_y[0] << "\t" << 
		"|y0 - y_i[0]| = " << std::fixed << std::setprecision(10) << abs(y0 - mass_y[0]) << 
		std::endl << std::endl;
	std::cout << std::defaultfloat;

	//������������ ���������� ������������ ������.
	delete[]
		mass_x,
		mass_p,
		mass_q,
		mass_f,
		mass_m,
		mass_r,
		mass_fi,
		mass_c,
		mass_d,
		mass_y;
}