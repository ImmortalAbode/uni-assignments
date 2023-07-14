#include <iostream>
#include <string>

#include "myfuncs.h"
#include "MyList.h"

//Функции для выбора операции со списком.
void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать со списком?" << std::endl;
	std::cout << "1 - Проход по списку с выводом на экран информационных частей элементов.\n"
		<< "2 - Поиск элемента с заданной информационной частью.\n"
		<< "3 - Добавление нового элемента.\n"
		<< "4 - Удаление заданного элемента.\n"
		<< "5 - Выход из программы.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
			std::cout << "Вы должны ввести целое число от 1 до 5. Повторите ввод. " << std::endl;
	}
}

//Вспомогательные проверяющие функции.
bool isEmpty(List list)
{
	return list.count == 0 ? true : false;
}
bool isFull(List list)
{
	return list.count == size ? true : false;
}

//Функции получения и проверки пользовательского ввода.
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
	std::cout << "Введите информационную часть элемента или нажмите 'q', чтобы вернуться в меню: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите целое число или 'q': ";
		else if (userStr == "q" || checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите целое число или 'q': ";
	}
}

//Функции для работы со списком.
void printDataList(List list)
{
	if (!isEmpty(list))
	{
		std::cout << "Ваш список: " << std::endl;
		for (int i{}; i < list.count; i++)
		{
			if (i % 20 == 0)
				std::cout << "\n";
			std::cout << list.list[i] << " ";
		}
		std::cout << std::endl;
	}
	else
		std::cout << "Ваш список пуст." << std::endl;
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
				int count{};
				for (int i{}; i < list.count; i++)
					if (list.list[i] == number)
					{
						count++;
						std::cout << i << "-ой/-ий/-ый элемент списка: " << list.list[i] << std::endl;
					}
				if (count != 0)
					std::cout << "Всего было найдено " << count << " элемент(-a/-ов)." << std::endl;
				else
					std::cout << "В списке нет элементов с данной информационной частью." << std::endl;
				break;
			}
			else
			{
				std::cout << "Возвращение в меню. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "Ваш список пуст, сначала добавьте элементы." << std::endl;
}
void addNewElement(List& list)
{
	if (isFull(list))
	{
		std::cout << "Ваш список полон, добавление нового элемента невозможно." << std::endl;
	}
	else if (isEmpty(list))
	{
		std::string userStr{ getUserInput() };
		if (userStr != "q")
		{
			int number{ convertStrToInt(userStr) };
			list.list[list.count] = number;
			list.count++;
			std::cout << "Элемент " << number << " был успешно добавлен в список." << std::endl;
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
	}
	else
	{
		std::string userStr{ getUserInput() };
		if (userStr != "q")
		{
			int number{ convertStrToInt(userStr) };
			bool maxNumber{ true };
			for (int i{}; i < list.count;i++)
			{
				if (list.list[i] > number)
				{
					for (int j{ list.count };j > i;j--)
						list.list[j] = list.list[j - 1];
					list.list[i] = number;
					list.count++;
					maxNumber = false;
					break;
				}
			}
			if (maxNumber)
			{
				list.list[list.count] = number;
				list.count++;
			}
			std::cout << "Новый элемент " << number << " был успешно добавлен в список." << std::endl;
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
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
				for (int i{}; i < list.count;i++)
				{
					if (list.list[i] == number)
					{
						isData = true;
						if (i == list.count - 1)
							list.count--;
						else
						{
							for (int j{ i };j < list.count;j++)
								list.list[j] = list.list[j + 1];
							list.count--;
						}
						std::cout << "Элемент " << number << " был успешно удален из списка." << std::endl;
						break;
					}
				}
				if (isData)
					break;
				std::cout << "Указанного элемента нет в списке. Повторите ввод. " << std::endl;
			}
			else
			{
				std::cout << "Возвращение в меню. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "Ваш список пуст, сначала добавьте элементы." << std::endl;
}