#include <iostream>
#include <string>
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time() и clock()

#include "myarray.h"
#include "myfuncs.h"

//ГПСЧ.
float getRandomNumber(float min, float max) //Генерация случайного числа между заданными min и max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//Функции для выбора операции с массивом.
void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать с массивом?" << std::endl;
	std::cout << "1 - Создание массива.\n"
		<< "2 - Сортировка массива обменом (методом пузырька).\n"
		<< "3 - Сортировка массива выбором.\n"
		<< "4 - Сортировка массива вставками.\n"
		<< "5 - Печать неотсортированного массива.\n"
		<< "6 - Выход из программы.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice =="6")
			return choice[0];
		else
			std::cout << "Вы должны ввести целое число от 1 до 6. Повторите ввод. " << std::endl;
	}
}

//Функции получения и проверки пользовательского ввода.
int convertStrToInt(std::string const& convertStr)
{
	int number{};
	for (int i{}; i < convertStr.length();i++)
	{
		number += static_cast<int>((convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i));
	}
	return number;
}
bool checkStrIsNumeric(std::string const& userStr)
{
	for (int i{}; i < userStr.length();i++)
		if (userStr[i] < '0' || userStr[i] > '9')
			return false;
	return true;
}
std::string getUserInput()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите натуральное число до 10000: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0 && convertStrToInt(userStr) <= 10000)
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите натуральное число до 10000: ";
	}
}
std::string getUserChoice()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите натуральное число до 10000 или 'q', чтобы выйти: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0 && convertStrToInt(userStr) <= 10000 || userStr == "q")
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите натуральное число до 10000 или 'q', чтобы выйти: ";
	}
}

//Основные функции с массивом.
void CreateArray(Array& mass, const int& choice)
{
	if (choice == -1)
	{
		std::cout << "Массив какого размера вы хотите создать (до 10000)?" << std::endl;
		std::string UserStr{ getUserInput() };
		const int size{ convertStrToInt(UserStr) };
		mass.size = size;
		mass.array = new int[mass.size] {};
	}
	else
	{
		mass.size = choice;
		mass.array = new int[mass.size] {};
	}
	for (int i{}; i < mass.size;i++)
		mass.array[i] = static_cast<int>(getRandomNumber(-1000, 1000));
	std::cout << "Массив размера " << mass.size << " был успешно создан." << std::endl << std::endl;
	print_array(mass);
}
void print_array(Array& mass)
{
	std::cout << "Ваш массив:\n";
	for (unsigned int i{}; i < mass.size;i++)
		std::cout << mass.array[i] << (((i + 1) % 10 == 0) ? "\n" : "\t");
	std::cout << std::endl;
}
void RecreateArray(Array& mass)
{
	std::string UserStr{ getUserChoice() };
	if (UserStr == "q")
		return;
	else
	{
		delete[] mass.array;
		mass.size = 0;
		CreateArray(mass, convertStrToInt(UserStr));
	}
}

//Вспомогательные функции.
void Swap_Counter(Array& mass, const int& left_elem, const int& right_elem)
{
	int temp = mass.array[left_elem];
	mass.array[left_elem] = mass.array[right_elem];
	mass.array[right_elem] = temp;
}
int*& CopyArray(const Array& mass)
{
	int* copy_array = new int[mass.size]{};
	for (int i{}; i < mass.size;i++)
		copy_array[i] = mass.array[i];
	return copy_array;
}

//Функции сортировки заданного массива.
//Сложность O(n^2). Сортировка обменом(методом пузырька).
void Bubble_ExchangeSort(Array mass)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};
	std::cout << "Сортировка обменом (методом пузырька) заданного массива:" << std::endl;

	double time_spent{};
	clock_t start_time = clock();
	for (int i{};i < mass.size - 1;i++)
		for (int j{ i + 1 }; j < mass.size;j++)
		{
			if (mass.array[i] > mass.array[j])
			{
				Swap_Counter(mass, i, j);
				counter_swap += 3;
			}
			counter_comparison++;
		}
	clock_t end_time = clock();

	print_array(mass);
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Время выполнения сортировки: " << time_spent << " сек.\n";
	std::cout << "Было выполнено операций сравнения: " << counter_comparison << ".\nБыло выполнено операций пересылок: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}
//Сложность O(n^2). Сортировка выбором.
void SelectionSort(Array mass)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};
	std::cout << "Сортировка выбором заданного массива: " << std::endl;

	double time_spent{};
	clock_t start_time = clock();
	int min_elem{};
	for (int i{}; i < mass.size - 1;i++)
	{
		min_elem = i;
		for (int j{ i + 1 };j < mass.size;j++)
		{
			if (mass.array[j] < mass.array[min_elem])
				min_elem = j;
			counter_comparison++;
		}
		if (mass.array[min_elem] != mass.array[i])
		{
			Swap_Counter(mass, i, min_elem);
			counter_swap += 3;
		}
		//counter_comparison++;
	}
	clock_t end_time = clock();

	print_array(mass);
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Время выполнения сортировки: " << time_spent << " сек.\n";
	std::cout << "Было выполнено операций сравнения: " << counter_comparison << ".\nБыло выполнено операций пересылок: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}
//Сложность О(n^2). Сортировка вставками.
void InsertionSort(Array mass)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};
	std::cout << "Сортировка вставками заданного массива:" << std::endl;

	double time_spent{};
	clock_t start_time = clock();
	for (int i{ 1 }; i < mass.size;i++)
	{
		counter_swap++;
		int current_elem{ mass.array[i]};
		int j{ i - 1 };

		while (j >= 0 && mass.array[j] > current_elem)
		{
			counter_comparison++;
			mass.array[j + 1] = mass.array[j];
			counter_swap++;
			j--;
		}
		if (j >=0) 
			counter_comparison++;

		//counter_comparison++;
		if (mass.array[j + 1] != current_elem)
		{
			counter_swap++;
			mass.array[j + 1] = current_elem;
		}
	}
	clock_t end_time = clock();

	print_array(mass);
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Время выполнения сортировки: " << time_spent << " сек.\n";
	std::cout << "Было выполнено операций сравнения: " << counter_comparison << ".\nБыло выполнено операций пересылок: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}