#include <iostream>
#include <string>
#include <iomanip>

#include "Constants.h";
#include "myfuncs.h"

/*ФУНКЦИИ ОБРАБОТКИ НЕКОРРЕКТНОГО ПОЛЬЗОВАТЕЛЬСКОГО ВВОДА*/
//Функции для проверки введённой пользователем строки на возможность преобразования в число.
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
//Функция для преобразования введённой пользователем строки в число.
long double convertStrToNumber(std::string const& convertStr)
{
	long double number{};
	bool negative_number{ false };
	int separator_index{ -1 };
	bool fraction{ false };
	long double number_2{};
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
			number += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<long double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<long double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_2 += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<long double>(-number) : static_cast<long double>(number);
	else
		return negative_number ? static_cast<long double>(-number / number_2) : static_cast<long double>(number / number_2);
}

/*ФУНКЦИИ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод первоначальной информации.
void prePrint()
{
	std::cout << std::setw(210) << "Горшков Андрей Олегович," << std::setw(210) << "группа 4312" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 3." << std::endl << std::endl;
	std::cout << "Заданная функция:\n";
	std::cout << "f(x) = (x + 1) * sin(x)" << std::endl << std::endl;

	std::cout << "Выбранный отрезок, где функция имеет наиболее пологий вид: [" << a << ";" << b << "]." << std::endl;
}
//Разделительная черта.
void printDash()
{
	std::cout << std::string(210, '-') << std::endl;
}
//Вывод меню на консоль.
void printMenu()
{
	std::cout << "Что вы хотите сделать в программе?" << std::endl;
	std::cout << "1. Запустить программу.\n"
		<< "2. Выйти из программы." << std::endl;
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Функция выбора действия в меню.
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
		{
			printDash();
			return choice[0];
		}
		else
			std::cout << "Вы должны ввести целое число от 1 до 2. Повторите ввод. " << std::endl;
	}
}
//Получение значения текущего X от пользователя.
long double getX()
{
	while (true)
	{
		std::string user_value{};
		std::getline(std::cin, user_value);
		if (checkStrIsNumeric(user_value))
			if (convertStrToNumber(user_value) >= a && convertStrToNumber(user_value) <= b)
				return convertStrToNumber(user_value);
			else
				std::cout << "Введенное Вами число вышло за диапазон допустимых значений. Повторите ввод: ";
		else
			std::cout << "Ошибка ввода. Вы ввели не число! Повторите ввод: ";
	}
}
void getValuesXFromUser(long double user_values_of_X[])
{
	std::cout << "Введите 3 значения X из отрезка [" << a << ";" << b << "]:" << std::endl;
	std::cout << "Первое значение X: ";
	user_values_of_X[0] = getX();
	std::cout << "Второе значение X: ";
	user_values_of_X[1] = getX();
	std::cout << "Третье значение X: ";
	user_values_of_X[2] = getX();
}

/*ФУНКЦИИ ВЫВОДА ОСНОВНЫХ ДАННЫХ ПРОГРАММЫ*/
//Вывод шапки исходной таблицы для интерполирования.
void printTableInterpolation()
{
	std::cout << std::string(208, '_') << std::endl;
	std::cout << "|" << std::setw(13) << "x" <<
		"|" << std::setw(13) << "y(x)" <<
		"|" << std::setw(20) << "PI(x)" <<
		"|" << std::setw(27) << "|y(x) - PI(x)|     " <<
		"|" << std::setw(15) << "q" <<
		"|" << std::setw(20) << "PII(x)" <<
		"|" << std::setw(27) << "|y(x) - PII(x)|    " <<
		"|" << std::setw(15) << "t" <<
		"|" << std::setw(20) << "L(x)" <<
		"|" << std::setw(27) << "|y(x) - L(x)|      " <<
		"|" << std::endl;
	std::cout << std::string(208, '_') << std::endl;
}
//Вывод шапки исходной таблицы для численного дифференцирования.
void printTableNumericalDefferentiation()
{
	std::cout << std::string(202, '_') << std::endl;
	std::cout << "|" << std::setw(13) << "x" <<
		"|" << std::setw(16) << "y'(x)" <<
		"|" << std::setw(13) << "~x_0" <<
		"|" << std::setw(20) << "(PI(x))'" <<
		"|" << std::setw(30) << "|y'(x) - PI(x))'|    " <<
		"|" << std::setw(18) << "q" <<
		"|" << std::setw(13) << "~x_n" <<
		"|" << std::setw(20) << "(PII(x))'" <<
		"|" << std::setw(30) << "|y'(x) - PII(x))'|      " <<
		"|" << std::setw(18) << "t" <<
		"|" << std::endl;
	std::cout << std::string(202, '_') << std::endl;
}

