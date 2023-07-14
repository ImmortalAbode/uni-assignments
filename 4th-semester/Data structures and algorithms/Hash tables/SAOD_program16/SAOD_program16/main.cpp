#include <iostream>
#include <string>

#include "myfuncs.h"
#include "HashTable.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	HashTable hash_table{};
	buildNonConflictHashTable(hash_table);
	printHashTable(hash_table);
	findKeyInHashTable(hash_table);
	std::cout << "Завершение программы. . ." << std::endl;
	return 0;
}