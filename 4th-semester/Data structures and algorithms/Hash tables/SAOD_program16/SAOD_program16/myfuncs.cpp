#include <iostream>
#include <string>

#include "myfuncs.h"
#include "HashTable.h"
#include "constants.h"

int hashFunc(std::string const& new_key)
{
	int index{};
	for (int i{}; i < new_key.length(); i++)
		index += static_cast<int>(new_key[i]);
	return index % max_size;
}
void buildNonConflictHashTable(HashTable& hash_table)
{
	for (int i{}; i < max_size; i++)
	{
		int index{ hashFunc(keys[i]) };
		hash_table.array[index] = keys[i];
	}
}
void printHashTable(const HashTable& hash_table)
{
	std::cout << std::string(80, '-') << std::endl;
	std::cout << "Построенная бесконфликтная хеш-таблица:" << std::endl;
	for (int i{}; i < 10; i++)
		std::cout << i << ": " << hash_table.array[i] << std::endl;
}
void findKeyInHashTable(const HashTable& hash_table)
{
	std::cout << std::string(80, '-') << std::endl;
	while (true)
	{
		std::cout << "Введите значение ключа, который хотите найти, или -1 для завершения программы: " << std::endl;
		std::string user_key{};
		std::getline(std::cin, user_key);
		int index{ hashFunc(user_key) };
		if (user_key == "-1")
		{
			std::cout << std::string(80, '-') << std::endl;
			break;
		}
		else if (hash_table.array[index] == user_key)
			std::cout << "Ключ " << user_key << " имеет индекс " << index << "." << std::endl;
		else
			std::cout << "Данного ключа нет в хеш-таблице." << std::endl;
		std::cout << std::string(80, '-') << std::endl;
	}
}