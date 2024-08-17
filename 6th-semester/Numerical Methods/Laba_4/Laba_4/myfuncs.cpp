#include <iostream>
#include <iomanip>
#include <string>

#include "myfuncs.h"
#include "constants.h"
#include "math.h"

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
	std::cout << "���������:" << std::endl;
	std::cout << "\tgamma\t=    " << gamma << std::endl;
	std::cout << "\tm\t=   " << m << std::endl;
	std::cout << "\talpha\t=   " << alpha << std::endl;
	std::cout << "\tbeta\t=    " << beta << std::endl;
	std::cout << "\tM\t=   " << M << std::endl;
	std::cout << "\tN\t=    " << N << std::endl;
	std::cout << "��������� �������:\n" << std::endl;
	std::cout << "  _\n | u(x,0) = 0.6e^(-1.1x) + cos(0.6x)\n<\n |_u'_t(x,0) = -1.3e^x + 0.6cos(0.6x)\n" << std::endl;
	std::cout << "��������� �������:\n" << std::endl;
	std::cout << "  _\n | u(0,t) = -1.3t + sin(0.6t)\n<\n |_u(l,t) = e^(1.3t) - 1.2sin(-1.1t) + 1.3\n" << std::endl;
}
//���������������� ����.
void PrintMenu()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1. ��������� ���������." << std::endl <<
		"2. ����� �� ���������." << std::endl;
}


/*������� �������� ����������������� �����*/
//�������� �������� ������������� ������ �� ����������� �������������� � �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	bool negative_number{ false }, separator{ false };
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		if (!separator && i != 0 && (i != tempStr.length() - 1) && (tempStr[i] == '.' || tempStr[i] == ',' || tempStr[i] == '/'))
		{
			separator = true;
			continue;
		}
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//�������������� �������� ������������� ������ � �����.
long double convertStrToNumber(std::string convertStr)
{
	long double number{}, number_for_fraction{};
	bool negative_number{ false }, fraction{ false };
	int separator_index{ -1 }, k{};
	for (int i{}; i < convertStr.length(); i++)
	{
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
		{
			if (convertStr[i] == '/') fraction = true;
			separator_index = i;
			break;
		}
	}
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && convertStr[i] == '-')
		{
			negative_number = true;
			continue;
		}
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
			continue;
		if (separator_index == -1)
			number += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<long double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<long double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_for_fraction += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<long double>(-number) : static_cast<long double>(number);
	else
		return negative_number ? static_cast<long double>(-number / number_for_fraction) : static_cast<long double>(number / number_for_fraction);
}
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
//��������� �������� a �� ������������.
long double GetaValue()
{
	std::cout << "������� �������� a: ";
	std::string S_value{};
	while (true)
	{
		std::getline(std::cin, S_value);
		if (checkStrIsNumeric(S_value))
		{
			long double numeric_S_value{ convertStrToNumber(S_value) };
			return numeric_S_value;
		}
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}

/*�������� �������*/
//����� �������.
void printTable(const double* const& x, const double* const& t, const double* const& u_virtual, const double* const* const& u)
{
	std::cout << std::string(144, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "    t     " << "|";
	for (int i{}; i < n + 1; i++)
	{
		std::cout << std::setw(5) << "x=" << std::fixed << std::setprecision(2) << std::right << x[i] << "  |";
	}
	std::cout << std::endl;
	std::cout << std::string(144, '_') << std::endl;

	std::cout << "|" << "����.����:" << "|";
	for (int i{}; i < n + 1; i++)
	{
		if (i == 0 || i == n)
		{
			std::cout << std::setw(11) << "" << "|";
		}
		else
		{
			if (u_virtual[i] < 0)
				std::cout << std::setw(2) << "";
			else
				std::cout << std::setw(3) << "";
			std::cout << std::setw(6) << std::setprecision(4) << u_virtual[i] << std::setw(2) << "" << "|";

		}
	}
	std::cout << std::endl;
	std::cout << std::string(144, '_') << std::endl;

	for (int j{}; j < n + 1; j++)
	{
		std::cout << "|" << std::setw(3) << " t=" << std::setw(7) << std::left << std::setprecision(4) << t[j] << "|";
		for (int i{}; i < n + 1; i++)
		{
			if (u[i][j] < 0)
				std::cout << std::setw(2) << "";
			else
				std::cout << std::setw(3) << "";
			std::cout << std::setw(6) << std::setprecision(4) << u[i][j] << std::setw(2) << "" << "|";
		}
		std::cout << std::endl;
		std::cout << std::string(144, '_') << std::endl;
	}
}
//����� �����.
void GridMethod(const double& a) {
	//���������� ����� h �� ��� x � k �� ��� t.
	double h{ l / n };
	double k{ h / a };

	//������ �� ���������� xi.
	double* x = new double[n + 1]{};
	//������ �� ���������� tj.
	double* t = new double[n + 1]{};
	//������ �� ���������� u(xi,-1) �� "�����������" ����.
	double* u_virtual = new double[n + 1]{};
	//������ �� ���������� u't_i0=u't(xi,0).
	double* u_t = new double[n + 1]{};
	//��������� ������ �� ���������� uij=u(xi,tj).
	double** u = new double* [n + 1]{};
	for (int iter{}; iter < n + 1; iter++) {
		u[iter] = new double[n + 1]{};
	}

	//���������� ������� �� ���������� xi.
	for (int i{}; i < n + 1; i++) {
		x[i] = i * h;
	}
	//���������� ������� �� ���������� tj.
	for (int j{}; j < n + 1; j++) {
		t[j] = j * k;
	}
	//���������� ���������� ������� ���������� uij=u(xi,tj).
	/*�� ��������� �������*/
	for (int i{}; i < n + 1; i++) {
		u[i][0] = 0.6 * exp(-1.1 * x[i]) + cos(0.6 * x[i]);
	}
	for (int i{ 1 }; i < n; i++) {
		u_t[i] = -1.3 * exp(x[i]) + 0.6 * cos(0.6 * x[i]); //F_i
	}
	/*�� ��������� ��������*/
	for (int j{ 1 }; j < n + 1; j++)
	{
		u[0][j] = -1.3 * t[j] + sin(0.6 * t[j]); //phi_j
		u[n][j] = exp(1.3 * t[j]) - 1.2 * sin(-1.1 * t[j]) + 1.3; //psi_j
	}
	//���������� ������� �� ���������� u(xi,-1) �� "�����������" ����.
	for (int i{ 1 }; i < n; i++) {
		u_virtual[i] = u[i][0] - k * u_t[i];
	}
	/*�� �������-����������� �����������*/
	for (int j{}; j < n; j++) {
		for (int i{ 1 }; i < n; i++)
		{
			if ((j - 1) == -1) {
				u[i][j + 1] = u[i + 1][j] + u[i - 1][j] - u_virtual[i];
			}
			else {
				u[i][j + 1] = u[i + 1][j] + u[i - 1][j] - u[i][j - 1];
			}
		}
	}

	//����� �������.
	printTable(x, t, u_virtual, u);

	//������������ ���������� ������������ ������.
	delete[] x;
	delete[] t;
	delete[] u_virtual;
	delete[] u_t;
	for (int i{}; i < n + 1; i++)
		delete[] u[i];
	delete[] u;
}