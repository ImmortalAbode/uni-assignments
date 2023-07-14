#ifndef MYFUNCS_H
#define MYFUNCS_H

#include <string>
#include "HashTable.h"

//������� ��� ������ �������� � ���-��������.
void MenuOfProgram();
int getChoice();

//��������������� �������.
int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);

//������� �������� � ���-��������.
int hashFunc(std::string const& new_key);
void addNewKeyInHashTable(HashTable& hash_table, int& common_add_count_of_compares);
void findKeyInHashTable(const HashTable& hash_table);
void printHashTable(const HashTable& hash_table);

#endif /*MYFUNCS_H*/