#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>

#include "constants.h"
#include "myfuncs.h"

/*ОБЩИЕ ФУНКЦИИ ВВОДА И ВЫВОДА*/
//Вывод разделительной черты.
void PrintDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод информации об авторе, варианте и задании.
void PrePrint()
{
	std::cout << std::setw(210) << "Горшков Андрей Олегович," << std::endl << std::setw(209) << "группа 4312" << std::endl;
	PrintDash();
	std::cout << "Вариант индивидуального задания: 10." << std::endl;
	std::cout << "Заданная задача Коши (обыкновенное дифференциальное уравнение и начальное условие):" << std::endl;
	std::cout << " _\n|\n| dy/dx = x^3*y\n<\n| y(-2) = 2\n|_\n" << std::endl;
	std::cout << "Заданный отрезок: [" << a << "; " << b << "]." << std::endl;
	std::cout << "Общее решение ДУ: y = Ce^(x^4/4), C принадлежит R." << std::endl;
	std::cout << "Частное решение ДУ (задача Коши): y = 2e^(x^4/4-4)." << std::endl;
}
//Пользовательское меню.
void PrintMenu()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1. Запустить программу." << std::endl <<
		"2. Выйти из программы." << std::endl;
}


/*ФУНКЦИИ ПРОВЕРКИ ПОЛЬЗОВАТЕЛЬСКОГО ВВОДА*/
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
//Получение значения точности.
double getEpsilon()
{
	std::cout << "Введите значение эпсилон: ";
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
				std::cout << "Ошибка ввода. Значение эпсилон должно быть больше нуля по условию! Повторите ввод: ";
		}
		else
			std::cout << "Ошибка ввода. Вы ввели не число! Повторите ввод: ";
	}
}
//Запрос действия у пользователя.
char GetChoice()
{
	while (true)
	{
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода! Вам нужно ввести номер Вашего выбора в соответсвии с вышеперечисленными пунктами (от 1 до 2). Повторите ввод." << std::endl;
	}
}
//Функция для преобразования введённой пользователем строки в число.
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


