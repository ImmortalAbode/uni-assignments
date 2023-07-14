#include <iostream>
#include <string>
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time() и clock()

#include "myarray.h"
#include "myfuncs.h"
#include "Bucket.h"

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
	std::cout << "1  - Создание массива.\n"
		<< "2  - Сортировка массива обменом (методом пузырька).\n"
		<< "3  - Сортировка массива выбором.\n"
		<< "4  - Сортировка массива вставками.\n"
		<< "5  - Сортировка массива методом Шелла.\n"
		<< "6  - Быстрая сортировка массива.\n"
		<< "7  - Пирамидальная сортировка массива (сортировка кучей).\n"
		<< "8  - Простейшая карманная сортировка с использованием второго массива.\n"
		<< "9  - Простейшая карманная сортировка без использования второго массива.\n"
		<< "10 - Обобщенная карманная сортировка с повторяющимися ключами и дополнительными списками.\n"
		<< "11 - Поразрядная сортировка.\n"
		<< "12 - Печать неотсортированного массива.\n"
		<< "13 - Выход из программы.";
	std::cout << std::endl;
}
int getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9"
			|| choice == "10" || choice == "11" || choice == "12" || choice == "13")
			return convertStrToInt(choice);
		else
			std::cout << "Вы должны ввести целое число от 1 до 13. Повторите ввод. " << std::endl;
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

