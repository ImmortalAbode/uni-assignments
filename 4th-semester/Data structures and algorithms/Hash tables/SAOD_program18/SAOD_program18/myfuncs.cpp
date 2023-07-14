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
		<< "4 - ������� �������� ���� � ���-�������.\n"
		<< "5 - ����� �� ���������.";
	std::cout << std::endl;
}
int getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			std::cout << std::endl;
			return convertStrToInt(choice);
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 5. ��������� ����. " << std::endl;
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
	//if (hash_table.count_key < max_count_keys)
	//{
		int count_of_compares{};
		std::cout << "������� ����� ���� ��� ���-�������:" << std::endl;
		std::string new_key{};
		std::getline(std::cin, new_key);
		int index{ hashFunc(new_key) };
		std::cout << "������� �������� � �����c " << index << "." << std::endl;
		if (hash_table.array[index].key == "")
		{
			count_of_compares++;
			hash_table.array[index].key = new_key;
			hash_table.count_key++;
			common_add_count_of_compares += count_of_compares;
			std::cout << "���� ��� �������� �� ������� " << index << "." << std::endl;
		}
		else
		{
			if (hash_table.array[index].key == new_key)
			{
				count_of_compares++;
				std::cout << "����� �������. ���������� �� ����������." << std::endl;
			}
			else
			{
				if (hash_table.array[index].first == nullptr)
				{
					count_of_compares++;
					hash_table.array[index].first = new Node{};
					hash_table.array[index].last = hash_table.array[index].first;
					hash_table.array[index].last->key = new_key;
				}
				else
				{
					count_of_compares++;
					Node* cur_ptr{ hash_table.array[index].first };
					while (cur_ptr->next != nullptr)
					{
						count_of_compares++;
						if (cur_ptr->key == new_key)
						{
							std::cout << "����� �������. ���������� �� ����������." << std::endl;
							std::cout << "���� ����������� " << count_of_compares << " ��������� (-�, -��)." << std::endl;
							return;
						}
						cur_ptr = cur_ptr->next;
					}
					if (cur_ptr->key == new_key)
					{
						count_of_compares++;
						std::cout << "����� �������. ���������� �� ����������." << std::endl;
						std::cout << "���� ����������� " << count_of_compares << " ��������� (-�, -��)." << std::endl;
						return;
					}
					cur_ptr->next = new Node{};
					cur_ptr->next->key = new_key;
					hash_table.array[index].last = cur_ptr->next;
				}
				hash_table.count_key++;
				std::cout << "���� ��� �������� �� ������� " << index << "." << std::endl;
				common_add_count_of_compares += count_of_compares;
			}
		}
		std::cout << "���� ����������� " << count_of_compares << " ��������� (-�, -��)." << std::endl;
	//}
	//else
		//std::cout << "���������� ����������� ������ �����������. �������� ����� ���� ������." << std::endl;
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
		if (hash_table.array[index].key == "")
		{
			count_of_compares++;
			std::cout << "������� ����� ��� � ���-�������." << std::endl;
		}
		else
		{
			if (hash_table.array[index].key == finding_key)
			{
				count_of_compares++;
				std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
			}
			else
			{
				count_of_compares++;
				if (hash_table.array[index].first != nullptr)
				{
					Node* cur_ptr{ hash_table.array[index].first };
					while (cur_ptr->next != nullptr)
					{
						count_of_compares++;
						if (cur_ptr->key == finding_key)
						{
							std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
							std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
							return;
						}
						cur_ptr = cur_ptr->next;
					}
					if (cur_ptr->key == finding_key)
					{
						count_of_compares++;
						std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
						std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
						return;
					}
				}
				std::cout << "������� ����� ��� � ���-�������." << std::endl;
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
	{
		std::cout << i << ": " << hash_table.array[i].key;
		if (hash_table.array[i].first != nullptr)
		{
			Node* cur_ptr{ hash_table.array[i].first };
			while (cur_ptr != nullptr)
			{
				std::cout << " -> " << cur_ptr->key;
				cur_ptr = cur_ptr->next;
			}
		}
		std::cout << std::endl;
	}
}
void delKeyFromHashTable(HashTable& hash_table)
{
	if (hash_table.count_key != 0)
	{
		int count_of_compares{};
		printHashTable(hash_table);
		std::cout << "����� ���� �� ������ �������? " << std::endl;
		std::string del_key{};
		std::getline(std::cin, del_key);
		int index{ hashFunc(del_key) };
		bool is_elem{ false };

		if (hash_table.array[index].key == "")
		{
			count_of_compares++;
			is_elem = false;
		}
		else
		{
			if (hash_table.array[index].key == del_key)
			{
				is_elem = true;
				count_of_compares++;
				std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
				std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
				hash_table.count_key--;
				if (hash_table.array[index].first == nullptr)
					hash_table.array[index].key = "";
				else
				{
					hash_table.array[index].key = hash_table.array[index].first->key;
					Node* cur_ptr{ hash_table.array[index].first };
					hash_table.array[index].first = cur_ptr->next;
					delete cur_ptr;
				}
			}
			else
			{
				count_of_compares++;
				if (hash_table.array[index].first != nullptr)
				{
					Node* cur_ptr{ hash_table.array[index].first };
					while (cur_ptr->next != nullptr)
					{
						count_of_compares++;
						if (cur_ptr->key == del_key)
						{
							std::cout << "������ ���� ������ �� ������� " << index << "." << std::endl;
							std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
							is_elem = true;
							break;
						}
						cur_ptr = cur_ptr->next;
					}
					if (!is_elem && cur_ptr->key == del_key)
					{
						count_of_compares++;
						is_elem = true;
					}
					if (is_elem)
					{
						Node* prev_ptr{ hash_table.array[index].first };
						if (cur_ptr == hash_table.array[index].first)
						{
							hash_table.array[index].first = cur_ptr->next;
							if (cur_ptr->next == nullptr) hash_table.array[index].last = nullptr;
							std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
						}
						else if (cur_ptr == hash_table.array[index].last)
						{
							while (prev_ptr->next != cur_ptr)
								prev_ptr = prev_ptr->next;
							hash_table.array[index].last = prev_ptr;
							prev_ptr->next = nullptr;
							std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
						}
						else
						{
							while (prev_ptr->next != cur_ptr)
								prev_ptr = prev_ptr->next;
							prev_ptr->next = cur_ptr->next;
						}
						hash_table.count_key--;
						delete cur_ptr;
					}
				}
			}
		}
		if (!is_elem)
		{
			std::cout << "���� ����������� " << count_of_compares << " ��������e (-�, -��)." << std::endl;
			std::cout << "������ ���� �� ������ � ���-�������." << std::endl;
		}
		else
			std::cout << "���� ��� ������� ������." << std::endl;
	}
	else
		std::cout << "���-������� ������." << std::endl;
}

void delHashTable(HashTable& hash_table)
{
	if (hash_table.count_key != 0)
	{
		for (int i{}; i < hash_table.count_key; i++)
		{
			if (hash_table.array[i].first != nullptr)
			{
				Node* cur_ptr{ hash_table.array[i].first };
				while (cur_ptr != nullptr)
				{
					Node* del_cur_ptr{ cur_ptr };
					cur_ptr = cur_ptr->next;
					delete del_cur_ptr;
				}
			}
		}
	}
}