#include <iostream>
#include <string>
#include <iomanip>

#include "constants.h"
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

/*ФУНКЦИИ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод первоначальной информации.
void prePrint()
{
	//Подпись.
	std::cout << std::setw(210) << "Горшков Андрей Олегович," << std::setw(210) << "группа 4312" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 3." << std::endl << std::endl;
	//Заданное нелинейной уравнение.
	std::cout << "Нелинейное уравнение:\n";
	std::cout << "exp(2x) + 4x = 0" << std::endl << std::endl;

	std::cout << "В результате проверок теорем о достаточных условиях для сходимости нелинейного уравнения к единственному решению на отрезке [a;b] был выбран отрезок [" << a << ";" << b << "]." << std::endl;
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
	std::cout << "1. Запустить программу по умолчанию (выданное требование).\n"
		<< "2. Задать в программе своё значение точности эпсилон и дельта, а затем выполнить МПИ, МН и ММН для заданного нелинейного уравнения.\n"
		<< "3. Выйти из программы." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3")
		{
			printDash();
			return choice[0];
		}
		else
			std::cout << "Вы должны ввести целое число от 1 до 3. Повторите ввод. " << std::endl;
	}
}

/*ФУНКЦИИ ВВОДА ОСНОВНЫХ ДАННЫХ ПРОГРАММЫ*/
//Функция получения значения максимального приближения эпсилон.
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
//Функция получения значения максимального приближения дельта.
double getDeltha()
{
	std::cout << "Введите значение дельты: ";
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
				std::cout << "Ошибка ввода. Значение дельты должно быть больше нуля по условию! Повторите ввод: ";
		}
		else
			std::cout << "Ошибка ввода. Вы ввели не число! Повторите ввод: ";
	}
}
//Функция для получения значения одной координаты начального приближения, заданного пользователем.
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
				std::cout << "Ошибка ввода. Начальное приближение должно принадлежать отрезку [" << a << ";" << b << "]. Повторите ввод:" << std::endl;
				std::cout << "x_0 = ";
			}
		else
			std::cout << "Ошибка ввода. Вы ввели не число! Повторите ввод: ";
	}
}
//Функция для задания начального приближения.
void getInitOfApproximation(double& approximate_x0)
{
	std::cout << "Задайте начальное приближение:" << std::endl;
	std::cout << "x_0 = ";
	approximate_x0 = getValueOfApproxCoordinate();
}

