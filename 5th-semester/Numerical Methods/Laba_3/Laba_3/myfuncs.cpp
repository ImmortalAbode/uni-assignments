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
	std::cout << "Система нелинейных уравнений (СНУ):\n";
	std::cout << " _\n| x^2 - y^2 - 5 = 0;" << std::endl;
	std::cout << "<" << std::endl;
	std::cout << "|_x - y - 1 = 0." << std::endl << std::endl;

	std::cout << "Начальное приближение (1,0)." << std::endl;
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
			return convertStrToNumber(approx_coordinate);
		else
			std::cout << "Ошибка ввода. Вы ввели не число! Повторите ввод: ";
	}
}
//Функция для задания начального приближения.
void getInitOfApproximation_v2(double approximate_mass[])
{
	std::cout << "Вы хотите задать собственное начальное приближение или оставить заданное (1, 0) (\"новое\"/\"enter\")? ";
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
		else if (new_or_default_initial_approx == "новое")
		{
			std::cout << "Задайте начальное приближение:" << std::endl;
			std::cout << "x_0 = ";
			approximate_mass[0] = getValueOfApproxCoordinate();
			std::cout << "y_0 = ";
			approximate_mass[1] = getValueOfApproxCoordinate();
			break;
		}
		else
			std::cout << "Ошибка ввода. Введите либо ключевое слово \"новое\", либо нажмите \"enter\": ";
	}
}
void getInitOfApproximation(double approximate_mass[])
{
	std::cout << "Задайте начальное приближение:" << std::endl;
	std::cout << "Компонента x^(0) = ";
	approximate_mass[0] = getValueOfApproxCoordinate();
	std::cout << "Компонента y^(0) = ";
	approximate_mass[1] = getValueOfApproxCoordinate();
}

