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
	std::cout << "������� ���������� ��������� (���):\n";
	std::cout << " _\n| x^2 - y^2 - 5 = 0;" << std::endl;
	std::cout << "<" << std::endl;
	std::cout << "|_x - y - 1 = 0." << std::endl << std::endl;

	std::cout << "��������� ����������� (1,0)." << std::endl;
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
			return convertStrToNumber(approx_coordinate);
		else
			std::cout << "������ �����. �� ����� �� �����! ��������� ����: ";
	}
}
//������� ��� ������� ���������� �����������.
void getInitOfApproximation_v2(double approximate_mass[])
{
	std::cout << "�� ������ ������ ����������� ��������� ����������� ��� �������� �������� (1, 0) (\"�����\"/\"enter\")? ";
	std::string new_or_default_initial_approx{};
	while (true)
	{
		std::getline(std::cin, new_or_default_initial_approx);
		if (new_or_default_initial_approx.empty())
		{
			approximate_mass[0] = 1;
			approximate_mass[1] = 0;
			break;
		}
		else if (new_or_default_initial_approx == "�����")
		{
			std::cout << "������� ��������� �����������:" << std::endl;
			std::cout << "x_0 = ";
			approximate_mass[0] = getValueOfApproxCoordinate();
			std::cout << "y_0 = ";
			approximate_mass[1] = getValueOfApproxCoordinate();
			break;
		}
		else
			std::cout << "������ �����. ������� ���� �������� ����� \"�����\", ���� ������� \"enter\": ";
	}
}
void getInitOfApproximation(double approximate_mass[])
{
	std::cout << "������� ��������� �����������:" << std::endl;
	std::cout << "���������� x^(0) = ";
	approximate_mass[0] = getValueOfApproxCoordinate();
	std::cout << "���������� y^(0) = ";
	approximate_mass[1] = getValueOfApproxCoordinate();
}

