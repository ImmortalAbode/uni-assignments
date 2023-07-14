#include <iostream>
#include <string>

#include "HashTable.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");

	HashTable hash_table{};
	int common_add_count_of_compares{};

	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case 1:
			addNewKeyInHashTable(hash_table, common_add_count_of_compares);
			break;
		case 2:
			findKeyInHashTable(hash_table);
			break;
		case 3:
			printHashTable(hash_table);
			break;
		case 4:
			delKeyFromHashTable(hash_table);
			break;
		case 5:
			cycle = false;
			delHashTable(hash_table);
			break;
		}
		if (hash_table.count_key == max_count_keys)
		{
			std::cout << std::endl;
			std::cout << "Среднее количество сравнений для размещения и поиска ключей: " << (float)common_add_count_of_compares / (float)max_count_keys << std::endl;
		}
		std::cout << std::string(80, '-') << std::endl;
	}
}