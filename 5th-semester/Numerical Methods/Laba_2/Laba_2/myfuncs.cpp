#include <iostream>
#include <string>
#include <iomanip>

#include "constants.h"
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
		return negative_number ? static_cast<double>(-number / number_2) : static_cast<double>(number / number_2);
}

/*������� ������ ���������� �� �������*/
//����� �������������� ����������.
void prePrint()
{
	//�������.
	std::cout << std::setw(210) << "������� ������ ��������," << std::setw(210) << "������ 4312" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 3." << std::endl << std::endl;
	//�������� ���������� ���������.
	std::cout << "���������� ���������:\n";
	std::cout << "exp(2x) + 4x = 0" << std::endl << std::endl;

	std::cout << "� ���������� �������� ������ � ����������� �������� ��� ���������� ����������� ��������� � ������������� ������� �� ������� [a;b] ��� ������ ������� [" << a << ";" << b << "]." << std::endl;
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
		<< "2. ������ � ��������� ��� �������� �������� ������� � ������, � ����� ��������� ���, �� � ��� ��� ��������� ����������� ���������.\n"
		<< "3. ����� �� ���������." << std::endl;
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
//������� ��������� �������� ������������� ����������� ������.
double getDeltha()
{
	std::cout << "������� �������� ������: ";
	std::string user_deltha{};
	while (true)
	{
		std::getline(std::cin, user_deltha);
		if (checkStrIsNumeric(user_deltha))
		{
			double numeric_user_deltha{ convertStrToNumber(user_deltha) };
			if (numeric_user_deltha > 0)
				return numeric_user_deltha;
			else
				std::cout << "������ �����. �������� ������ ������ ���� ������ ���� �� �������! ��������� ����: ";
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
			if (convertStrToNumber(approx_coordinate) >= a && convertStrToNumber(approx_coordinate) <= b)
				return convertStrToNumber(approx_coordinate);
			else
			{
				std::cout << "������ �����. ��������� ����������� ������ ������������ ������� [" << a << ";" << b << "]. ��������� ����:" << std::endl;
				std::cout << "x_0 = ";
			}
		else
			std::cout << "������ �����. �� ����� �� �����! ��������� ����: ";
	}
}
//������� ��� ������� ���������� �����������.
void getInitOfApproximation(double& approximate_x0)
{
	std::cout << "������� ��������� �����������:" << std::endl;
	std::cout << "x_0 = ";
	approximate_x0 = getValueOfApproxCoordinate();
}

//����� ����� ������� ��� ������ ������� �������� (���), ������ ������� (��), ����������������� ������ ������� (���).
void printSIM_NM_MNM_table()
{
	std::cout << std::string(71, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(15) << "x_(k+1)"
		"|" << std::setw(20) << "   |x_(k+1) - x_k|   "
		"|" << std::setw(13) << "   |f(x_(k+1))|" << std::endl;
	std::cout << std::string(71, '_') << std::endl;
}
//���.
void simpleIterationMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_x0)
{
	printDash();
	//����� ���������� ��� ���.
	std::cout << "����� ������� �������� (���) ��� ��������� ����������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\t x_0 = " << user_approximate_x0 << "." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t " << user_deltha << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_k{ user_approximate_x0 }, x_k_plus_1{};
	unsigned int k{ 1 };
	//����� ������� ���.
	printSIM_NM_MNM_table();
	//������������ ������� ���.
	while (true)
	{
		//���������� ����������� ���������� ((k+1)-���) ���� ��������.
		x_k_plus_1 = x_k + C * (exp(2 * x_k) + 4 * x_k);
		//���������� �������.
		std::cout << "|" << std::setw(5) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(14) << x_k_plus_1 <<
			"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(14) << abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) << 
			"|" << std::endl;
		std::cout << std::string(71, '_') << std::endl;
		//������� ��������� ������������� �������� ���.
		if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <= user_deltha)
			break;
		//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
		k += 1;
		x_k = x_k_plus_1;
	}
	std::cout << std::endl << "����� �������, ������� ����������� ��������� �� ��� � ��������� ��������� � ��������� ������������: x = " << x_k_plus_1 << "." << std::endl;
}
//��.
void NewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_x0)
{
	printDash();
	//����� ���������� ��� ��.
	std::cout << "����� ������� (��) ��� ��������� ����������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\t x_0 = " << user_approximate_x0 << "." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t " << user_deltha << "." << std::endl;
	if ((exp(2 * user_approximate_x0) + 4 * user_approximate_x0) * 4 * exp(2 * user_approximate_x0) > 0)
	{
		//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
		double x_k{ user_approximate_x0 }, x_k_plus_1{};
		unsigned int k{ 1 };
		//����� ������� ��.
		printSIM_NM_MNM_table();
		//������������ ������� ��.
		while (true)
		{
			//���������� ����������� ���������� ((k+1)-���) ���� ��������.
			x_k_plus_1 = x_k - ((exp(2 * x_k) + 4 * x_k) / (2 * exp(2 * x_k) + 4));
			//���������� �������.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(14) << abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(71, '_') << std::endl;
			//������� ��������� ������������� �������� ��.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <= user_deltha)
				break;
			//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "����� �������, ������� ����������� ��������� �� �� � ��������� ��������� � ��������� ������������: x = " << x_k_plus_1 << "." << std::endl;
	}
	else
	{
		std::cout << "�� ����������� ����������� ������� ���������� ��." << std::endl << std::endl;
		std::cout << "�������� ���������� ����������� x_0 ������ ���� ������� �� ������� [a;b] = [" << a << "; " << b << "] ���, ����� " << "����������� ��������� �������: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, �.�. (exp(2x_0) + 4x_0)*(4exp(2x_0)) > 0." << std::endl;
		std::cout << "� ������ ������ �������� ��������� �����: " << std::endl << (exp(2 * user_approximate_x0) + 4 * user_approximate_x0) * 4 * exp(2 * user_approximate_x0) << " < 0." << std::endl;
	}
}
//���.
void modifiedNewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_x0)
{
	printDash();
	//����� ���������� ��� ���.
	std::cout << "���������������� ����� ������� (���) ��� ��������� ����������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\t x_0 = " << user_approximate_x0 << "." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t " << user_deltha << "." << std::endl;
	if (exp(2 * user_approximate_x0) + 4 * user_approximate_x0 > 0)
	{
		//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
		double x_k{ user_approximate_x0 }, x_k_plus_1{};
		double darivative_x0{ 2 * exp(2 * user_approximate_x0) + 4 };
		unsigned int k{ 1 };
		//����� ������� ���.
		printSIM_NM_MNM_table();
		//������������ ������� ���.
		while (true)
		{
			//���������� ����������� ���������� ((k+1)-���) ���� ��������.
			x_k_plus_1 = x_k - ((exp(2 * x_k) + 4 * x_k) / darivative_x0);
			//���������� �������.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(14) << abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(71, '_') << std::endl;
			//������� ��������� ������������� �������� ���.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <= user_deltha)
				break;
			//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "����� �������, ������� ����������� ��������� �� ��� � ��������� ��������� � ��������� ������������: x = " << x_k_plus_1 << "." << std::endl;
	}
	else
	{
		std::cout << "�� ����������� ����������� ������� ���������� ���." << std::endl << std::endl;
		std::cout << "�������� ���������� ����������� x_0 ������ ���� ������� �� ������� [a;b] = [" << a << "; " << b << "] ���, ����� " << "����������� ��������� �������: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, �.�. (exp(2x_0) + 4x_0)*(4exp(2x_0)) > 0." << std::endl;
		std::cout << "� ������ ������ �������� ��������� �����: " << std::endl << (exp(2 * user_approximate_x0) + 4 * user_approximate_x0) * 4 * exp(2 * user_approximate_x0) << " < 0." << std::endl;
	}
}