//Вывод шапки таблицы для метода простых итераций (МПИ), метода Ньютона (МН), модифицированного метода Ньютона (ММН).
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
//МПИ.
void simpleIterationMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_x0)
{
	printDash();
	//Вывод информации для МПИ.
	std::cout << "Метод простых итераций (МПИ) для заданного нелинейного уравнения." << std::endl;
	std::cout << "Начальное приближение:\t\t x_0 = " << user_approximate_x0 << "." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t " << user_deltha << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_k{ user_approximate_x0 }, x_k_plus_1{};
	unsigned int k{ 1 };
	//Шапка таблицы МПИ.
	printSIM_NM_MNM_table();
	//Итерационный процесс МПИ.
	while (true)
	{
		//Вычисление приближения следующего ((k+1)-ого) шага итерации.
		x_k_plus_1 = x_k + C * (exp(2 * x_k) + 4 * x_k);
		//Заполнение таблицы.
		std::cout << "|" << std::setw(5) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(14) << x_k_plus_1 <<
			"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(14) << abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) << 
			"|" << std::endl;
		std::cout << std::string(71, '_') << std::endl;
		//условие окончания итерационного процесса МПИ.
		if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <= user_deltha)
			break;
		//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
		k += 1;
		x_k = x_k_plus_1;
	}
	std::cout << std::endl << "Таким образом, решение нелинейного уравнения по МПИ с указанной точностью и начальным приближением: x = " << x_k_plus_1 << "." << std::endl;
}
//МН.
void NewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_x0)
{
	printDash();
	//Вывод информации для МН.
	std::cout << "Метод Ньютона (МН) для заданного нелинейного уравнения." << std::endl;
	std::cout << "Начальное приближение:\t\t x_0 = " << user_approximate_x0 << "." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t " << user_deltha << "." << std::endl;
	if ((exp(2 * user_approximate_x0) + 4 * user_approximate_x0) * 4 * exp(2 * user_approximate_x0) > 0)
	{
		//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
		double x_k{ user_approximate_x0 }, x_k_plus_1{};
		unsigned int k{ 1 };
		//Шапка таблицы МН.
		printSIM_NM_MNM_table();
		//Итерационный процесс МН.
		while (true)
		{
			//Вычисление приближения следующего ((k+1)-ого) шага итерации.
			x_k_plus_1 = x_k - ((exp(2 * x_k) + 4 * x_k) / (2 * exp(2 * x_k) + 4));
			//Заполнение таблицы.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(14) << abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(71, '_') << std::endl;
			//условие окончания итерационного процесса МН.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <= user_deltha)
				break;
			//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "Таким образом, решение нелинейного уравнения по МН с указанной точностью и начальным приближением: x = " << x_k_plus_1 << "." << std::endl;
	}
	else
	{
		std::cout << "Не выполняется достаточное условие сходимости МН." << std::endl << std::endl;
		std::cout << "Значение начального приближения x_0 должно быть выбрано из отрезка [a;b] = [" << a << "; " << b << "] так, чтобы " << "выполнялось следующее условие: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, т.е. (exp(2x_0) + 4x_0)*(4exp(2x_0)) > 0." << std::endl;
		std::cout << "В данном случае значение выражения равно: " << std::endl << (exp(2 * user_approximate_x0) + 4 * user_approximate_x0) * 4 * exp(2 * user_approximate_x0) << " < 0." << std::endl;
	}
}
//ММН.
void modifiedNewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_x0)
{
	printDash();
	//Вывод информации для ММН.
	std::cout << "Модифицированный метод Ньютона (ММН) для заданного нелинейного уравнения." << std::endl;
	std::cout << "Начальное приближение:\t\t x_0 = " << user_approximate_x0 << "." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t " << user_deltha << "." << std::endl;
	if (exp(2 * user_approximate_x0) + 4 * user_approximate_x0 > 0)
	{
		//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
		double x_k{ user_approximate_x0 }, x_k_plus_1{};
		double darivative_x0{ 2 * exp(2 * user_approximate_x0) + 4 };
		unsigned int k{ 1 };
		//Шапка таблицы ММН.
		printSIM_NM_MNM_table();
		//Итерационный процесс ММН.
		while (true)
		{
			//Вычисление приближения следующего ((k+1)-ого) шага итерации.
			x_k_plus_1 = x_k - ((exp(2 * x_k) + 4 * x_k) / darivative_x0);
			//Заполнение таблицы.
			std::cout << "|" << std::setw(5) << k <<
				"|" << std::setw(11) << x_k <<
				"|" << std::setw(14) << x_k_plus_1 <<
				"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(14) << abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(71, '_') << std::endl;
			//условие окончания итерационного процесса ММН.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(exp(2 * x_k_plus_1) + 4 * x_k_plus_1) <= user_deltha)
				break;
			//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "Таким образом, решение нелинейного уравнения по ММН с указанной точностью и начальным приближением: x = " << x_k_plus_1 << "." << std::endl;
	}
	else
	{
		std::cout << "Не выполняется достаточное условие сходимости ММН." << std::endl << std::endl;
		std::cout << "Значение начального приближения x_0 должно быть выбрано из отрезка [a;b] = [" << a << "; " << b << "] так, чтобы " << "выполнялось следующее условие: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, т.е. (exp(2x_0) + 4x_0)*(4exp(2x_0)) > 0." << std::endl;
		std::cout << "В данном случае значение выражения равно: " << std::endl << (exp(2 * user_approximate_x0) + 4 * user_approximate_x0) * 4 * exp(2 * user_approximate_x0) << " < 0." << std::endl;
	}
}