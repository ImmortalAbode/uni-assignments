#include <iostream>
#include <string>

#include "myfuncs.h"
#include "list.h"

//������� ��� ������ �������� �� �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� �� �������?" << std::endl;
	std::cout << "1 - ������ �� ������ � ������� �� ����� �������������� ������ ���������.\n"
		<< "2 - ����� �������� � �������� �������������� ������.\n"
		<< "3 - ���������� ������ �������� �� ���������.\n"
		<< "4 - ���������� ������ �������� ����� ���������.\n"
		<< "5 - �������� ��������� ��������.\n"
		<< "6 - �������� ���������������� ������ ��������� ���������.\n"
		<< "7 - ����� �� ���������.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 7. ��������� ����. " << std::endl;
	}
}

//��������������� ����������� �������.
bool isEmpty(List* my_list)
{
	return my_list->Head_ptr->Next == nullptr ? true : false;
}
Node* searchNode(List* my_list, const int& searching_elem)
{
	Node* current{ my_list->Head_ptr };
	for (int i{}; i < my_list->count; i++)
	{
		current = current->Next;
		if (current->data == searching_elem)
			return current;
	}
	return nullptr;
}
void clearList(List*& list)
{
	int count{ list->count };
	for (int i{}; i < count;i++)
	{
		Node* current{ list->Head_ptr->Next };
		list->Head_ptr->Next = nullptr;
		delete list->Head_ptr;
		list->Head_ptr = current;
		list->count--;
	}
	delete list->Head_ptr;
	delete list;
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
			std::cout << "������ �����. ������� ����� �����.";
		else if (checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "������ �����. ������� ����� �����.";
	}
}

//������� ��� ������ �� �������.
void printDataList(List* list)
{
	if (!isEmpty(list))
	{
		std::cout << "��� ������: " << std::endl;
		Node* current{ list->Head_ptr };
		for (int i{}; i < list->count;i++)
		{
			current = current->Next;
			std::cout << i + 1 << "-��/-��/-�� ������� ������:\t" << current->data << std::endl;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "��� ������ ����." << std::endl;
}
void searchDataList(List* my_list)
{
	if (!isEmpty(my_list))
	{
		while (true)
		{
			printDataList(my_list);
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				int number{ convertStrToInt(userStr) };
				int count{};
				Node* current{ my_list->Head_ptr };
				for (int i{}; i < my_list->count; i++)
				{
					current = current->Next;
					if (current->data == number)
					{
						count++;
						std::cout << i+1 << "-��/-��/-�� ������� ������:\t" << current->data << std::endl;
					}
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
void addNewElement(List*& my_list, const int& choice, List*& sub_list)
{
	if (isEmpty(my_list) && choice == 1)
		std::cout << "������ �������� ������� �� ���������, ����� ������ ������!" << std::endl;
	else if (isEmpty(my_list) && choice == 2)
	{
		std::cout << "�������� ������ ������� � ������." << std::endl;
		std::string userStr{ getUserInput() };
		if (userStr != "q")
		{
			try
			{
				int number{ convertStrToInt(userStr) };
				Node* new_node = new Node{};
				new_node->data = number;
				new_node->Next = nullptr;
				my_list->Head_ptr->Next = new_node;
				my_list->count++;
				std::cout << "������ ������� " << my_list->Head_ptr->Next->data << " ��� ������� �������� � ������." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
				clearLists(my_list, sub_list);
				exit(-1);
			}
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
				printDataList(my_list);
				if (choice == 1) std::cout << "������� �������� ��������, �� �������� ������ ����������� ����������: ";
				if (choice == 2) std::cout << "������� �������� ��������, ����� �������� ������ ����������� ����������: ";
				std::string userStr_2{ getUserInput_2() };
				int elem{ convertStrToInt(userStr_2) };
				Node* important_node{ searchNode(my_list, elem) }, * current{ my_list->Head_ptr };
				if (important_node != nullptr)
				{
					if (choice == 1)
					{
						try
						{
							Node* new_node = new Node{};
							new_node->data = number;
							new_node->Next = important_node;
							while (current->Next != important_node)
								current = current->Next;
							current->Next = new_node;
							my_list->count++;
							std::cout << "����� ������� " << number << " ��� ������� �������� � ������." << std::endl;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
							clearLists(my_list, sub_list);
							exit(-1);
						}
					}
					if (choice == 2)
					{
						try
						{
							Node* new_node = new Node{};
							new_node->data = number;
							new_node->Next = important_node->Next;
							important_node->Next = new_node;
							my_list->count++;
							std::cout << "����� ������� " << number << " ��� ������� �������� � ������." << std::endl;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
							clearLists(my_list, sub_list);
							exit(-1);
						}
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
void removeElement(List*& my_list, List*& sub_list)
{
	if (!isEmpty(my_list))
	{
		printDataList(my_list);
		while (true)
		{
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				int number{ convertStrToInt(userStr) };
				Node* important_node{ searchNode(my_list, number) }, * current{ my_list->Head_ptr };
				if (important_node != nullptr)
				{
					while (current->Next != important_node)
						current = current->Next;
					current->Next = important_node->Next;
					important_node->Next = sub_list->Head_ptr->Next;
					sub_list->Head_ptr->Next = important_node;
					my_list->count--;
					sub_list->count++;
					std::cout << "������� "<< number << " ��� ������� ������ �� ������ � �������� �� ��������������� ������ (����)." << std::endl;
					break;
				}
				else
					std::cout << "��������� ���� �������� ��� � ������! ��������� ����. " << std::endl;
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
void clearLists(List*& my_list, List*& sub_list)
{
	clearList(my_list);
	clearList(sub_list);
	std::cout << "��� ���������� ������ ���� ������� ���������� � ����. ���������� ���������..." << std::endl;
}