//����� ����� ������� ��� ������ ������� �������� (���), ������ ������� (��), ����������������� ������ ������� (���).
void printSIM_NM_MNM_table()
{
	std::cout << std::string(159, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(12) << "x^(k)"
		"|" << std::setw(12) << "y^(k)"
		"|" << std::setw(15) << "x^(k+1)"
		"|" << std::setw(15) << "y^(k+1)"
		"|" << std::setw(20) << "  |x^(k+1) - x^(k)|  "
		"|" << std::setw(20) << "  |y^(k+1) - y^(k)|  "
		"|" << std::setw(13) << " |f_1(x^(k+1), y^(k+1))|  "
		"|" << std::setw(13) << " |f_2(x^(k+1), y^(k+1))|  " 
		"|" << std::endl;
	std::cout << std::string(159, '_') << std::endl;
}
//���.
void simpleIterationMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[])
{
	printDash();
	//����� ���������� ��� ���.
	std::cout << "����� ������� �������� (���) ��� �������� ���." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "��������� �����������:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t " << user_deltha << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
	unsigned int k{ 1 };
	bool solution{ true };
	//����� ������� ���.
	if (x_k != y_k)
		printSIM_NM_MNM_table();
	//������������ ������� ���.
	/*�������� ���������� ������������ ������� ���������� �� ���������, �.�.��� ������ ����������� ��� �������� ������������� �����, ����, �����, ������
	 *� ������������ ������� ������ ������� �������� (���).
	 *����� ����������� ����������� �� ������������� ������-���� ������������ � ������, ���� ��� ��������� �������� ������� �� 0 ��� �������� ��������� ������������.
	 */
	while (true)
	{
		//���������� ����������� ���������� ((k+1)-���) ���� ��������.
		x_k_plus_1 = x_k + 1 / (2 * (y_k - x_k)) * (pow(x_k, 2) - pow(y_k, 2) - 5) + y_k / (x_k - y_k) * (x_k - y_k - 1);
		y_k_plus_1 = y_k + 1 / (2 * (y_k - x_k)) * (pow(x_k, 2) - pow(y_k, 2) - 5) + x_k / (x_k - y_k) * (x_k - y_k - 1);
		if (x_k == y_k)
		{
			std::cout << std::endl << "������ ��������� ���������� �����������! ���������� ���������� ����������� x^(0) � y^(0) �� ������ ���� ����� ���� �����, �.�. x^(0) != y^(0). " <<
				"� ��������� ������ ���������� ������� �� 0 � ������������ ������� ������ ������� ��������(���)." << std::endl <<
				"� ������ ������ ���������� ���������� ����������� ����� ���� �����, �.�: " << user_approximate_mass[0] << " = " << user_approximate_mass[1] << std::endl;
			solution = false;
			break;
		}
		else
		{
			//���������� �������.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(11) << y_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(14) << y_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
				"|" << std::setw(26) << abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <<
				"|" << std::setw(26) << abs(x_k_plus_1 - y_k_plus_1 - 1) <<
				"|" << std::endl;
			std::cout << std::string(159, '_') << std::endl;
			//������� ��������� ������������� �������� ���.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(y_k_plus_1 - y_k) <= user_epsilon &&
				abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <= user_deltha && abs(x_k_plus_1 - y_k_plus_1 - 1) <= user_deltha)
				break;
			//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
	}
	if (solution)
		std::cout << std::endl << "����� �������, ������� ������� ���������� ��������� �� ��� � ��������� ��������� � ��������� ������������: (x, y) = (" << x_k_plus_1 << ", " << y_k_plus_1 << ")." << std::endl;
	else
		std::cout << std::endl << "������� ����������: ������� �� 0! ����� �� ����� ��������� ����������." << std::endl;
}
//��.
void NewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[])
{
	printDash();
	//����� ���������� ��� ��.
	std::cout << "����� ������� (��) ��� �������� ���." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "��������� �����������:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t " << user_deltha << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
	unsigned int k{ 1 };
	bool solution{ true };
	//����� ������� ��.
	if (2 * (y_k - x_k) != 0)
		printSIM_NM_MNM_table();
	//������������ ������� ��.
	/*�������� ������������� �������� ������� �����(������� ����� ������ ���� �������������) ��� �������� ��������� �����������,
	 *�.�. � ��������� ������ ����� ������� (��) ��������� ����� ����������.
	 */
	while (true)
	{
		//���������� ����������� ���������� ((k+1)-���) ���� ��������.
		x_k_plus_1 = x_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_k - y_k)) + (y_k * (x_k - y_k - 1) / (y_k - x_k)));
		y_k_plus_1 = y_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_k - y_k)) + (x_k * (x_k - y_k - 1) / (y_k - x_k)));
		if (2 * (y_k - x_k) != 0)
		{
			//���������� �������.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(11) << y_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(14) << y_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
				"|" << std::setw(26) << abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <<
				"|" << std::setw(26) << abs(x_k_plus_1 - y_k_plus_1 - 1) <<
				"|" << std::endl;
			std::cout << std::string(159, '_') << std::endl;
			//������� ��������� ������������� �������� ��.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(y_k_plus_1 - y_k) <= user_epsilon &&
				abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <= user_deltha && abs(x_k_plus_1 - y_k_plus_1 - 1) <= user_deltha)
				break;
			//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
		else
		{
			if (k == 1)
			{
				std::cout << std::endl << "������ ���������� �����������! ��� �������� ��������� ����������� �������� ������� ����� �� ����������, " << std::endl <<
					"������� ����� ������� (��) �� ����� ���� �����������. ������� �������������: " << std::endl;
				std::cout << "\t   | 2x^(0)\t-2y^(0)  |" << std::endl;
				std::cout << "  _" << std::endl;
				std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) + 2y^(0) = 2 * (" << user_approximate_mass[1] << " - " << user_approximate_mass[0] << ") = " <<
					"2 * ((" << user_approximate_mass[1] << ") - (" << user_approximate_mass[0] << ")) = 0." << std::endl;
				std::cout << "����� �������, ������� ����� �����������, �.�. �������� ������� ����� �� ����������." << std::endl;
			}
			else
			{
				std::cout << std::endl << "������ " << k + 1 << "-�� �����������! ��� �������� ����������� �������� ������� ����� �� ����������, " << std::endl <<
					"������� ����� ������� (��) �� ����� ���� �����������. ������� �������������: " << std::endl;
				std::cout << "\t   | 2x^(" << k + 1 << ")\t-2y^(" << k + 1 << ") | " << std::endl;
				std::cout << "  _" << std::endl;
				std::cout << "J(w^(" << k + 1 << ")) = |\t1\t-1\t| = -2x^(" << k + 1 << ") + 2y^(" << k + 1 << ") = 2 * (" << y_k << " - " << x_k << ") = " <<
					"2 * ((" << x_k << ") - (" << y_k << ")) = 0." << std::endl;
				std::cout << "����� �������, ������� ����� �����������, �.�. �������� ������� ����� �� ������ ���� �������� �� ����������." << std::endl;
			}
			solution = false;
			break;
		}
	}
	if (solution)
		std::cout << std::endl << "����� �������, ������� ������� ���������� ��������� �� ��� � ��������� ��������� � ��������� ������������: (x, y) = (" << x_k_plus_1 << ", " << y_k_plus_1 << ")." << std::endl;
	else
		std::cout << std::endl << "�� ����������� ������� ��� ���������� ��." << std::endl;
}
//���.
void modifiedNewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[])
{
	printDash();
	//����� ���������� ��� ���.
	std::cout << "���������������� ����� ������� (���) ��� �������� ���." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "��������� �����������:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ")." << std::endl;
	std::cout << "�������� �������� �������:\t " << user_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t " << user_deltha << "." << std::endl;
	//������������� ���������� ��� �������� k-��� � (k+1)-��� ����������� � ��������.
	double x_0{ user_approximate_mass[0] }, y_0{ user_approximate_mass[1] };
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
	unsigned int k{ 1 };
	bool solution{ true }, method_converges{ true };

	//����� ������� ���.
	if (2 * (y_0 - x_0) != 0)
		printSIM_NM_MNM_table();
	//������������ ������� ���.
	/* �������� ������������� �������� ������� �����(������� ����� ������ ���� �������������) ��� �������� ��������� �����������,
	 *�.�. � ��������� ������ ���������������� ����� ������� (���) ��������� ����� ����������.
	 */
	while (true)
	{
		//���������� ����������� ���������� ((k+1)-���) ���� ��������.
		x_k_plus_1 = x_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_0 - y_0)) + (y_0 * (x_k - y_k - 1) / (y_0 - x_0)));
		y_k_plus_1 = y_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_0 - y_0)) + (x_0 * (x_k - y_k - 1) / (y_0 - x_0)));
		if (2 * (y_0 - x_0) != 0)
		{
			//���������� �������.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(11) << y_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(14) << y_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
				"|" << std::setw(26) << abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <<
				"|" << std::setw(26) << abs(x_k_plus_1 - y_k_plus_1 - 1) <<
				"|" << std::endl;
			std::cout << std::string(159, '_') << std::endl;
			//������� ��������� ������������� �������� ���.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(y_k_plus_1 - y_k) <= user_epsilon &&
				abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <= user_deltha && abs(x_k_plus_1 - y_k_plus_1 - 1) <= user_deltha)
				break;
			//������� � ��������� ��������, ���� ������� ��������� ������������� �������� ��� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
			if (x_k == +INFINITY || y_k == +INFINITY || x_k == -INFINITY && y_k == -INFINITY)
			{
				method_converges = false;
				break;
			}
		}
		else
		{
			std::cout << std::endl << "������ ���������� �����������! ��� �������� ��������� ����������� �������� ������� ����� �� ����������, " << std::endl <<
				"������� ����� ������� (��) �� ����� ���� �����������. ������� �������������: " << std::endl;
			std::cout << "\t   | 2x^(0)\t-2y^(0)  |" << std::endl;
			std::cout << "  _" << std::endl;
			std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) + 2y^(0) = 2 * (" << user_approximate_mass[1] << " - " << user_approximate_mass[0] << ") = " <<
				"2 * ((" << user_approximate_mass[1] << ") - (" << user_approximate_mass[0] << ")) = 0." << std::endl;
			std::cout << "����� �������, ������� ����� �����������, �.�. �������� ������� ����� �� ����������." << std::endl;
			solution = false;
			break;
		}
	}
	if (solution && method_converges)
		std::cout << std::endl << "����� �������, ������� ������� ���������� ��������� �� ��� � ��������� ��������� � ��������� ������������: (x, y) = (" << x_k_plus_1 << ", " << y_k_plus_1 << ")." << std::endl;
	else
	{
		if (!solution)
			std::cout << std::endl << "�� ����������� ������� ��� ���������� ���." << std::endl;
		if (!method_converges)
			std::cout << std::endl << "���������������� ����� ������� ����������, �.�. �������� ������� ����� �� �������� ����������� � ���� ���������� " <<
			"� ������� (�����������), � ������� ���� �������." << std::endl;
	}
}