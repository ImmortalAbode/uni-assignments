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
bool checkStrIsShort(std::string userStr)
{
	for (int i{}; i < userStr.length();i++)
	{
		if (userStr.length() > 15)
			return false;
		if (userStr[i] == ' ' || userStr[i] < 'A' || (userStr[i] > 'Z' && userStr[i] < 'a') || userStr[i] > 'z')
			return false;
	}
	return true;
}
std::string getUserInput()
{
	std::cout << "Строка содержит только символы от 'a' до 'z' и от 'A' до 'Z'." << std::endl;
	std::cout << "Введите информационную часть элемента или '-1', чтобы вернуться в меню: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите короткую строку или '-1': ";
		else if (userStr == "-1" || checkStrIsShort(userStr))
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите короткую строку или '-1': ";
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
			if (list.count % 20 == 0)
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
			if (userStr != "-1")
			{
				int count{};
				for (int i{}; i < list.count; i++)
					if (list.list[i] == userStr)
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
		if (userStr != "-1")
		{
			list.list[list.count] = userStr;
			list.count++;
			std::cout << "Элемент " << userStr << " был успешно добавлен в список." << std::endl;
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
	}
	else
	{
		std::string userStr{ getUserInput() };
		if (userStr != "-1")
		{
			bool maxStr{ true };
			for (int i{}; i < list.count;i++)
			{
				if (list.list[i] < userStr)
				{
					for (int j{ list.count };j > i;j--)
						list.list[j] = list.list[j - 1];
					list.list[i] = userStr;
					list.count++;
					maxStr = false;
					break;
				}
			}
			if (maxStr)
			{
				list.list[list.count] = userStr;
				list.count++;
			}
			std::cout << "Новый элемент " << userStr << " был успешно добавлен в список." << std::endl;
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
			if (userStr != "-1")
			{
				bool isData{ false };
				for (int i{}; i < list.count;i++)
				{
					if (list.list[i] == userStr)
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
						std::cout << "Элемент " << userStr << " был успешно удален из списка." << std::endl;
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