#include <iostream>
#include <string>

#include "myfuncs.h"
#include "MyList.h"

//������� ��� ������ �������� �� �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� �� �������?" << std::endl;
	std::cout << "1 - ������ �� ������ � ������� �� ����� �������������� ������ ���������.\n"
		<< "2 - ����� �������� � �������� �������������� ������.\n"
		<< "3 - ���������� ������ �������� �� ���������.\n"
		<< "4 - ���������� ������ �������� ����� ���������.\n"
		<< "5 - �������� ��������� ��������.\n"
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
		{
			return choice[0];
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 6. ��������� ����. " << std::endl;
	}
}

//��������������� ����������� �������.
bool isEmpty(List list)
{
	int ptr_index{ list.index[0] };
	return ptr_index == 0 ? true : false;
}
bool isFull(List list)
{
	for (int i{ 1 }; i < size;i++)
	{
		if (list.index[i] == -1)
			return false;
	}
	return true;
}
int getNextFreeIndex(List list)
{
	for (int i{ 1 }; i < size;i++)
		if (list.index[i] == -1)
			return i;
	return -1;
}
//������� ��������� � �������� ����������������� �����.
int convertStrToInt(std::string const& convertStr)
{
	int number{};
	bool negative(false);
	for (int i{}; i < convertStr.length();i++)
	{
		if (i == 0 && convertStr[0] == '-')
		{
			negative = true;
			continue;
		}
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i);
	}
	return negative == true ? number * (-1) : number;
}
bool checkStrIsNumeric(std::string const& userStr)
{
	for (int i{}; i < userStr.length();i++)
	{
		if ((i == 0) && (userStr[i] == '-'))
			continue;
		if (userStr[i] < '0' || userStr[i] > '9')
			return false;
	}
	return true;
}
std::string getUserInput()
{
	std::cout << "������� �������������� ����� �������� ��� ������� 'q', ����� ��������� � ����: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����� ����� ��� 'q': ";
		else if (userStr == "q" || checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "������ �����. ������� ����� ����� ��� 'q': ";
	}
}
std::string getUserInput_2()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� ����� �����: ";
		else if (checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "������ �����. ������� ����� �����: ";
	}
}

//������� ��� ������ �� �������.
void printDataList(List list)
{
	if (!isEmpty(list))
	{
		std::cout << "��� ������: " << std::endl;
		int ptr_index{ list.index[0] };
		int count{};
		while (ptr_index != 0)
		{
			count++;
			if (count % 20 == 0)
				std::cout << "\n";
			std::cout << list.data[ptr_index] << " ";
			ptr_index = list.index[ptr_index];
		}
		std::cout << std::endl;
	}
	else
		std::cout << "��� ������ ����." << std::endl;
}
void searchDataList(List list)
{
	if (!isEmpty(list))
	{
		while (true)
		{
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				int number{ convertStrToInt(userStr) };
				int count{}, ptr_index{ list.index[0] };
				while (ptr_index != 0)
				{
					if (list.data[ptr_index] == number)
					{
						count++;
						std::cout << ptr_index << "-��/-��/-�� ������� ������: " << list.data[ptr_index] << std::endl;
					}
					ptr_index = list.index[ptr_index];
				}
				if (count != 0)
					std::cout << "����� ���� ������� " << count << " �������(-a/-��)." << std::endl;
				else
					std::cout << "� ������ ��� ��������� � ������ �������������� ������." << std::endl;
				break;
			}
			else
			{
				std::cout << "����������� � ����. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "��� ������ ����, ������� �������� ��������." << std::endl;
}
void addNewElement(List& list, const int& choice)
{
	if (isFull(list))
	{
		std::cout << "��� ������ �����, ���������� ������ �������� ����������." << std::endl;
	}
	else if (isEmpty(list) && choice == 1)
		std::cout << "������ �������� ������� �� ���������, ����� ������ ������!" << std::endl;
	else if (isEmpty(list) && choice == 2)
	{
		std::cout << "�������� ������ ������� � ������." << std::endl;
		std::string userStr{ getUserInput() };
		if (userStr != "q")
		{
			int number{ convertStrToInt(userStr) };
			int ptr_index{ 1 };
			list.index[0] = ptr_index;
			list.data[ptr_index] = number; list.index[ptr_index] = 0;
			std::cout << "������ ������� " << number << " ��� ������� �������� � ������." << std::endl;
		}
		else
			std::cout << "����������� � ����." << std::endl;
	}
	else
	{
		std::string userStr{ getUserInput() };
		if (userStr != "q")
		{
			int number{ convertStrToInt(userStr) };
			while (true)
			{
				printDataList(list);
				if (choice == 1) std::cout << "������� �������� ��������, �� �������� ������ ����������� ����������: ";
				if (choice == 2) std::cout << "������� �������� ��������, ����� �������� ������ ����������� ����������: ";
				std::string userStr_2{ getUserInput_2() };
				int elem{ convertStrToInt(userStr_2) };
				bool flag{ false };

				int ptr_next_index{ getNextFreeIndex(list) };
				int ptr_prev_index{};
				int ptr_index{ list.index[ptr_prev_index] };

				while (ptr_index != 0)
				{
					if (list.data[ptr_index] == elem)
					{
						flag = true;
						break;
					}
					ptr_prev_index = ptr_index;
					ptr_index = list.index[ptr_index];
				}
				if (flag)
				{
					if (choice == 1)
					{
						list.index[ptr_prev_index] = ptr_next_index;
						list.index[ptr_next_index] = ptr_index;
						list.data[ptr_next_index] = number;
						std::cout << "����� ������� " << number << " ��� ������� �������� � ������ �� �������� " << elem << "." << std::endl;
					}
					if (choice == 2)
					{
						ptr_prev_index = list.index[ptr_index];
						list.index[ptr_index] = ptr_next_index;
						list.data[ptr_next_index] = number;
						list.index[ptr_index] != 0 ? list.index[ptr_next_index] = ptr_prev_index : list.index[ptr_next_index] = 0;
						std::cout << "����� ������� " << number << " ��� ������� �������� � ������ ����� �������� " << elem << "." << std::endl;
					}
					break;
				}
				else
					std::cout << "��������� ���� �������� ��� � ������! ��������� ����. " << std::endl;
			}
		}
		else
			std::cout << "����������� � ����." << std::endl;
	}
}
void removeElement(List& list)
{
	if (!isEmpty(list))
	{
		printDataList(list);
		while (true)
		{
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				int number{ convertStrToInt(userStr) };
				bool isData{ false };
				int ptr_prev_index{};
				int ptr_index{ list.index[ptr_prev_index] };
				while (ptr_index != 0)
				{
					if (list.data[ptr_index] == number)
					{
						isData = true;
						if (list.index[ptr_index] == 0)
						{
							list.index[ptr_prev_index] = 0;
							list.index[ptr_index] = -1;
						}
						else
						{
							list.index[ptr_prev_index] = list.index[ptr_index];
							list.index[ptr_index] = -1;
						}
						std::cout << "������� " << number << " ��� ������� ������ �� ������." << std::endl;
						break;
					}
					ptr_prev_index = ptr_index;
					ptr_index = list.index[ptr_index];
				}
				if (isData)
					break;
				std::cout << "���������� �������� ��� � ������. ��������� ����. " << std::endl;
			}
			else
			{
				std::cout << "����������� � ����. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "��� ������ ����, ������� �������� ��������." << std::endl;
} 