#include <iostream>
#include <string>
#include <cstdlib> //��� ������� rand() � srand()
#include <ctime> //��� ������� time() � clock()

#include "myarray.h"
#include "myfuncs.h"

//����.
float getRandomNumber(float min, float max) //��������� ���������� ����� ����� ��������� min � max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//������� ��� ������ �������� � ��������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� � ��������?" << std::endl;
	std::cout << "1 - �������� �������.\n"
		<< "2 - ���������� ������� ������� (������� ��������).\n"
		<< "3 - ���������� ������� �������.\n"
		<< "4 - ���������� ������� ���������.\n"
		<< "5 - ������ ������������������ �������.\n"
		<< "6 - ����� �� ���������.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice =="6")
			return choice[0];
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 6. ��������� ����. " << std::endl;
	}
}

//������� ��������� � �������� ����������������� �����.
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
			std::cout << "������ �����. ������� ����������� ����� �� 10000: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0 && convertStrToInt(userStr) <= 10000)
			return userStr;
		else
			std::cout << "������ �����. ������� ����������� ����� �� 10000: ";
	}
}
std::string getUserChoice()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����������� ����� �� 10000 ��� 'q', ����� �����: ";
		else if (checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0 && convertStrToInt(userStr) <= 10000 || userStr == "q")
			return userStr;
		else
			std::cout << "������ �����. ������� ����������� ����� �� 10000 ��� 'q', ����� �����: ";
	}
}

//�������� ������� � ��������.
void CreateArray(Array& mass, const int& choice)
{
	if (choice == -1)
	{
		std::cout << "������ ������ ������� �� ������ ������� (�� 10000)?" << std::endl;
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
	std::cout << "������ ������� " << mass.size << " ��� ������� ������." << std::endl << std::endl;
	print_array(mass);
}
void print_array(Array& mass)
{
	std::cout << "��� ������:\n";
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

//��������������� �������.
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

//������� ���������� ��������� �������.
//��������� O(n^2). ���������� �������(������� ��������).
void Bubble_ExchangeSort(Array mass)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};
	std::cout << "���������� ������� (������� ��������) ��������� �������:" << std::endl;

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
	std::cout << "����� ���������� ����������: " << time_spent << " ���.\n";
	std::cout << "���� ��������� �������� ���������: " << counter_comparison << ".\n���� ��������� �������� ���������: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}
//��������� O(n^2). ���������� �������.
void SelectionSort(Array mass)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};
	std::cout << "���������� ������� ��������� �������: " << std::endl;

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
	std::cout << "����� ���������� ����������: " << time_spent << " ���.\n";
	std::cout << "���� ��������� �������� ���������: " << counter_comparison << ".\n���� ��������� �������� ���������: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}
//��������� �(n^2). ���������� ���������.
void InsertionSort(Array mass)
{
	int* copy_array{ CopyArray(mass) };
	mass.array = copy_array;

	int counter_swap{};
	int counter_comparison{};
	std::cout << "���������� ��������� ��������� �������:" << std::endl;

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
	std::cout << "����� ���������� ����������: " << time_spent << " ���.\n";
	std::cout << "���� ��������� �������� ���������: " << counter_comparison << ".\n���� ��������� �������� ���������: " << counter_swap << "." << std::endl;
	delete[] mass.array;
}