/*ОСНОВНЫЕ ФУНКЦИИ ПРОГРАММЫ*/
void  interpolation_formulas(long double user_values_of_X[])
{
	for (int i{};i < 3;i++)
	{
		//Вычисление y(x).
		long double y_x{ (user_values_of_X[i] + 1) * sin(user_values_of_X[i]) };

		//Вычисление q.
		long double q{ (user_values_of_X[i] - a) / h };
		//Вычисление PI(x).
		long double PI_x{ -0.238165 + q * (-0.001874) + (q * (q - 1) * 0.002457) / 2 + (q * (q - 1) * (q - 2) * 0.000038) / 6 + (q * (q - 1) * (q - 2) * (q - 3) * (-0.000006)) / 24 + (q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * 0) / 120 };

		//Вычисление t.
		long double t{ (user_values_of_X[i] - b) / h };
		//Вычисление PII(x).
		long double PII_x{ -0.222615 + t * 0.008158 + (t * (t + 1)) / 2 * 0.002553 + (t * (t + 1) * (t + 2)) / 6 * 0.000026 + (t * (t + 1) * (t + 2) * (t + 3)) / 24 * (-0.000006) + (t * (t + 1) * (t + 2) * (t + 3) * (t + 4) * 0) / 120 };

		//Вычисление L(x).
		long double L_x{ 37788.22316 * (user_values_of_X[i] + 0.489) * (user_values_of_X[i] + 0.454) * (user_values_of_X[i] + 0.419) * (user_values_of_X[i] + 0.384) * (user_values_of_X[i] + 0.349) +
						(-190427.79794) * (user_values_of_X[i] + 0.524) * (user_values_of_X[i] + 0.454) * (user_values_of_X[i] + 0.419) * (user_values_of_X[i] + 0.384) * (user_values_of_X[i] + 0.349) +
						379930.58448 * (user_values_of_X[i] + 0.524) * (user_values_of_X[i] + 0.489) * (user_values_of_X[i] + 0.419) * (user_values_of_X[i] + 0.384) * (user_values_of_X[i] + 0.349) +
						(-375046.90506) * (user_values_of_X[i] + 0.524) * (user_values_of_X[i] + 0.489) * (user_values_of_X[i] + 0.454) * (user_values_of_X[i] + 0.384) * (user_values_of_X[i] + 0.349) +
						183076.89256 * (user_values_of_X[i] + 0.524) * (user_values_of_X[i] + 0.489) * (user_values_of_X[i] + 0.454) * (user_values_of_X[i] + 0.419) * (user_values_of_X[i] + 0.349) +
						(-35320,9972) * (user_values_of_X[i] + 0.524) * (user_values_of_X[i] + 0.489) * (user_values_of_X[i] + 0.454) * (user_values_of_X[i] + 0.419) * (user_values_of_X[i] + 0.384) };
		//Заполнение таблицы.
		std::cout << "|" << std::setw(13) << std::setprecision(13) << user_values_of_X[i] <<
			"|" << std::setw(13) << std::setprecision(10) << y_x <<
			"|" << std::setw(20) << std::setprecision(10) << PI_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(y_x - PI_x) <<
			"|" << std::setw(15) << std::setprecision(10) << q <<
			"|" << std::setw(20) << std::setprecision(10) << PII_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(y_x - PII_x) <<
			"|" << std::setw(15) << std::setprecision(10) << t <<
			"|" << std::setw(20) << std::setprecision(10) << L_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(y_x - L_x) <<
			"|" << std::endl;
		std::cout << std::string(208, '_') << std::endl;
	}
}
long double getClosestToX(const long double& cur_x_value, const int& method)
{
	long double x0{ -0.524 }, x1{ -0.489 }, x2{ -0.454 }, x3{ -0.419 }, x4{ -0.384 }, x5{ -0.349 };
	if (cur_x_value != x0 && cur_x_value != x1 && cur_x_value != x2 && cur_x_value != x3 && cur_x_value != x4 && cur_x_value != x5)
	{
		if (cur_x_value > x0 && cur_x_value < x1)
		{
			if (method == 1)
			{
				if (abs(abs(cur_x_value - x0) - abs(cur_x_value - x1)) < 0.00000000001)
					return x0;
				else if (abs(cur_x_value - x0) < abs(cur_x_value - x1))
					return x0;
				else
					return x1;
			}
			else
			{
				if (abs(abs(cur_x_value - x0) - abs(cur_x_value - x1)) < 0.00000000001)
					return x1;
				else if (abs(cur_x_value - x0) < abs(cur_x_value - x1))
					return x0;
				else
					return x1;
			}
		}
		else if (cur_x_value > x1 && cur_x_value < x2)
		{
			if (method == 1)
			{
				if (abs(abs(cur_x_value - x1) - abs(cur_x_value - x2)) < 0.00000000001)
					return x1;
				else if (abs(cur_x_value - x1) <= abs(cur_x_value - x2))
					return x1;
				else
					return x2;
			}
			else
			{
				if (abs(abs(cur_x_value - x1) - abs(cur_x_value - x2)) < 0.00000000001)
					return x2;
				if (abs(cur_x_value - x1) < abs(cur_x_value - x2))
					return x1;
				else
					return x2;
			}
		}
		else if (cur_x_value > x2 && cur_x_value < x3)
		{
			if (method == 1)
			{
				if (abs(abs(cur_x_value - x2) - abs(cur_x_value - x3)) < 0.00000000001)
					return x2;
				else if (abs(cur_x_value - x2) <= abs(cur_x_value - x3))
					return x2;
				else
					return x3;
			}
			else
			{
				if (abs(abs(cur_x_value - x2) - abs(cur_x_value - x3)) < 0.00000000001)
					return x3;
				else if (abs(cur_x_value - x2) < abs(cur_x_value - x3))
					return x2;
				else
					return x3;
			}
		}
		else if (cur_x_value > x3 && cur_x_value < x4)
		{
			if (method == 1)
			{
				if (abs(abs(cur_x_value - x3) - abs(cur_x_value - x4)) < 0.00000000001)
					return x3;
				else if (abs(cur_x_value - x3) <= abs(cur_x_value - x4))
					return x3;
				else
					return x4;
			}
			else
			{
				if (abs(abs(cur_x_value - x3) - abs(cur_x_value - x4)) < 0.00000000001)
					return x4;
				else if (abs(cur_x_value - x3) < abs(cur_x_value - x4))
					return x3;
				else
					return x4;
			}
		}
		else if (cur_x_value > x4 && cur_x_value < x5)
		{
			if (method == 1)
			{
				if (abs(abs(cur_x_value - x4) - abs(cur_x_value - x5)) < 0.00000000001)
					return x4;
				else if (abs(cur_x_value - x4) <= abs(cur_x_value - x5))
					return x4;
				else
					return x5;
			}
			else
			{
				if (abs(abs(cur_x_value - x4) - abs(cur_x_value - x5)) < 0.00000000001)
					return x5;
				else if (abs(cur_x_value - x4) < abs(cur_x_value - x5))
					return x4;
				else
					return x5;
			}
		}
	}
	else
	{
		if (cur_x_value == x0)
			return x0;
		else if (cur_x_value == x1)
			return x1;
		else if (cur_x_value == x2)
			return x2;
		else if (cur_x_value == x3)
			return x3;
		else if (cur_x_value == x4)
			return x4;
		else if (cur_x_value == x5)
			return x5;

	}
}
void numerical_differentation_formulas(long double user_values_of_X[])
{
	for (int i{}; i < 3; i++)
	{
		//Вычисление y'(x).
		long double dy{ sin(user_values_of_X[i] + (user_values_of_X[i] + 1) * cos(user_values_of_X[i]))};
		//Вычисление ~x_0.
		long double tilde_x_0{ getClosestToX(user_values_of_X[i], 1) };
		//Вычисление q.
		long double q{ (user_values_of_X[i] - tilde_x_0) / h };
		//Вычисление (PI(x))'.
		long double dPI_x{ 1 / h * ((-0.001874) + ((2 * q - 1) * 0.002457) / 2 + ((3 * pow(q,2) - 6 * q + 2) * 0.000038) / 6 + ((4 * pow(q,3) - 18 * pow(q,2) + 22 * q - 6) * (-0.000006)) / 24 + ((5 * pow(q,4) - 40 * pow(q,3) + 105 * pow(q,2) - 100 * q + 24) * 0) / 120) };
		//Вычисление ~x_n
		long double tilde_x_n{ getClosestToX(user_values_of_X[i], 2) };
		//Вычисление t.
		long double t{ (user_values_of_X[i] - tilde_x_n) / h };
		//Вычисление (PII(x))'.
		long double dPII_x{ 1 / h * (0.008158 + (2 * t + 1) / 2 * 0.002553 + (3 * pow(t,2) + 6 * t + 2) / 6 * 0.000026 + (4 * pow(t,3) + 18 * pow(t,2) + 22 * t + 6) / 24 * (-0.000006) + (5 * pow(t,4) + 40 * pow(t,3) + 105 * pow(t,2) + 100 * q + 24) / 120 * 0) };
		//Заполнение таблицы.
		std::cout << "|" << std::setw(13) << std::setprecision(13) << user_values_of_X[i] <<
			"|" << std::setw(16) << std::setprecision(10) << dy <<
			"|" << std::setw(13) << std::setprecision(10) << tilde_x_0 <<
			"|" << std::setw(20) << std::setprecision(10) << dPI_x <<
			"|" << std::setw(30) << std::setprecision(10) << abs(dy - dPI_x) <<
			"|" << std::setw(18) << std::setprecision(10) << q <<
			"|" << std::setw(13) << std::setprecision(10) << tilde_x_n <<
			"|" << std::setw(20) << std::setprecision(10) << dPII_x <<
			"|" << std::setw(30) << std::setprecision(10) << abs(dy - dPII_x) <<
			"|" << std::setw(18) << std::setprecision(10) << t <<
			"|" << std::endl;
		std::cout << std::string(202, '_') << std::endl;
	}
}