char getUserShellChoice()
{
	while (true)
	{
		std::string ShellChoice{};
		std::getline(std::cin, ShellChoice);
		if (ShellChoice == "1" || ShellChoice == "2")
			return ShellChoice[0];
		else
			std::cout << "Вы должны ввести целое число от 1 до 2. Повторите ввод. " << std::endl;
	}
}
std::string getUserCountSteps(Array mass, const int& max_count_steps)
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите количество шагов сортировки Шелла (количество шагов большее " << max_count_steps << " бессмысленно): ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0 && convertStrToInt(userStr) <= max_count_steps)
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите количество шагов сортировки Шелла (количество шагов большее " << max_count_steps << " бессмысленно): ";
	}
}
int getUserSteps(Array mass, int* mass_steps, const int& mass_steps_size)
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите значение шага сортировки Шелла (шаг больший size/2 и повторяющийся - бессмысленнен): ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0 && convertStrToInt(userStr) <= mass.size / 2 && convertStrToInt(userStr) != 1)
		{
			for (int i{}; i < mass_steps_size - 1; i++)
			{
				if (mass_steps[i] == convertStrToInt(userStr))
				{
					std::cout << "Данный шаг уже добавлен в массив. Повторите ввод: ";
					break;
				}
				else
					return convertStrToInt(userStr);
			}
		}
		else
			std::cout << "Ошибка ввода. Введите значение шага сортировки Шелла (шаг больший size/2 и повторяющийся - бессмысленнен, шаг равный 1 вводить нельзя): ";
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
		mass.array = new int[mass.size]{};
	}
	else
	{
		mass.size = choice;
		mass.array = new int[mass.size]{};
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

void random_shuffle(Array& mass)
{
	for (int i{}; i < mass.size;i++)
		Swap_Counter(mass, i, static_cast<int>(getRandomNumber(i, mass.size - 1)));
}
void RecreateArray(Array& mass, const int& feature)
{
	if (feature == 0)
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
	else if (feature == 1)
	{
		for (int i{}; i < mass.size; i++)
			mass.array[i] = i;
		random_shuffle(mass);
		print_array(mass);
	}
	else
	{
		for (int i{}; i < mass.size; i++)
			mass.array[i] = static_cast<int>(getRandomNumber(0, 1000));
		print_array(mass);
	}
}

//Вспомогательные функции.
void Swap_Counter(Array& mass, const int& left_elem_ind, const int& right_elem_ind)
{
	int temp = mass.array[left_elem_ind];
	mass.array[left_elem_ind] = mass.array[right_elem_ind];
	mass.array[right_elem_ind] = temp;
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
double Bubble_ExchangeSort(Array& mass, int& counter_swap, int& counter_comparison)
{
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
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//double Bubble_ExchangeSort(Array& mass, int& counter_swap, int& counter_comparison)
//{
//	clock_t start_time = clock();
//	for (int i{};i < mass.size - 1;i++)
//		for (int j{}; j < mass.size - i - 1;j++)
//		{
//			if (mass.array[j] > mass.array[j + 1])
//			{
//				Swap_Counter(mass, j, j + 1);
//				counter_swap += 3;
//			}
//			counter_comparison++;
//		}
//	clock_t end_time = clock();
//	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
//}

//Сложность O(n^2). Сортировка выбором.
double SelectionSort(Array& mass, int& counter_swap, int& counter_comparison)
{
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
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Сложность О(n^2). Сортировка вставками.
double InsertionSort(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();
	for (int i{ 1 }; i < mass.size;i++)
	{
		counter_swap++;
		int current_elem{ mass.array[i] };
		int j{ i - 1 };

		while (j >= 0 && mass.array[j] > current_elem)
		{
			counter_comparison++;
			mass.array[j + 1] = mass.array[j];
			counter_swap++;
			j--;
		}
		if (j >= 0) 
			counter_comparison++;

		//counter_comparison++;
		if (mass.array[j + 1] != current_elem)
		{
			counter_swap++;
			mass.array[j + 1] = current_elem;
		}
	}
	clock_t end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Улучшенные методы сортировки.
//Сложность: лучшая O(n*log(n)^2), худшая O(n^2). Сортировка Шелла.
int*& UserWishes(Array mass, int& steps_size)
{
	int counter_swap{}, counter_comparison{};
	std::cout << "Введите количество шагов для сортировки Шелла. Шаг размера 1 будет добавлен автоматически. Ввод: ";
	int max_count_steps{}, value{ mass.size };
	while (value != 1)
	{
		value /= 2;
		max_count_steps += 1;
	}
	std::string UserCountSteps{ getUserCountSteps(mass, max_count_steps) };
	int size = convertStrToInt(UserCountSteps);
	int* steps = new int[size] {};
	steps[size - 1] = 1;
	std::cout << "Шаг " << size << ": 1" << std::endl;
	for (int i{ 1 };i < size;i++)
	{
		std::cout << "Шаг " << size - i << ": ";
		int UserStep{ getUserSteps(mass, steps, size) };
		steps[i - 1] = UserStep;
	}
	if (size > 1)
	{
		std::cout << "Шаги должны выполняться от большего к меньшему, ваши значения были отсортированны." << std::endl;
		QuickSort(steps, 0, size - 1, counter_swap, counter_comparison);
		for (int i{ size }; i > 0;i--)
			std::cout << "Шаг " << size - i + 1 << ": " << steps[i - 1] << std::endl;
	}
	steps_size = size;
	return steps;
}
double UserShellSort(Array& mass, int& counter_swap, int& counter_comparison, int* steps, const int& steps_size)
{
	clock_t start_time = clock();

	for (int steps_index{ steps_size - 1 }; steps_index >= 0;steps_index--)
	{
		int step{ steps[steps_index] };
		for (int subarray_index{ step }; subarray_index < mass.size; subarray_index++)
		{
			counter_swap++;
			int current_elem{ mass.array[subarray_index] };
			int j{ subarray_index - step };

			while (j >= 0 && mass.array[j] > current_elem)
			{
				counter_comparison++;
				mass.array[j + step] = mass.array[j];
				counter_swap++;
				j -= step;
			}
			if (j >= 0) counter_comparison++;

			//counter_comparison++;
			if (mass.array[j + step] != current_elem)
			{
				counter_swap++;
				mass.array[j + step] = current_elem;
			}
		}
	}

	clock_t end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
double ShellSort(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();

	for (int step{ mass.size / 2 }; step > 0;step /= 2)
	{
		for (int subarray_index{ step }; subarray_index < mass.size; subarray_index++)
		{
			counter_swap++;
			int current_elem{ mass.array[subarray_index] };
			int j{ subarray_index - step };

			while (j >= 0 && mass.array[j] > current_elem)
			{
				counter_comparison++;
				mass.array[j + step] = mass.array[j];
				counter_swap++;
				j -= step;
			}
			if (j >= 0) counter_comparison++;

			//counter_comparison++;
			if (mass.array[j + step] != current_elem)
			{
				counter_swap++;
				mass.array[j + step] = current_elem;
			}
		}
	}

	clock_t end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Сложность: лучшая O(n*log(n)), худшая O(n^2). Быстрая сортировка.
void QuickSort(int*& array, int first, int last, int& counter_swap, int& counter_comparison)
{
	if (first < last)
	{
		int middle_element{ array[(first + last) / 2] }; //pivot
		int left_index{ first };
		int right_index{ last };

		while (left_index <= right_index)
		{
			while (array[left_index] < middle_element)
			{
				counter_comparison++;
				left_index++;
			}
			counter_comparison++;

			while (array[right_index] > middle_element)
			{
				counter_comparison++;
				right_index--;
			}
			counter_comparison++;

			if (left_index <= right_index)
			{
				if (array[left_index] != array[right_index])
				{
					//Swap_Counter(mass, left_index, right_index) 
					int temp = array[left_index];
					array[left_index] = array[right_index];
					array[right_index] = temp;
					counter_swap += 3;
				}
				//counter_comparison++;
				left_index++;
				right_index--;
			}
		}
		QuickSort(array, first, right_index, counter_swap, counter_comparison);
		QuickSort(array, left_index, last, counter_swap, counter_comparison);
	}
}
//Сложность O(n*log(n). Пирамидальная сортировка. Сортировка кучей.
void Heapify(Array& mass, const int& current_max_index, const int& current_index, int& counter_swap, int& counter_comparison)
{
	int largest_element_index{ current_index };
	int left_child_index{ 2 * current_index + 1 };
	int right_child_index{ 2 * current_index + 2 };

	counter_comparison++;
	if (left_child_index < current_max_index && mass.array[left_child_index] > mass.array[largest_element_index])
		largest_element_index = left_child_index;

	counter_comparison++;
	if (right_child_index < current_max_index && mass.array[right_child_index] > mass.array[largest_element_index])
		largest_element_index = right_child_index;

	if (largest_element_index != current_index)
	{
		//counter_comparison++;
		if (mass.array[largest_element_index] != mass.array[current_index])
		{
			Swap_Counter(mass, current_index, largest_element_index);
			counter_swap += 3;
		}
		Heapify(mass, current_max_index, largest_element_index, counter_swap, counter_comparison);
	}
}
double HeapSort(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();

	for (int i{ mass.size / 2 - 1 }; i >= 0; --i)
		Heapify(mass, mass.size, i, counter_swap, counter_comparison);

	for (int i{ mass.size - 1 }; i >= 0; --i)
	{
		//counter_comparison++;
		if (mass.array[0] != mass.array[i])
		{
			Swap_Counter(mass, 0, i);
			counter_swap += 3;
		}
		Heapify(mass, i, 0, counter_swap, counter_comparison);
	}

	clock_t end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Специальные методы сортировки.
//Сложность O(n). Простейшая карманная сортировка с использованием второго массива.
double BucketSortWithArray(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();

	int* second_array = new int[mass.size]{};

	for (int i{}; i < mass.size; i++)
	{
		second_array[mass.array[i]] = mass.array[i];
		counter_swap++;
	}

	clock_t end_time = clock();

	delete[] mass.array;
	mass.array = nullptr;
	mass.array = second_array;

	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Сложность O(n). Простейшая карманная сортировка без использования второго массива.
double BucketSortWithoutArray(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();

	for (int i{}; i < mass.size; i++)
	{
		while (mass.array[i] != i)
		{
			int temp{ mass.array[i] };
			mass.array[i] = mass.array[temp];
			mass.array[temp] = temp;
			counter_swap += 3;
		}
	}

	clock_t end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Сложность O(n). Обобщенная карманная сортировка.
void DeleteBuckets(Bucket*& buckets, const int& size)
{
	for (int i{}; i < size;i++)
	{
		if (buckets[i].head_ptr != nullptr)
		{
			while (buckets[i].head_ptr->next != nullptr)
			{
				Node* current{ buckets[i].head_ptr->next };
				buckets[i].head_ptr->next = buckets[i].head_ptr->next->next;
				delete current;
			}
			buckets[i].last_element = buckets[i].head_ptr;
			delete buckets[i].head_ptr;
			buckets[i].last_element = nullptr;
		}
	}
	delete[] buckets;
}
double GenericBucketSort(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();

	Bucket* buckets = new Bucket[1001];
	for (int i{}; i < mass.size;i++)
	{
		Node* new_node = new Node{};
		new_node->data = mass.array[i];
		counter_swap++;
		if (buckets[mass.array[i]].head_ptr == nullptr)
		{
			buckets[mass.array[i]].head_ptr = new Node{};
			buckets[mass.array[i]].head_ptr->next = new_node;
		}
		else
		{
			buckets[mass.array[i]].last_element->next = new_node;
		}
		buckets[mass.array[i]].last_element = new_node;
	}

	clock_t end_time = clock();

	int number{};
	for (int i{}; i < 1001;i++)
		if (buckets[i].head_ptr != nullptr)
		{
			Node* current{ buckets[i].head_ptr };
			while (current->next != nullptr)
			{
				mass.array[number] = current->next->data;
				number++;
				current = current->next;
			}
		}
	DeleteBuckets(buckets, 1001);

	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
//Сложность O(n). Поразрядная сортировка.
double RadixSort(Array& mass, int& counter_swap, int& counter_comparison)
{
	clock_t start_time = clock();

	int max{};
	for (int i{}; i < mass.size;i++)
		if (mass.array[i] > max)
			max = mass.array[i];

	for (int discharge{ 1 }; max / discharge > 0; discharge *= 10)
	{
		Bucket* buckets = new Bucket[10];
		for (int i{};i < mass.size;i++)
		{
			Node* new_node = new Node{};
			new_node->data = mass.array[i];
			counter_swap++;
			if (buckets[(mass.array[i] / discharge) % 10].head_ptr == nullptr)
			{
				buckets[(mass.array[i] / discharge) % 10].head_ptr = new Node{};
				buckets[(mass.array[i] / discharge) % 10].head_ptr->next = new_node;
			}
			else
			{
				buckets[(mass.array[i] / discharge) % 10].last_element->next = new_node;
			}
			buckets[(mass.array[i] / discharge) % 10].last_element = new_node;

			int number{};
			for (int i{}; i < 10;i++)
			{
				if (buckets[i].head_ptr != nullptr)
				{
					Node* current{ buckets[i].head_ptr };
					while (current->next != nullptr)
					{
						mass.array[number] = current->next->data;
						number++;
						current = current->next;
					}
				}
			}
		}
		DeleteBuckets(buckets, 10);
	}

	clock_t end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

void SortingTimePreparation(Array mass, const std::string& type_of_sort)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};

	double time_spent{};
	if (type_of_sort == "bubble")
	{
		std::cout << "Сортировка обменом (методом пузырька) заданного массива: " << std::endl;
		time_spent = Bubble_ExchangeSort(mass, counter_swap, counter_comparison);
	}
	else if (type_of_sort == "selection")
	{
		std::cout << "Сортировка выбором заданного массива: " << std::endl;
		time_spent = SelectionSort(mass, counter_swap, counter_comparison);
	}
	else if (type_of_sort == "insertion")
	{
		std::cout << "Сортировка вставками заданного массива: " << std::endl;
		time_spent = InsertionSort(mass, counter_swap, counter_comparison);
	}
	else if (type_of_sort == "shell")
	{
		std::cout << "Вы хотите использовать стандартную версию сортировки Шелла (1) или задать шаги сами (2)?: ";
		char ShellChoice{ getUserShellChoice() };
		if (ShellChoice == '1')
		{
			std::cout << "Сортировка Шелла для заданного массива: " << std::endl;
			time_spent = ShellSort(mass, counter_swap, counter_comparison);
		}
		else if (ShellChoice == '2')
		{
			int steps_size{};
			int* steps = UserWishes(mass, steps_size);
			time_spent = UserShellSort(mass, counter_swap, counter_comparison, steps, steps_size);
			delete[] steps;
		}
	}
	else if (type_of_sort == "quick")
	{
		std::cout << "Быстрая сортировка массива: " << std::endl;
		clock_t start_time = clock();
		QuickSort(mass.array, 0, mass.size - 1, counter_swap, counter_comparison);
		clock_t end_time = clock();
		time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	}
	else if (type_of_sort == "heap")
	{
		std::cout << "Пирамидальная сортировка (сортировка кучей) заданного массива: " << std::endl;
		time_spent = HeapSort(mass, counter_swap, counter_comparison);
	}
	else if (type_of_sort == "bucket_with_array" || type_of_sort == "bucket_without_array")
	{
		std::cout << "Простейшая карманная сортировка не может быть выполнена для массива значений, которые <0 или превышают (size-1).\n" <<
			"Будет создан временный массив того же размера для данной сортировки." << std::endl;
		RecreateArray(mass, 1);

		if (type_of_sort == "bucket_with_array")
		{
			std::cout << "Простейшая карманная сортировка с использованием второго массива для заданного массива: " << std::endl;
			BucketSortWithArray(mass, counter_swap, counter_comparison);
		}
		else
		{
			std::cout << "Простейшая карманная сортировка без использования второго массива для заданного массива: " << std::endl;
			BucketSortWithoutArray(mass, counter_swap, counter_comparison);
		}
	}
	else if (type_of_sort == "generic_bucket")
	{
		std::cout << "Обобщенная карманная сортировка не может быть выполнена для массива значений, которые <0 или превышают (size-1).\n" <<
			"Будет создан временный массив того же размера для данной сортировки." << std::endl;
		RecreateArray(mass, 2);

		std::cout << "Обобщенная карманная сортировка заданного массива: " << std::endl;
		GenericBucketSort(mass, counter_swap, counter_comparison);
	}
	else if (type_of_sort == "radix")
	{
		std::cout << "Поразрядная сортировка будет выполнена для массива положительных значений.\n" <<
			"Будет создан временный массив того же размера для данной сортировки." << std::endl;
		RecreateArray(mass, 2);

		std::cout << "Поразрядная сортировка заданного массива: " << std::endl;
		RadixSort(mass, counter_swap, counter_comparison);
	}

	print_array(mass);

	std::cout << "Время выполнения сортировки: " << time_spent << " сек.\n";
	std::cout << "Было выполнено операций сравнения: " << counter_comparison << ".\nБыло выполнено операций пересылок: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}