//Вывод шапки таблицы для метода простых итераций (МПИ), метода Ньютона (МН), модифицированного метода Ньютона (ММН).
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
//МПИ.
void simpleIterationMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[])
{
	printDash();
	//Вывод информации для МПИ.
	std::cout << "Метод простых итераций (МПИ) для заданной СНУ." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t " << user_deltha << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
	unsigned int k{ 1 };
	bool solution{ true };
	//Шапка таблицы МПИ.
	if (x_k != y_k)
		printSIM_NM_MNM_table();
	//Итерационный процесс МПИ.
	/*Проверка выполнения достаточного условия сходимости не требуется, т.к.оно всегда выполняется при заданных коэффициентах альфа, бета, гамма, дельта
	 *в итерационной формуле метода простых итераций (МПИ).
	 *Здесь учитывается возможность не существования какого-либо коэффициента в случае, если его выражение включает деление на 0 при заданном начальном приближиении.
	 */
	while (true)
	{
		//Вычисление приближения следующего ((k+1)-ого) шага итерации.
		x_k_plus_1 = x_k + 1 / (2 * (y_k - x_k)) * (pow(x_k, 2) - pow(y_k, 2) - 5) + y_k / (x_k - y_k) * (x_k - y_k - 1);
		y_k_plus_1 = y_k + 1 / (2 * (y_k - x_k)) * (pow(x_k, 2) - pow(y_k, 2) - 5) + x_k / (x_k - y_k) * (x_k - y_k - 1);
		if (x_k == y_k)
		{
			std::cout << std::endl << "Ошибка компонент начального приближения! Компоненты начального приближения x^(0) и y^(0) не должны быть равны друг другу, т.е. x^(0) != y^(0). " <<
				"В противном случае происходит деление на 0 в итерационной формуле метода простых итераций(МПИ)." << std::endl <<
				"В данном случае компоненты начального приближения равны друг другу, т.е: " << user_approximate_mass[0] << " = " << user_approximate_mass[1] << std::endl;
			solution = false;
			break;
		}
		else
		{
			//Заполнение таблицы.
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
			//условие окончания итерационного процесса МПИ.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(y_k_plus_1 - y_k) <= user_epsilon &&
				abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <= user_deltha && abs(x_k_plus_1 - y_k_plus_1 - 1) <= user_deltha)
				break;
			//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
	}
	if (solution)
		std::cout << std::endl << "Таким образом, решение системы нелинейных уравнений по МПИ с указанной точностью и начальным приближением: (x, y) = (" << x_k_plus_1 << ", " << y_k_plus_1 << ")." << std::endl;
	else
		std::cout << std::endl << "Вызвано исключение: деление на 0! Метод не имеет конечного результата." << std::endl;
}
//МН.
void NewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[])
{
	printDash();
	//Вывод информации для МН.
	std::cout << "Метод Ньютона (МН) для заданной СНУ." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t " << user_deltha << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
	unsigned int k{ 1 };
	bool solution{ true };
	//Шапка таблицы МН.
	if (2 * (y_k - x_k) != 0)
		printSIM_NM_MNM_table();
	//Итерационный процесс МН.
	/*Проверка существования обратной матрицы Якоби(матрица Якоби должна быть невырожденной) при заданном начальном приближении,
	 *т.к. в противном случае метод Ньютона (МН) применить будет невозможно.
	 */
	while (true)
	{
		//Вычисление приближения следующего ((k+1)-ого) шага итерации.
		x_k_plus_1 = x_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_k - y_k)) + (y_k * (x_k - y_k - 1) / (y_k - x_k)));
		y_k_plus_1 = y_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_k - y_k)) + (x_k * (x_k - y_k - 1) / (y_k - x_k)));
		if (2 * (y_k - x_k) != 0)
		{
			//Заполнение таблицы.
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
			//условие окончания итерационного процесса МН.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(y_k_plus_1 - y_k) <= user_epsilon &&
				abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <= user_deltha && abs(x_k_plus_1 - y_k_plus_1 - 1) <= user_deltha)
				break;
			//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
			y_k = y_k_plus_1;
		}
		else
		{
			if (k == 1)
			{
				std::cout << std::endl << "Ошибка начального приближения! При заданном начальном приближении обратная матрица Якоби не существует, " << std::endl <<
					"поэтому метод Ньютона (МН) не может быть использован. Покажем вышесказанное: " << std::endl;
				std::cout << "\t   | 2x^(0)\t-2y^(0)  |" << std::endl;
				std::cout << "  _" << std::endl;
				std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) + 2y^(0) = 2 * (" << user_approximate_mass[1] << " - " << user_approximate_mass[0] << ") = " <<
					"2 * ((" << user_approximate_mass[1] << ") - (" << user_approximate_mass[0] << ")) = 0." << std::endl;
				std::cout << "Таким образом, матрица Якоби вырожденная, т.е. обратной матрицы Якоби не существует." << std::endl;
			}
			else
			{
				std::cout << std::endl << "Ошибка " << k + 1 << "-го приближения! При заданном приближении обратная матрица Якоби не существует, " << std::endl <<
					"поэтому метод Ньютона (МН) не может быть использован. Покажем вышесказанное: " << std::endl;
				std::cout << "\t   | 2x^(" << k + 1 << ")\t-2y^(" << k + 1 << ") | " << std::endl;
				std::cout << "  _" << std::endl;
				std::cout << "J(w^(" << k + 1 << ")) = |\t1\t-1\t| = -2x^(" << k + 1 << ") + 2y^(" << k + 1 << ") = 2 * (" << y_k << " - " << x_k << ") = " <<
					"2 * ((" << x_k << ") - (" << y_k << ")) = 0." << std::endl;
				std::cout << "Таким образом, матрица Якоби вырожденная, т.е. обратной матрицы Якоби на данном шаге итерации не существует." << std::endl;
			}
			solution = false;
			break;
		}
	}
	if (solution)
		std::cout << std::endl << "Таким образом, решение системы нелинейных уравнений по МПИ с указанной точностью и начальным приближением: (x, y) = (" << x_k_plus_1 << ", " << y_k_plus_1 << ")." << std::endl;
	else
		std::cout << std::endl << "Не выполняется условие для сходимости МН." << std::endl;
}
//ММН.
void modifiedNewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[])
{
	printDash();
	//Вывод информации для ММН.
	std::cout << "Модифицированный метод Ньютона (ММН) для заданной СНУ." << std::endl;
	std::cout << std::setw(34) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\t W_(0) = " << "(" << user_approximate_mass[0] << ", " << user_approximate_mass[1] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t " << user_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t " << user_deltha << "." << std::endl;
	//Инициализация переменных для хранения k-ого и (k+1)-ого приближения у итераций.
	double x_0{ user_approximate_mass[0] }, y_0{ user_approximate_mass[1] };
	double x_k{ user_approximate_mass[0] }, y_k{ user_approximate_mass[1] }, x_k_plus_1{}, y_k_plus_1{};
	unsigned int k{ 1 };
	bool solution{ true }, method_converges{ true };

	//Шапка таблицы ММН.
	if (2 * (y_0 - x_0) != 0)
		printSIM_NM_MNM_table();
	//Итерационный процесс ММН.
	/* Проверка существования обратной матрицы Якоби(матрица Якоби должна быть невырожденной) при заданном начальном приближении,
	 *т.к. в противном случае модифицированный метод Ньютона (ММН) применить будет невозможно.
	 */
	while (true)
	{
		//Вычисление приближения следующего ((k+1)-ого) шага итерации.
		x_k_plus_1 = x_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_0 - y_0)) + (y_0 * (x_k - y_k - 1) / (y_0 - x_0)));
		y_k_plus_1 = y_k - ((pow(x_k, 2) - pow(y_k, 2) - 5) / (2 * (x_0 - y_0)) + (x_0 * (x_k - y_k - 1) / (y_0 - x_0)));
		if (2 * (y_0 - x_0) != 0)
		{
			//Заполнение таблицы.
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
			//условие окончания итерационного процесса ММН.
			if (abs(x_k_plus_1 - x_k) <= user_epsilon && abs(y_k_plus_1 - y_k) <= user_epsilon &&
				abs(pow(x_k_plus_1, 2) - pow(y_k_plus_1, 2) - 5) <= user_deltha && abs(x_k_plus_1 - y_k_plus_1 - 1) <= user_deltha)
				break;
			//Переход к следующей итерации, если условие окончания итерационного процесса еще не было удовлетворено.
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
			std::cout << std::endl << "Ошибка начального приближения! При заданном начальном приближении обратная матрица Якоби не существует, " << std::endl <<
				"поэтому метод Ньютона (МН) не может быть использован. Покажем вышесказанное: " << std::endl;
			std::cout << "\t   | 2x^(0)\t-2y^(0)  |" << std::endl;
			std::cout << "  _" << std::endl;
			std::cout << "J(w^(0)) = |\t1\t-1\t| = -2x^(0) + 2y^(0) = 2 * (" << user_approximate_mass[1] << " - " << user_approximate_mass[0] << ") = " <<
				"2 * ((" << user_approximate_mass[1] << ") - (" << user_approximate_mass[0] << ")) = 0." << std::endl;
			std::cout << "Таким образом, матрица Якоби вырожденная, т.е. обратной матрицы Якоби не существует." << std::endl;
			solution = false;
			break;
		}
	}
	if (solution && method_converges)
		std::cout << std::endl << "Таким образом, решение системы нелинейных уравнений по МПИ с указанной точностью и начальным приближением: (x, y) = (" << x_k_plus_1 << ", " << y_k_plus_1 << ")." << std::endl;
	else
	{
		if (!solution)
			std::cout << std::endl << "Не выполняется условие для сходимости ММН." << std::endl;
		if (!method_converges)
			std::cout << std::endl << "Модифицированный метод Ньютона расходится, т.к. обратная матрица Якоби не является непрерывной и мало меняющейся " <<
			"в области (окрестности), в которой ищем решение." << std::endl;
	}
}