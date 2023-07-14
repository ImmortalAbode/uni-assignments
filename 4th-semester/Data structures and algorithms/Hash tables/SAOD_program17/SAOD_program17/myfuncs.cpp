#include <iostream>
#include <string>

#include "constants.h"
#include "HashTable.h"
#include "myfuncs.h"

void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать с хеш-таблицей?" << std::endl;
	std::cout << "1 - Добавить ключ в хеш-таблицу.\n"
		<< "2 - Поиск заданного ключа в таблице.\n"
		<< "3 - Вывод текущего состояния хеш-таблицы.\n"
		<< "4 - Выход из программы.";
	std::cout << std::endl;
}
int getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4")
		{
			std::cout << std::endl;
			return convertStrToInt(choice);
		}
		else
			std::cout << "Вы должны ввести целое число от 1 до 4. Повторите ввод. " << std::endl;
	}
}

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

int hashFunc(std::string const& new_key)
{
	int index{};
	for (int i{}; i < new_key.length(); i++)
		index += static_cast<int>(new_key[i]);
	return index % m;
}
void addNewKeyInHashTable(HashTable& hash_table, int& common_add_count_of_compares)
{
	if (hash_table.count_key < max_count_keys)
	{
		int count_of_compares{};
		std::cout << "Введите новый ключ для хеш-таблицы:" << std::endl;
		std::string new_key{};
		std::getline(std::cin, new_key);
		int index{ hashFunc(new_key) };
		std::cout << "Попытка добавить в индекc " << index << "." << std::endl;
		count_of_compares++;
		if (hash_table.array[index] == "")
		{
			hash_table.array[index] = new_key;
			hash_table.count_key++;
			common_add_count_of_compares += count_of_compares;
			std::cout << "Ключ был добавлен по индексу " << index << "." << std::endl;
		}
		else
		{
			if (hash_table.array[index] == new_key)
				std::cout << "Ключи совпали. Добавления не происходит." << std::endl;
			else
			{
				while (hash_table.array[index] != "")
				{
					count_of_compares++;
					index = (index + 1) % m;
					if (hash_table.array[index] == new_key)
					{
						std::cout << "Ключи совпали. Добавления не происходит." << std::endl;
						std::cout << "Было произведено " << count_of_compares << " сравнение (-я, -ий)." << std::endl;
						return;
					}
				}
				hash_table.array[index] = new_key;
				hash_table.count_key++;
				common_add_count_of_compares += count_of_compares;
				std::cout << "Ключ был добавлен по индексу " << index << "." << std::endl;
			}
		}
		std::cout << "Было произведено " << count_of_compares << " сравнение (-я, -ий)." << std::endl;
	}
	else
		std::cout << "Количество добавленных ключей максимально. Добавить новый ключ нельзя." << std::endl;
}
void findKeyInHashTable(const HashTable& hash_table)
{
	if (hash_table.count_key != 0)
	{
		int count_of_compares{};
		printHashTable(hash_table);
		std::cout << "Какой ключ вы хотите найти? " << std::endl;
		std::string finding_key{};
		std::getline(std::cin, finding_key);
		int index{ hashFunc(finding_key) };
		std::cout << "Попытка просмотреть индекc " << index << "." << std::endl;
		count_of_compares++;
		if (hash_table.array[index] == "")
			std::cout << "Данного ключа нет в хеш-таблице." << std::endl;
		else
		{
			if (hash_table.array[index] == finding_key)
				std::cout << "Данный ключ найден по индексу " << index << "." << std::endl;
			else
			{
				while (hash_table.array[index] != "" && hash_table.array[index] != finding_key)
				{
					count_of_compares++;
					index = (index + 1) % m;
				}
				if (hash_table.array[index] == "") std::cout << "Данного ключа нет в хеш-таблице." << std::endl;
				else std::cout << "Данный ключ найден по индексу " << index << "." << std::endl;
			}
		}
		std::cout << "Было произведено " << count_of_compares << " сравнениe (-я, -ий)." << std::endl;
	}
	else
		std::cout << "Хеш-таблица пустая." << std::endl;
}
void printHashTable(const HashTable& hash_table)
{
	std::cout << "\t Ваша хеш-таблица:" << std::endl << std::endl;
	for (int i{}; i < m; i++)
		std::cout << i << ":" << hash_table.array[i] << std::endl;
}