#include <iostream>
#include <string>
#include <iomanip>

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
		return negative_number ? static_cast<double>(-number/number_2) : static_cast<double>(number/number_2);
}

/*ФУНКЦИИ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод первоначальной информации.
void prePrint()
{
	//Подпись.
	std::cout << std::setw(210) << "Горшков Андрей Олегович," << std::setw(210) << "группа 4312" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 3." << std::endl;
	//Изначальная СЛАУ.
	std::cout << "Cистема линейных алгебраических уравнений (СЛАУ):\n";
	std::cout << " _\n|  5x - y - z = 3;\n|\n<  6x - 8y + z = -1;\n|\n|_ 2x - 3y + 10z = 9." << std::endl << std::endl;

	//Приведенная СЛАУ.
	std::cout << "Приведённая СЛАУ:\n";
	std::cout << " _\n|  x = 0.6 + 0.2y + 0.2z;\n|\n<  y = 0.125 + 0.75x + 0.125z;\n|\n|_ z = 0.9 - 0.2x + 0.3y" << std::endl;
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
		<< "2. Задать в программе своё значение точности эпсилон, а затем выполнить МПИ, МЗ и МР для заданного СЛАУ.\n"
		<< "3. Выйти из программы." << std::endl;
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Функция нахождения максимального числа из трёх.
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
//Функция для получения значения одной координаты начального приближения, заданного пользователем.
double getValueOfApproxCoordinate()
{
	while (true)
	{
		std::string approx_coordinate{};
		std::getline(std::cin, approx_coordinate);
		if (checkStrIsNumeric(approx_coordinate))
			return convertStrToNumber(approx_coordinate);
		else
			std::cout << "Ошибка ввода. Вы ввели не число! Повторите ввод: ";
	}
}
//Функция для задания начального приближения.
void getInitOfApproximation(double approximate_mass[])
{
	std::cout << "Задайте начальное приближение:" << std::endl;
	std::cout << "x_(0) = ";
	approximate_mass[0] = getValueOfApproxCoordinate();
	std::cout << "y_(0) = ";
	approximate_mass[1] = getValueOfApproxCoordinate();
	std::cout << "z_(0) = ";
	approximate_mass[2] = getValueOfApproxCoordinate();
}

//Вывод шапки таблицы для метода простых итераций (МПИ) и метода Зейделя (МЗ).
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
		"|" << std::setw(13) << "Сумма|" << std::endl;
	std::cout << std::string(167, '_') << std::endl;
}
//МПИ.
void simpleIterationMethod(const double& user_epsilon, const double user_approximate_mass[])
{
	printDash();
	//Вывод информации для МПИ.
	std::cout << "Метод простых итераций (МПИ) для заданной СЛАУ." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ", " << user_approximate_mass[2] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, z_k{ user_approximate_mass[2] }, x_k_plus_1{}, y_k_plus_1{}, z_k_plus_1{};
	unsigned int k{ 1 };
	//Шапка таблицы МПИ.
	printSIMandSMTable();
	//Итерационный процесс МПИ.
	while (true)
	{
		//Вычисление приближения следующего ((k+1)-ого) шага итерации.
		x_k_plus_1 = 0.6f + 0.2f * y_k + 0.2f * z_k;
		y_k_plus_1 = 0.125f + 0.75f * x_k + 0.125f * z_k;
		z_k_plus_1 = 0.9f - 0.2f * x_k + 0.3f * y_k;
		//Заполнение таблицы.
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
		//условие окончания итерационного процесса МПИ.
		if (abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <= user_epsilon)
			break;
		//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
		k += 1;
		x_k = x_k_plus_1;
		y_k = y_k_plus_1;
		z_k = z_k_plus_1;
	}
	std::cout << std::endl << "Таким образом, решение СЛАУ по МПИ с указанной точностью и начальным приближением: (x, y, z) = " << "(" << x_k_plus_1 << ", " << y_k_plus_1 << ", " << z_k_plus_1 << ")." << std::endl;
}
//МЗ.
void seidelMethod(const double& user_epsilon, const double user_approximate_mass[])
{
	printDash();
	//Вывод информации для МЗ.
	std::cout << "Метод Зейделя (МЗ) для заданной СЛАУ." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ", " << user_approximate_mass[2] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, z_k{ user_approximate_mass[2] }, x_k_plus_1{}, y_k_plus_1{}, z_k_plus_1{};
	unsigned int k{ 1 };
	//Шапка таблицы МЗ.
	printSIMandSMTable();
	//Итерационный процесс МЗ.
	while (true)
	{
		//Вычисление приближения следующего ((k+1)-ого) шага итерации.
		x_k_plus_1 = 0.6f + 0.2f * y_k + 0.2f * z_k;
		y_k_plus_1 = 0.125f + 0.75f * x_k_plus_1 + 0.125f * z_k;
		z_k_plus_1 = 0.9f - 0.2f * x_k_plus_1 + 0.3f * y_k_plus_1;
		//Заполнение таблицы.
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
		//условие окончания итерационного процесса МЗ.
		if (abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <= user_epsilon)
			break;
		//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
		k += 1;
		x_k = x_k_plus_1;
		y_k = y_k_plus_1;
		z_k = z_k_plus_1;
	}
	std::cout << std::endl << "Таким образом, решение СЛАУ по МЗ с указанной точностью и начальным приближением: (x, y, z) = " << "(" << x_k_plus_1 << ", " << y_k_plus_1 << ", " << z_k_plus_1 << ")." << std::endl;
}
//Вывод шапки таблицы для метода релаксации (ослабления) (МР).
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
//МР.
void relaxationMethod(const double& user_epsilon, const double user_approximate_mass[])
{
	printDash();
	//Вывод информации для МР.
	std::cout << "Метод релаксации (ослабления) (МР) для заданной СЛАУ." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ", " << user_approximate_mass[2] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, z_k{ user_approximate_mass[2] }, Rx_k{}, Ry_k{}, Rz_k{};
	unsigned int k{};
	//Шапка таблицы МР.
	printRMTable();
	//Итерационный процесс МР.
	while (true)
	{
		//Вычисление невязок на k-ом шаге итерации.
		Rx_k = 0.6f - x_k + 0.2f * y_k + 0.2f * z_k;
		Ry_k = 0.125f + 0.75f * x_k - y_k + 0.125f * z_k;
		Rz_k = 0.9f - 0.2f * x_k + 0.3f * y_k - z_k;
		//условие окончания итерационного процесса МЗ.
		if (abs(Rx_k) <= user_epsilon && abs(Ry_k) <= user_epsilon && abs(Rz_k) <= user_epsilon)
			break;
		double max{ getMaxOfThreeNumbers(abs(Rx_k), abs(Ry_k), abs(Rz_k)) };
		//Заполнение таблицы.
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
		//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
		k += 1;
		if (max == abs(Rx_k))
			x_k += Rx_k;
		else if (max == abs(Ry_k))
			y_k += Ry_k;
		else
			z_k += Rz_k;
	}
	std::cout << std::endl << "Таким образом, решение СЛАУ по МР с указанной точностью и начальным приближением: (x, y, z) = " << "(" << x_k << ", " << y_k << ", " << z_k << ")." << std::endl;
}