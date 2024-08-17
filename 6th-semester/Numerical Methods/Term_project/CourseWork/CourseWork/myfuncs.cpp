#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>
#include <vector>

#include "constants.h"
#include "myfuncs.h"

/*-------------------------------
 * ОБЩИЕ ФУНКЦИИ ВВОДА И ВЫВОДА |
--------------------------------*/
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
	std::cout << std::string(90, ' ') << "Тема курсовой работы:\n" << std::endl;
	std::cout << std::string(50, ' ') << "Тема 3. Решение алгебраического уравнения с двумя парами комплексных корней методом Лобачевского - Греффе\n" << std::endl;
	std::cout << " Вариант индивидуального задания: 3.\n" << std::endl;
	std::cout << " Заданное алгебраическое уравнение:\nx^4 + 2x^3 + 2x^2 - 8x + 16 = 0\n" << std::endl;
}
//Пользовательское меню.
void PrintMenu()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1. Запустить программу." << std::endl <<
		"2. Выйти из программы." << std::endl;
}
/*-------------------------------------------
 * ФУНКЦИИ ПРОВЕРКИ ПОЛЬЗОВАТЕЛЬСКОГО ВВОДА |
--------------------------------------------*/
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
	std::cout << "Введите значение эпсилон - степень точности равенства значения квадрата предыдущего коэффициента по отношению к текущему: ";
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
/*-----------------------------------------
 * ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ РЕШЕНИЯ ЗАДАЧИ |
------------------------------------------*/
//Вывод шапки таблицы.
void PrintHeadTable()
{
	std::cout << std::string(115, '_') << std::endl;
	std::cout << "|" << std::setw(9) << " Степени " <<
		"|" << std::setw(20) << "x^4        " <<
		"|" << std::setw(20) << "x^3        " <<
		"|" << std::setw(20) << "x^2        " <<
		"|" << std::setw(20) << "x^1        " <<
		"|" << std::setw(20) << "x^0        " <<
		"|" << std::endl;
	std::cout << std::string(115, '_') << std::endl;
}
//Функция определения порядка значений.
long long int GetValueOrder(const long double& num)
{
	long double temp{ num };
	long long int order{};
	while (temp / 10 > 1)
	{
		temp /= 10;
		order++;
	}
	return order;
}
//Функция понижения степени (нужна для корректности данных).
long long int LowerValueOrder(const long double& num)
{
	long double temp{ num };
	long long int order{};
	while (temp * 10 < 1)
	{
		temp *= 10;
		order++;
	}
	return order;
}
//Функция приведения значений к виду a*10^m, где а<10, а m - целое число (обновление векторов порядков).
//Значения k и s вспомогательные - для определения того, какие именно значения из вектора следует брать в различных случаях учета порядков.
long double UpdateDegrees(std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees, long double& num, const long long int& k, const long long int& s, const std::string& type)
{
	//Сразу находим порядок поступившего числа для корректировки имеющегося порядка (число не превышает 10 после того, как достигнет порядка 10^4).
	long long int add_order{ GetValueOrder(abs(num)) };
	if (type == "coef_squared")
	{
		//Если число >9999, то есть достигает порядка 10^4, то округляем его и заносим первый порядок в вектор.
		if (abs(num) >= 9999)
		{
			num = num / pow(10, add_order);
			values_degrees.back().push_back(add_order);
		}
		//Если число <1, то восстанавливаем его порядок так, чтобы значащие цифры числа были видны.
		else if (abs(num) < 1 && coefs_degrees.back()[k] != 0)
		{
			add_order = LowerValueOrder(abs(num));
			num = num * pow(10, add_order);
			values_degrees.back().push_back(coefs_degrees.back()[k] * 2 - add_order);
		}
		else
		{
			//Если число <9999, то рассматриваем случаи, когда реальное число уже > 10^4 и когда еще не достигло 10^4.
			if (coefs_degrees.back()[k] != 0)
			{
				num = num / pow(10, add_order);
				values_degrees.back().push_back(coefs_degrees.back()[k] * 2 + add_order);
			}
			else
				values_degrees.back().push_back(0);
		}
	}
	else if (type == "double_products")
	{
		//Поиск удвоенных произведений соседей на общий порядок значений не влияет, но его нужно правильно привести, чтобы текущий порядок был применим.
		//Смысл работать с порядком данного значения возникает только в случае, когда это число уже привысило 10^4.
		if (num == 0.0f)
			num = 0.0f;
		if (values_degrees.back()[k] != 0)
			//Искомый порядок будет равен сумме порядков соседей + собственный порядок числа - порядок первого значения (квадрат коэффицента). 
			//Если порядки отличаются более, чем на 5, то значение равно 0, так как оно влияния не оказывает на общее поведение коэффициента.
			if (abs(coefs_degrees.back()[k - s] + coefs_degrees.back()[k + s] + add_order - values_degrees.back()[k]) >= 5)
				num = 0;
			//Если порядки отличаются менее, чем на 5, то в текущем значении еще есть значащие цифры - округляем.
			else
				num = num / pow(10, values_degrees.back()[k] - coefs_degrees.back()[k - s] - coefs_degrees.back()[k + s]);
	}
	else if (type == "new_coef")
	{
		//Если коэффициент превышает 10, то работа аналогична квадратам коэффициентов для значений при подсчете следующего коэффициента. В противном случае (<10) коэффициент имеет прежний порядок.
		if (abs(num) >= 10)
		{
			if (values_degrees.back()[k] != 0)
			{
				num = num / pow(10, add_order);
				coefs_degrees.back().push_back(values_degrees.back()[k] + add_order);
			}
			else
			{
				coefs_degrees.back().push_back(0);
			}
		}
		else
		{
			if (num == 0)
				coefs_degrees.back().push_back(0);
			else
				coefs_degrees.back().push_back(values_degrees.back()[k]);
		}
	}

	return num;
}
//Получение максимальной длины элемента вектора вектора таблицы для корректного вывода.
int GetMaxLength(const std::vector<std::vector<std::vector<long double>>>& table)
{
	int max_count_of_elemenets{};
	for (int i{}; i < table.size(); i++)
		for (int j{}; j < table[i].size(); j++)
			if (table[i][j].size() > max_count_of_elemenets)
				max_count_of_elemenets = table[i][j].size();
	return max_count_of_elemenets;
}
//Поиск столбцов процесса квадрирования, где прослеживаются комплексные корни.
void FindComplexColumns(const std::vector<std::vector<std::vector<long double>>>& table, long long int& first_complex_column, long long int& second_complex_column)
{
	for (long long int row{ 1 }; row < table.size(); row++)
	{
		bool first_negative_coef{ false };
		long long int count_negative_coef{};
		for (long long column{ 1 }; column < table[row].size() - 1; column++)
		{
			if (table[row][column][0] < 0)
				count_negative_coef++;
		}
		for (long long column{ 1 }; column < table[row].size() - 1; column++)
		{
			if (table[row][column][0] < 0 && !first_negative_coef && count_negative_coef == 2)
			{
				first_complex_column = column;
				first_negative_coef = true;
			}
			if (table[row][column][0] < 0 && first_negative_coef && count_negative_coef == 2)
			{
				second_complex_column = column;
			}
		}
	}
}
/*---------------------------------
 * ОСНОВНЫЕ ФУНКЦИИ РЕШЕНИЯ ЗАДАЧИ |
-----------------------------------*/
//Функция добавления в вектор дополнительных значений для нахождения следующего коэффициента.
void Add2aa(std::vector<std::vector<long double>>& cur_row, std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees)
{
	std::vector<long long int> new_values_degrees{};
	values_degrees.push_back(new_values_degrees);
	for (long long int k{}; k < cur_row.size(); k++)
	{
		long double coef_squared{ pow(cur_row[k][0],2) };
		cur_row[k].push_back(UpdateDegrees(coefs_degrees, values_degrees, coef_squared, k, -1, "coef_squared"));
		for (long long int s{ 1 }; s <= k; s++)
		{
			long double doubleProducts{};
			if ((k - s < 0) || (k + s > (cur_row.size() - 1)))
			{
				doubleProducts = 0;
			}
			else
			{
				doubleProducts = 2 * pow(-1, s) * cur_row[k - s][0] * cur_row[k + s][0];
				cur_row[k].push_back(UpdateDegrees(coefs_degrees, values_degrees, doubleProducts, k, s, "double_products"));
			}
		}
	}
}
//Функция нахождения нового значения коэффициента (квадрирование).
void AddNewCoef(std::vector<std::vector<std::vector<long double>>>& table, std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees)
{
	std::vector<std::vector<long double>> new_row{};
	std::vector<long long int> new_coef_degrees{};
	coefs_degrees.push_back(new_coef_degrees);
	for (unsigned i{}; i < table.back().size(); i++)
	{
		long double newA{};
		for (unsigned j{ 1 }; j < table.back()[i].size(); j++)
			newA += table.back()[i][j];
		newA = UpdateDegrees(coefs_degrees, values_degrees, newA, i, -1, "new_coef");
		new_row.push_back(std::vector<long double>{newA});
	}
	table.push_back(new_row);
}
//Проверка близости шагов квадрирования для выхода из процесса.
bool Equal(const std::vector<std::vector<std::vector<long double>>>& table, const std::vector<std::vector<long long int>>& coefs_degrees, const long double& epsilon)
{
	long long int
		first_complex_column{},
		second_complex_column{};
	FindComplexColumns(table, first_complex_column, second_complex_column);

	//Учитывает число удовлетворяющих колонок за исключением крайних (для них выполняется всегда) и комплексных.
	long long int number_of_completed{};
	for (unsigned i{ 1 }; i < table.back().size() - 1; i++)
	{
		if (i != first_complex_column && i != second_complex_column)
		{
			long double last_coef_squared{ pow(table[table.size() - 2][i][0], 2) };
			long double cur_coef{ table.back()[i][0] };
			//Находим разность порядков значений для более корректного и быстро счета.
			long long int order_last_coef{ coefs_degrees[coefs_degrees.size() - 2][i] * 2 };
			long long int order_cur_coef{ coefs_degrees.back()[i] };
			long long int diff_degree{ abs(order_cur_coef - order_last_coef) };
			//Уравнивание порядков представления значений.
			if (order_cur_coef > order_last_coef)
				last_coef_squared /= pow(10, diff_degree);
			else
				cur_coef /= pow(10, diff_degree);
			//Сравнение близости чисел.
			if (cur_coef >= last_coef_squared)
			{
				if (last_coef_squared != 0.0f)
				{
					if (abs(cur_coef / last_coef_squared - 1.0f) < epsilon)
						number_of_completed++;
				}
			}
			else
			{
				if (cur_coef != 0.0f)
				{
					if (abs(last_coef_squared / cur_coef - 1.0f) < epsilon)
						number_of_completed++;
				}
			}
		}
	}
	/*table.back().size() - число столбцов в строке.
	* - 2 - не учитываем крайние колонки
	* - 2 - не учитываем комплекасные колонки (в данном случае их 2)
	*/
	return (number_of_completed == table.back().size() - 2 - 2 ? true : false);
}
//Вывод результатов на экран.
void PrintTable(const std::vector<std::vector<std::vector<long double>>>& table, std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees)
{
	//Шапка таблицы.
	PrintHeadTable();
	int max_length{ GetMaxLength(table) };
	for (unsigned row{}; row < table.size(); row++)
	{
		std::cout << "|" << std::right << std::setw(9) << pow(2, row) << "|";
		for (int element{}; element < max_length; element++)
		{
			for (int column{}; column < table[row].size(); column++)
			{
				//Если такой порядковый номер элемента присутствует в значениях.
				if (element < table[row][column].size())
				{
					long long int coef_order{ coefs_degrees[row][column] };
					long long int value_order{};
					//Последняя строка не содержит квадратов коэффициентов и подсчитанных удвоенных произведений соседних коэффициентов.
					if (row != table.size() - 1)
						value_order = values_degrees[row][column];
					//Вывод коэффициентов.
					if (element == 0)
					{
						if (coef_order != 0)
							if (table[row][column][element] == 0)
								std::cout << std::right << std::setw(11) << table[row][column][element] << "         |";
							else
								std::cout << std::right << std::fixed << std::setprecision(5) <<
								std::setw(11) << table[row][column][element] << " * 10^" << std::left << std::setw(3) << coefs_degrees[row][column] << "|" <<
								std::defaultfloat;
						else
							std::cout << std::right << std::setw(11) << table[row][column][element] << "         |";
					}
					//Вывод значений к коэффициентам.
					else
					{
						//У крайних колонок не выводим значения, у остальных - выводим.
						if (column != 0 && column != table[row].size() - 1)
							if (value_order != 0)
								if (table[row][column][element] == 0)
									std::cout << std::right << std::setw(11) << table[row][column][element] << "         |";
								else
									std::cout << std::right << std::fixed << std::setprecision(5) <<
									std::setw(11) << table[row][column][element] << " * 10^" << std::left << std::setw(3) << values_degrees[row][column] << "|" <<
									std::defaultfloat;
							else
								std::cout << std::right << std::setw(11) << table[row][column][element] << "         |";
						else
							std::cout << std::right << std::setw(20) << " " << "|";
					}
				}
				//Если его нет и это не последняя строка таблицы, то делаем отступ.
				else if (row != table.size() - 1)
					std::cout << std::right << std::setw(20) << " " << "|";
			}
			//Если это не последняя строка таблицы.
			if (row != table.size() - 1)
			{
				std::cout << std::endl;
				//После коэффициентов делаем прерывистую строку
				if (element == 0)
					std::cout << std::string(115, '-') << std::endl;
				//Под коэффициентами делаем отступ.
				if (element != max_length - 1)
					std::cout << "|" << std::right << std::setw(10) << "|";
			}
		}
		//Если это последняя строка таблицы, то завершаем вывод.
		if (row == table.size() - 1)
			std::cout << std::endl;
		std::cout << std::string(115, '_') << std::endl;
	}
}
//Получение решения полнинома (уравнения).
void GetSolutions(const std::vector<std::vector<std::vector<long double>>>& table, std::vector<std::vector<long long int>>& coefs_degrees, const long double& rude_up, const long double& rude_down)
{
	//Вектор действительных корней.
	std::vector<long double> real_roots{};

	//Поиск столбцов процесса квадрирования, где прослеживаются комплексные корни.
	long long int
		find_column1{},
		find_column2{};
	FindComplexColumns(table, find_column1, find_column2);
	//Нахождение квадратов модулей комплексных корней.
	long double
		b_k_plus_1{}, order_b_k_plus_1{},
		b_k_minus_1{}, order_b_k_minus_1{},
		b_m_plus_1{}, order_b_m_plus_1{},
		b_m_minus_1{}, order_b_m_minus_1{};
	long long int degree_of_squaring{ static_cast<long long int>(pow(2, table.size() - 1)) };
	//Определение коэффицентов для поиска комплексных корней.
	if (find_column1 != 0 && find_column2 != 0)
	{
		b_k_minus_1 = table.back()[find_column1 - 1][0]; order_b_k_minus_1 = coefs_degrees.back()[find_column1 - 1];
		b_k_plus_1 = table.back()[find_column1 + 1][0]; order_b_k_plus_1 = coefs_degrees.back()[find_column1 + 1];
		b_m_minus_1 = table.back()[find_column2 - 1][0]; order_b_m_minus_1 = coefs_degrees.back()[find_column2 - 1];
		b_m_plus_1 = table.back()[find_column2 + 1][0]; order_b_m_plus_1 = coefs_degrees.back()[find_column2 + 1];
	}
	if (b_k_minus_1 == 0 || b_k_plus_1 == 0 || b_m_minus_1 == 0 || b_m_plus_1 == 0)
	{
		std::cout << "Данное уравнение не относится к случаю двух пар комплексных корней, либо процесс квадрирования был завершен раньше. Попробуйте увеличить точность сравнения." << std::endl;
		return;
	}
	//Основные значения для квадратов модулей комплексных корней.
	long double
		r_1_squared{ pow(b_k_plus_1 / b_k_minus_1 * pow(10, order_b_k_plus_1 - order_b_k_minus_1), 1.0f / degree_of_squaring) },
		r_2_squared{ pow(b_m_plus_1 / b_m_minus_1 * pow(10, order_b_m_plus_1 - order_b_m_minus_1), 1.0f / degree_of_squaring) };
	long double
		sigma{},
		sigma_inverse{};
	/*Процесс нахождения действительных корней, если они есть.*/
	//Начало вывода корней уравнения.
	std::cout << "Искомые корни заданного уравнения: " << std::endl;
	int count_x{}; //счетчик корней
	if (table.back().size() <= 5)
	{
		sigma = 0;
		sigma_inverse = 0;
	}
	else
	{
		std::cout << std::endl;
		/*
		* |x| = (root*10^n)^1/m
		* ln(|x|) = ln[(root*10^n)^1/m]
		* ln(|x|) = 1/m * ln(root*10^n)
		* ln(|x|) = 1/m * [ln(root) + n*ln10]
		* |x| = e^{1/m * [ln(root) + n*ln10]}
		* где root = d2/d1, n = n2 - n1;
		* n2 имеет меньший индекс, чем n1
		*/
		//Нахождение модулей действительных корней.
		for (long long int i{ 1 }; i < table.back().size(); i++) {
			if (i != find_column1 && i != find_column1 + 1 && i != find_column2 && i != find_column2 + 1 &&
				i - 1 != find_column1 && i - 1 != find_column1 + 1 && i - 1 != find_column2 && i - 1 != find_column2 + 1)
			{
				long double coefs_difference{ table.back()[i][0] / table.back()[i - 1][0] };
				long long int degrees_difference{ coefs_degrees.back()[i] - coefs_degrees.back()[i - 1] };
				long double d{ exp(1.0f / degree_of_squaring * (log(coefs_difference) + degrees_difference * log(10))) };
				real_roots.push_back(d);
			}
		}
		//Определение знака действительного корня.
		for (long long int i{}; i < real_roots.size(); i++)
		{
			long double
				posRoot{ real_roots[i] },
				negRoot{ -real_roots[i] };
			long double
				posSum{ },
				negSum{ };
			for (long long int j{ static_cast<long long int>(table[0].size() - 1) }; j >= 0;j--)
			{
				posSum += table[0][table[0].size() - 1 - j][0] * pow(posRoot, j);
				negSum += table[0][table[0].size() - 1 - j][0] * pow(negRoot, j);
			}
			count_x++;
			std::cout << "Модуль действительного корня |x_" << count_x << "| = " << real_roots[i] << std::endl;
			std::cout << "Значение полинома при х_" << count_x << " = " << posRoot << ": " << posSum << std::endl;
			std::cout << "Значение полинома при х_" << count_x << " = " << negRoot << ": " << negSum << std::endl;
			if (abs(posSum) > abs(negSum))
			{
				real_roots[i] = -real_roots[i];
			}
			std::cout << "x_" << count_x << " = " << real_roots[i] << std::endl << std::endl;
		}
		//Нахождение sigma и sigma_inverse.
		for (long long int i{}; i < real_roots.size();i++)
		{
			sigma += real_roots[i];
			sigma_inverse += 1.0f / real_roots[i];
		}
	}
	//Решение системы.
	long double
		summa_u1_u2{ (-1 * base_coefs[1][0] / (2 * base_coefs[0][0]) - 1.0f / 2 * sigma == 0.0f) ? 0.0f : (-1 * base_coefs[1][0] / (2 * base_coefs[0][0]) - 1.0f / 2 * sigma) },
		summa_u1_r1_squared_u2_r2_squared{ -1 * base_coefs[base_coefs.size() - 2][0] / (2 * base_coefs.back()[0]) - 1.0f / 2 * sigma_inverse };
	//Подсчет действительной и мнимой части комплексного числа.
	long double u1{}, u2{}, v1{}, v2{};
	/*
	* A = -a_1/(2*a_0) - 1/2*sigma
	* B = -a_n_minus_1/(2*a_n) - 1/2*sigma_inverse
	*
	* u1 + u2 = A
	* u1/r1^2 + u2/r2^2 = B
	*
	* u1 = A - u2
	*
	* (A - u2)/r1^2 + u2/r2^2 = B
	* (r2^2 * (A - u2) + r1^2 * u2)/(r1^2 * r2^2) = B
	* (r2^2 * A + u2 * (r1^2 - r2^2) = B * r1^2 * r2^2
	* u2 = (r1^2 * r2^2 * B - r2^2 * A) / (r1^2 - r2^2)
	*/
	u2 = (r_1_squared * r_2_squared * summa_u1_r1_squared_u2_r2_squared - r_2_squared * summa_u1_u2) / (r_1_squared - r_2_squared);
	u1 = summa_u1_u2 - u2;

	v1 = sqrt(r_1_squared - pow(u1, 2));
	v2 = sqrt(r_2_squared - pow(u2, 2));
	//Вывод искомых корней уравнения.
	if (real_roots.size() == 0)
	{
		std::cout << "Действительных корней уравнение не имеет." << std::endl << std::endl;
	}
	std::cout << "Комплексные корни уравнения:" << std::endl;

	std::cout << "x_" << count_x + 1 << ", x_" << count_x + 2 << " = " << u1 << " ± " << v1 << "i" << std::defaultfloat << std::endl;
	count_x += 2;

	std::cout << std::right;
	std::cout << "x_" << count_x + 1 << ", x_" << count_x + 2 << " = " << u2 << " ± " << v2 << "i" << std::defaultfloat << std::endl;
	std::cout << "Покажем, что полученные модули комплексных корней удовлетворяют границам по грубой оценке:" << std::endl;
	std::cout << "(r_1)^2 = " << r_1_squared << ":\t" << rude_down << " <= " << sqrt(r_1_squared) << " <= " << rude_up << std::endl;
	std::cout << "(r_2)^2 = " << r_2_squared << ":\t" << rude_down << " <= " << sqrt(r_2_squared) << " <= " << rude_up << std::endl;
}
/*---------------------------
 * ОСНОВНАЯ ФУНКЦИЯ ЗАПУСКА |
----------------------------*/
//Метод Лобачевского-Греффе.
void LobachevskyGraeffeAlgorithm(const long double& epsilon)
{
	PrintDash();
	//Заполнение вектора коэффициентов.
	std::vector<std::vector<long double>> cur_row{ base_coefs };
	//Трехмерный ектор всех значений таблицы.
	std::vector<std::vector<std::vector<long double>>> table{ cur_row };
	//Двумерный вектор степеней самих коэффициентов.
	std::vector<std::vector<long long int>> coefs_degrees{};
	coefs_degrees.push_back(std::vector<long long int>{});
	for (unsigned i{}; i < cur_row.size();i++)
		coefs_degrees[0].push_back(0);
	//Двумерный вектор степеней дополнительных значений коэффициентов.
	std::vector<std::vector<long long int>> values_degrees{};
	/*Грубая оценка модулей корней.*/
	std::cout << "Границы модулей корней могут быть определены грубой оценкой. Проиллюстрируем:" << std::endl;
	float A{ -INFINITY }, B{ -INFINITY };
	//Определение А.
	for (long long int i{ 1 }; i < table[0].size(); i++)
		if (abs(table[0][i][0]) > A) A = abs(table[0][i][0]);
	//Определение B.
	for (long long int i{}; i < table[0].size() - 1; i++)
		if (abs(table[0][i][0]) > B) B = abs(table[0][i][0]);
	const long double
		rude_down{ 1.0f / (1 + B / abs(base_coefs[base_coefs.size() - 1][0])) },
		rude_up{ 1.0f + A / abs(base_coefs[0][0]) };
	std::cout << rude_down << " <= |x| <= " << rude_up << std::endl;
	std::cout << "\n\t\t\t\t\tПРОЦЕСС КВАДРИРОВАНИЯ КОРНЕЙ" << std::endl;
	//Процесс квадрирования.
	bool stop{ false };
	while (!stop)
	{
		Add2aa(table.back(), coefs_degrees, values_degrees);
		AddNewCoef(table, coefs_degrees, values_degrees);
		if (Equal(table, coefs_degrees, epsilon))
			stop = true;
	}
	PrintTable(table, coefs_degrees, values_degrees);
	GetSolutions(table, coefs_degrees, rude_up, rude_down);
}