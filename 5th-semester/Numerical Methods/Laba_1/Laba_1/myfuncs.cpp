#include <iostream>
#include <string>
#include <iomanip>

#include "myfuncs.h"

/*������� ��������� ������������� ����������������� �����*/
//������� ��� �������� �������� ������������� ������ �� ����������� �������������� � �����.
bool checkStrIsNumeric(std::string const& userStr)
{
	bool negative_number{ false }, separator{ false };
	for (int i{}; i < userStr.length(); i++)
	{
		if ((i == 0) && (userStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		if ((userStr[i] == '.' || userStr[i] == ',' || userStr[i] == '/') && !separator && i != 0 && i != userStr.length() - 1)
		{
			separator = true;
			continue;
		}
		if ((userStr[i] < '0') || (userStr[i] > '9'))
			return false;
	}
	return !userStr.empty();
}
//������� ��� �������������� �������� ������������� ������ � �����.
double convertStrToNumber(std::string const& convertStr)
{
	double number{};
	bool negative_number{ false };
	int separator_index{ -1 };
	bool fraction{ false };
	double number_2{};
	int k{};

	for (int i{}; i < convertStr.length(); i++)
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
		{
			if (convertStr[i] == '/') fraction = true;
			separator_index = i;
			break;
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
			number += static_cast<double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_2 += static_cast<double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<double>(-number) : static_cast<double>(number);
	else
		return negative_number ? static_cast<double>(-number/number_2) : static_cast<double>(number/number_2);
}

/*������� ������ ���������� �� �������*/
//����� �������������� ����������.
void prePrint()
{
	//�������.
	std::cout << std::setw(210) << "������� ������ ��������," << std::setw(210) << "������ 4312" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 3." << std::endl;
	//����������� ����.
	std::cout << "C������ �������� �������������� ��������� (����):\n";
	std::cout << " _\n|  5x - y - z = 3;\n|\n<  6x - 8y + z = -1;\n|\n|_ 2x - 3y + 10z = 9." << std::endl << std::endl;

	//����������� ����.
	std::cout << "���������� ����:\n";
	std::cout << " _\n|  x = 0.6 + 0.2y + 0.2z;\n|\n<  y = 0.125 + 0.75x + 0.125z;\n|\n|_ z = 0.9 - 0.2x + 0.3y" << std::endl;
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
	std::cout << "1. ��������� ��������� �� ��������� (�������� ����������).\n"
		<< "2. ������ � ��������� ��� �������� �������� �������, � ����� ��������� ���, �� � �� ��� ��������� ����.\n"
		<< "3. ����� �� ���������." << std::endl;
}

/*��������������� �������*/
//������� ���������� ������������� ����� �� ���.
double getMaxOfThreeNumbers(const double& number_1, const double& number_2, const double& number_3)
{
	double max{ number_1 };
	if (number_2 > max) max = number_2;
	if (number_3 > max) max = number_3;
	return max;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3")
		{
			printDash();
			return choice[0];
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 3. ��������� ����. " << std::endl;
	}
}

/*������� ����� �������� ������ ���������*/
//������� ��������� �������� ������������� ����������� �������.
double getEpsilon()
{
	std::cout << "������� �������� �������: ";
	std::string user_epsilon{};
	while (true)
	{
		std::getline(std::cin, user_epsilon);
		if (checkStrIsNumeric(user_epsilon))
		{
			double numeric_user_epsilon{ convertStrToNumber(user_epsilon) };
			if (numeric_user_epsilon > 0)
				return numeric_user_epsilon;
			else
				std::cout << "������ �����. �������� ������� ������ ���� ������ ���� �� �������! ��������� ����: ";
		}
		else
			std::cout << "������ �����. �� ����� �� �����! ��������� ����: ";
	}
}
//������� ��� ��������� �������� ����� ���������� ���������� �����������, ��������� �������������.
double getValueOfApproxCoordinate()
{
	while (true)
	{
		std::string approx_coordinate{};
		std::getline(std::cin, approx_coordinate);
		if (checkStrIsNumeric(approx_coordinate))
			return convertStrToNumber(approx_coordinate);
		else
			std::cout << "������ �����. �� ����� �� �����! ��������� ����: ";
	}
}
//������� ��� ������� ���������� �����������.
void getInitOfApproximation(double approximate_mass[])
{
	std::cout << "������� ��������� �����������:" << std::endl;
	std::cout << "x_(0) = ";
	approximate_mass[0] = getValueOfApproxCoordinate();
	std::cout << "y_(0) = ";
	approximate_mass[1] = getValueOfApproxCoordinate();
	std::cout << "z_(0) = ";
	approximate_mass[2] = getValueOfApproxCoordinate();
}

//����� ����� ������� ��� ������ ������� �������� (���) � ������ ������� (��).
void printSIMandSMTable()
{
	std::cout << std::string(167, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(12) << "y_k"
		"|" << std::setw(12) << "z_k"
		"|" << std::setw(15) << "x_(k+1)"
		"|" << std::setw(15) << "y_(k+1)"
		"|" << std::setw(15) << "z_(k+1)"
		"|" << std::setw(20) << "   |x_(k+1) - x_k|   "
		"|" << std::setw(20) << "   |y_(k+1) - y_k|   "
		"|" << std::setw(20) << "   |z_(k+1) - z_k|   "
		"|" << std::setw(13) << "�����|" << std::endl;
	std::cout << std::string(167, '_') << std::endl;
}
//���.
void simpleIterationMethod(const double& user_epsilon, const double user_approximate_mass[])
{
	printDash();
	//����� ���������� ��� ���.
	std::cout << "����� ������� �������� (���) ��� �������� ����." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "��������� �����������:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ", " << user_approximate_mass[2] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, z_k{ user_approximate_mass[2] }, x_k_plus_1{}, y_k_plus_1{}, z_k_plus_1{};
	unsigned int k{ 1 };
	//����� ������� ���.
	printSIMandSMTable();
	//������������ ������� ���.
	while (true)
	{
		//���������� ����������� ���������� ((k+1)-���) ���� ��������.
		x_k_plus_1 = 0.6f + 0.2f * y_k + 0.2f * z_k;
		y_k_plus_1 = 0.125f + 0.75f * x_k + 0.125f * z_k;
		z_k_plus_1 = 0.9f - 0.2f * x_k + 0.3f * y_k;
		//���������� �������.
		std::cout << "|" << std::setw(5) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(11) << y_k <<
			"|" << std::setw(11) << z_k <<
			"|" << std::setw(14) << x_k_plus_1 <<
			"|" << std::setw(14) << y_k_plus_1 <<
			"|" << std::setw(14) << z_k_plus_1 <<
			"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
			"|" << std::setw(21) << abs(z_k_plus_1 - z_k) <<
			"|" << std::setw(12) << abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <<
			"|" << std::endl;
		std::cout << std::string(167, '_') << std::endl;
		//������� ��������� ������������� �������� ���.
		if (abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <= user_epsilon)
			break;
		//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
		k += 1;
		x_k = x_k_plus_1;
		y_k = y_k_plus_1;
		z_k = z_k_plus_1;
	}
	std::cout << std::endl << "����� �������, ������� ���� �� ��� � ��������� ��������� � ��������� ������������: (x, y, z) = " << "(" << x_k_plus_1 << ", " << y_k_plus_1 << ", " << z_k_plus_1 << ")." << std::endl;
}
//��.
void seidelMethod(const double& user_epsilon, const double user_approximate_mass[])
{
	printDash();
	//����� ���������� ��� ��.
	std::cout << "����� ������� (��) ��� �������� ����." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "��������� �����������:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ", " << user_approximate_mass[2] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, z_k{ user_approximate_mass[2] }, x_k_plus_1{}, y_k_plus_1{}, z_k_plus_1{};
	unsigned int k{ 1 };
	//����� ������� ��.
	printSIMandSMTable();
	//������������ ������� ��.
	while (true)
	{
		//���������� ����������� ���������� ((k+1)-���) ���� ��������.
		x_k_plus_1 = 0.6f + 0.2f * y_k + 0.2f * z_k;
		y_k_plus_1 = 0.125f + 0.75f * x_k_plus_1 + 0.125f * z_k;
		z_k_plus_1 = 0.9f - 0.2f * x_k_plus_1 + 0.3f * y_k_plus_1;
		//���������� �������.
		std::cout << "|" << std::setw(5) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(11) << y_k <<
			"|" << std::setw(11) << z_k <<
			"|" << std::setw(14) << x_k_plus_1 <<
			"|" << std::setw(14) << y_k_plus_1 <<
			"|" << std::setw(14) << z_k_plus_1 <<
			"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
			"|" << std::setw(21) << abs(z_k_plus_1 - z_k) <<
			"|" << std::setw(12) << abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <<
			"|" << std::endl;
		std::cout << std::string(167, '_') << std::endl;
		//������� ��������� ������������� �������� ��.
		if (abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <= user_epsilon)
			break;
		//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
		k += 1;
		x_k = x_k_plus_1;
		y_k = y_k_plus_1;
		z_k = z_k_plus_1;
	}
	std::cout << std::endl << "����� �������, ������� ���� �� �� � ��������� ��������� � ��������� ������������: (x, y, z) = " << "(" << x_k_plus_1 << ", " << y_k_plus_1 << ", " << z_k_plus_1 << ")." << std::endl;
}
//����� ����� ������� ��� ������ ���������� (����������) (��).
void printRMTable()
{
	std::cout << std::string(108, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(12) << "y_k"
		"|" << std::setw(12) << "z_k"
		"|" << std::setw(15) << "Rx_(k)"
		"|" << std::setw(15) << "Ry_(k)"
		"|" << std::setw(15) << "Rz_(k)"
		"|" << std::setw(20) << "   max|R_(k)|   |" << std::endl;
	std::cout << std::string(108, '_') << std::endl;
}
//��.
void relaxationMethod(const double& user_epsilon, const double user_approximate_mass[])
{
	printDash();
	//����� ���������� ��� ��.
	std::cout << "����� ���������� (����������) (��) ��� �������� ����." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "��������� �����������:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ", " << user_approximate_mass[2] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, z_k{ user_approximate_mass[2] }, Rx_k{}, Ry_k{}, Rz_k{};
	unsigned int k{};
	//����� ������� ��.
	printRMTable();
	//������������ ������� ��.
	while (true)
	{
		//���������� ������� �� k-�� ���� ��������.
		Rx_k = 0.6f - x_k + 0.2f * y_k + 0.2f * z_k;
		Ry_k = 0.125f + 0.75f * x_k - y_k + 0.125f * z_k;
		Rz_k = 0.9f - 0.2f * x_k + 0.3f * y_k - z_k;
		//������� ��������� ������������� �������� ��.
		if (abs(Rx_k) <= user_epsilon && abs(Ry_k) <= user_epsilon && abs(Rz_k) <= user_epsilon)
			break;
		double max{ getMaxOfThreeNumbers(abs(Rx_k), abs(Ry_k), abs(Rz_k)) };
		//���������� �������.
		std::cout << "|" << std::setw(5) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(11) << y_k <<
			"|" << std::setw(11) << z_k <<
			"|" << std::setw(14) << Rx_k <<
			"|" << std::setw(14) << Ry_k <<
			"|" << std::setw(14) << Rz_k <<
			"|" << std::setw(19) << max <<
			"|" << std::endl;
		std::cout << std::string(108, '_') << std::endl;
		//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
		k += 1;
		if (max == abs(Rx_k))
			x_k += Rx_k;
		else if (max == abs(Ry_k))
			y_k += Ry_k;
		else
			z_k += Rz_k;
	}
	std::cout << std::endl << "����� �������, ������� ���� �� �� � ��������� ��������� � ��������� ������������: (x, y, z) = " << "(" << x_k << ", " << y_k << ", " << z_k << ")." << std::endl;
}