/*ФУНКЦИИ ВЫВОДА КОНКРЕТНЫХ ЗАДАЧ*/
//Вывод шапки общей таблицы, содержащей все методы.
void PrintСommonTable()
{
	std::cout << std::string(130, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "x_i  "
		"|" << std::setw(10) << "y_i  "
		"|" << std::setw(15) << "(y_i)^Э  "
		"|" << std::setw(20) << "  |y_i - (y_i)^Э|  "
		"|" << std::setw(15) << "(y_i)^(Р-К)  "
		"|" << std::setw(20) << "  |y_i - (y_i)^(Р-К)|  "
		"|" << std::setw(15) << "(y_i)^А    "
		"|" << std::setw(20) << "  |y_i - (y_i)^А|  "
		"|" << std::endl;
	std::cout << std::string(130, '_') << std::endl;
}
//Вывод шапки таблицы для Рунге-Кутта 4-ого порядка точности с двойным пересчетом.
void PrintRungeKuttTable()
{
	std::cout << std::string(116, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "x_i  "
		"|" << std::setw(10) << "y_i  "
		"|" << std::setw(15) << "(y_i)^(Р-К)  "
		"|" << std::setw(20) << "  |y_i - (y_i)^(Р-К)|  "
		"|" << std::setw(11) << "  h  "
		"|" << std::setw(15) << "  y_H     "
		"|" << std::setw(15) << " |y_h - y_H| "
		"|" << std::setw(15) << "  correct  "
		"|" << std::endl;
	std::cout << std::string(116, '_') << std::endl;
}


/*ПРОЧИЕ ФУНКЦИИ*/
double MyFunction(const double x_i, const double y_i)
{
	return pow(x_i, 3) * y_i;
}
double GetExactValue(const double x_i)
{
	return 2 * exp(pow(x_i, 4) / 4.f - 4);
}

/*ФУНКЦИИ ВЫВОДА РЕЗУЛЬТАТОВ РАСЧЕТОВ*/
void PrintFirstSecondTable(const double n)
{
	//Шапка таблицы.
	PrintСommonTable();
	//Шаг интерполирования.
	double h{ (b - a) / n };
	//Задача Коши для каждого метода и точного решения.
	double x_i{ x_0 }, x_i_adams[4]{};
	double y_i_euler{ y_0 }, y_i_r_k{ y_0 }, y_i_adams[4]{};
	int i{}; // Учет значений для Адамса.
	//Последующие значения.
	while (x_i - h < b)
	{
		ExactSolution(x_i);
		EulerMethod(h, x_i, y_i_euler);
		//Для Адамса, чтобы получать правильное значение до его изменения (в силу написанной программы).
		if (i <= 3)
		{
			x_i_adams[i] = x_i;
			y_i_adams[i] = y_i_r_k;
		}
		RungeKuttOrder4Method(h, x_i, y_i_r_k);
		if (i > 3) //Первые 4 значения при i = 0, 1, 2, 3 берутся из метода Р-К.
			AdamsMethod(h, x_i_adams, y_i_adams);
		else
		{
			std::cout << "|" << std::setw(14) << y_i_adams[i] <<
				"|" << std::setw(19) << abs(GetExactValue(x_i) - y_i_adams[i]);
		}
		x_i += h;
		i++;
		std::cout << "|" << std::endl;
		std::cout << std::string(130, '_') << std::endl;
	}
}
void PrintThirdFourthTable(const double n, const double epsilon)
{
	//Шаг интерполирования.
	double h{ (b - a) / n };
	std::cout << "Первоначальный шаг интерполирования: h = " << h << "." << std::endl;

	//Шапка таблицы.
	PrintRungeKuttTable();
	//Задача Коши для каждого метода и точного решения.
	double x_i{ x_0 };
	double y_i_r_k{ y_0 }, recalculation_x_y[2]{x_0, y_0};//Для запоминания y для пересчета.
	int i{}; // Учет числа проставленных точек для правильного выбора момента двойного пересчета.
	//Последующие значения.
	while (abs((x_i - h) - b) > 0.0001)
	{
		ExactSolution(x_i);
		RungeKuttOrder4WithRecalculationMethod(h, x_i, y_i_r_k, i, epsilon, recalculation_x_y);
		std::cout << std::endl;
		std::cout << std::string(116, '_') << std::endl;
	}
}


/*РАСЧЕТНЫЕ ФУНКЦИИ*/
//Точное решение задачи Коши.
void ExactSolution(const double x_i)
{
	double y_i{ GetExactValue(x_i) };

	std::cout << "|" << std::setw(9) << x_i <<
		"|" << std::setw(9) << y_i;
}
//Приближенное решение задачи Коши методом Эйлера.
void EulerMethod(const double h, const double x_i, double& y_i)
{
	double y_i_plus_1{ y_i + h * MyFunction(x_i, y_i) };

	std::cout << "|" << std::setw(14) << y_i <<
		"|" << std::setw(19) << abs(GetExactValue(x_i) - y_i);

	y_i = y_i_plus_1;
}
//Приближенное решение задачи Коши методом Рунге-Кутта 4-ого порядка точности без двойного пересчета.
void RungeKuttOrder4Method(const double h, const double x_i, double& y_i)
{
	double y_i_plus_1{ Calculation(h, x_i, y_i) };

	std::cout << "|" << std::setw(14) << y_i <<
		"|" << std::setw(23) << abs(GetExactValue(x_i) - y_i);

	y_i = y_i_plus_1;
}
//Приближенное решение задачи Коши методом Адамса.
void AdamsMethod(const double h, double x_i[], double y_i[])
{
	double y_i_plus_1{ y_i[3] + h / 24 * (55 * MyFunction(x_i[3], y_i[3]) - 59 * MyFunction(x_i[2], y_i[2]) + 37 * MyFunction(x_i[1],y_i[1]) - 9 * MyFunction(x_i[0],y_i[0])) };
	for (int i{}; i < 3;i++)
	{
		x_i[i] = x_i[i + 1];
		y_i[i] = y_i[i + 1];
	}
	x_i[3] = x_i[2] + h;

	std::cout << "|" << std::setw(14) << y_i_plus_1 <<
		"|" << std::setw(19) << abs(GetExactValue(x_i[3]) - y_i_plus_1);

	y_i[3] = y_i_plus_1;
}

//Приближенное решение задачи Коши методом Рунге-Кутта 4-ого порядка точности с двойным пересчетом.
double Calculation(const double h, const double x_i, const double y_i)
{
	double K1i{}, K2i{}, K3i{}, K4i{};

	K1i = h * MyFunction(x_i, y_i);
	K2i = h * MyFunction(x_i + h / 2.f, y_i + K1i / 2.f);
	K3i = h * MyFunction(x_i + h / 2.f, y_i + K2i / 2.f);
	K4i = h * MyFunction(x_i + h, y_i + K3i);
	return y_i + 1.f / 6.f * (K1i + 2 * K2i + 2 * K3i + K4i);
}
void RungeKuttOrder4WithRecalculationMethod(double& h, double& x_i, double& y_i, int& i, const double epsilon, double recalculation_x_y[])
{
	double y_i_plus_1{ Calculation(h,x_i,y_i) }, y_h{ y_i };
	double y_H{}, H{};

	if (i == 0 || i % 2 != 0)
	{
		std::cout << "|" << std::setw(14) << y_i <<
			"|" << std::setw(23) << abs(GetExactValue(x_i) - y_i) <<
			"|" << std::setw(10) << h <<
			"|" << std::setw(15) << std::setfill(' ') <<
			"|" << std::setw(15) << std::setfill(' ') <<
			"|" << std::setw(15) << std::setfill(' ') <<
			"|";
		y_i = y_i_plus_1;
		x_i += h;
		i += 1;
	}
	else
	{
		H = 2 * h;
		y_H = Calculation(H, recalculation_x_y[0], recalculation_x_y[1]);
		std::cout << "|" << std::setw(14) << y_i <<
			"|" << std::setw(23) << abs(GetExactValue(x_i) - y_i) <<
			"|" << std::setw(10) << h <<
			"|" << std::setw(14) << y_H <<
			"|" << std::setw(14) << abs(y_h - y_H);
		if (abs(y_h - y_H) > epsilon)
		{
			std::cout << "|" << std::setw(14) << "false";
			x_i = recalculation_x_y[0];
			y_i = recalculation_x_y[1];
			h = h / 2;
			i -= 2;
		}
		else
		{
			std::cout << "|" << std::setw(14) << "true";
			recalculation_x_y[0] = x_i;
			recalculation_x_y[1] = y_i;
			y_i = y_i_plus_1;
			x_i += h;
			i += 1;
		}
		std::cout << "|";
	}
}