#include <iostream>
#include <string>

#include "constants.h"
#include "HashTable.h"
#include "myfuncs.h"

void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� � ���-��������?" << std::endl;
	std::cout << "1 - �������� ���� � ���-�������.\n"
		<< "2 - ����� ��������� ����� � �������.\n"
		<< "3 - ����� �������� ��������� ���-�������.\n"
		<< "4 - ����� �� ���������.";
	std::cout << std::endl;
}
int getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4")
		{
			std::cout << std::endl;
			return convertStrToInt(choice);
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 4. ��������� ����. " << std::endl;
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
		std::cout << "������� ����� ���� ��� ���-�������:" << std::endl;
		std::string new_key{};
		std::getline(std::cin, new_key);
		int index{ hashFunc(new_key) };
		std::cout << "������� �������� � �����c " << index << "." << std::endl;
		count_of_compares++;
		if (hash_table.array[index] == "")
		{
			hash_table.array[index] = new_key;
			hash_table.count_key++;
			common_add_count_of_compares += count_of_compares;
			std::cout << "���� ��� �������� �� ������� " << index << "." << std::endl;
		}
		else
		{
			if (hash_table.array[index] == new_key)
				std::cout << "����� �������. ���������� �� ����������." << std::endl;
			else
			{
				while (hash_table.array[index] != "")
				{
					count_of_compares++;
					index = (index + 1) % m;
					if (hash_table.array[index] == new_key)
					{
						std::cout << "����� �������. ���������� �� ����������." << std::endl;
						std::cout << "���� ����������� " << count_of_compares << " ��������� (-�, -��)." << std::endl;
						return;
					}
				}
				hash_table.array[index] = new_key;
				hash_table.count_key++;
				common_add_count_of_compares += count_of_compares;
				std::cout << "���� ��� �������� �� ������� " << index << "." << std::endl;
			}
		}
		std::cout << "���� ����������� " << count_of_compares << " ��������� (-�, -��)." << std::endl;
	}
	else
		std::cout << "���������� ����������� ������ �����������. �������� ����� ���� ������." << std::endl;
}
void findKeyInHashTable(const HashTable& hash_table)
{
	if (hash_table.count_key != 0)
	{
		int count_of_compares{};
		printHashTable(hash_table);
		std::cout << "����� ���� �� ������ �����? " << std::endl;
		std::string finding_key{};
		std::getline(std::cin, finding_key);
		int index{ hashFunc(finding_key) };
		std::cout << "������� ����������� �����c " << index << "." << std::endl;
		count_of_compares++;
		if (hash_table.array[index] == "")
			std::cout << "������� ����� ��� � ���-�������." << std::endl;
		else
		{
			if (hash_table.array[index] == finding_key)
				std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
			else
			{
				while (hash_table.array[index] != "" && hash_table.array[index] != finding_key)
				{
					count_of_compares++;
					index = (index + 1) % m;
				}
				if (hash_table.array[index] == "") std::cout << "������� ����� ��� � ���-�������." << std::endl;
				else std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
			}
		}
		std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
	}
	else
		std::cout << "���-������� ������." << std::endl;
}
void printHashTable(const HashTable& hash_table)
{
	std::cout << "\t ���� ���-�������:" << std::endl << std::endl;
	for (int i{}; i < m; i++)
		std::cout << i << ":" << hash_table.array[i] << std::endl;
}