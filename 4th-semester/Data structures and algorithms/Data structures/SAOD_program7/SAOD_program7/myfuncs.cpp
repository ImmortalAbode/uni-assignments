#include <iostream>
#include <string>

#include "myfuncs.h"
#include "mystruct.h"

//������� ��� ������ �������� �� �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� �� �������?" << std::endl;
	std::cout << "1 - �������� ������ � ������ ����������� � ������� �� ����� �������������� ������ ���������.\n"
		<< "2 - �������� ������ � �������� ����������� � ������� �� ����� �������������� ������ ���������.\n"
		<< "3 - ����� �������� � �������� �������������� ������ � ������ �����������.\n"
		<< "4 - ����� �������� � �������� �������������� ������ � �������� �����������.\n"
		<< "5 - ���������� ������ �������� ����� ���������.\n"
		<< "6 - ���������� ������ �������� �� ���������.\n"
		<< "7 - �������� ��������� ��������.\n"
		<< "8 - ����� �� ���������.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
		{
			return choice[0];
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 8. ��������� ����. " << std::endl;
	}
}

//��������������� ����������� �������.
bool isEmpty(List* my_list)
{
	return my_list->Head_ptr->Next == my_list->Head_ptr ? true : false;
}
Node* searchNodeForward(List* my_list, const int& searching_elem)
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
Node* searchNodeBackward(List* my_list, const int& searching_elem)
{
	Node* current{ my_list->Head_ptr };
	for (int i{}; i < my_list->count; i++)
	{
		current = current->Prev;
		if (current->data == searching_elem)
			return current;
	}
	return nullptr;
}
void clearList(List*& my_list)
{
	int count{ my_list->count };
	for (int i{}; i < count;i++)
	{
		Node* current{ my_list->Head_ptr->Next };
		my_list->Head_ptr->Prev->Next = current;
		current->Prev = my_list->Head_ptr->Prev;
		my_list->Head_ptr->Next = nullptr;
		my_list->Head_ptr->Prev = nullptr;
		delete my_list->Head_ptr;
		my_list->Head_ptr = current;
		my_list->count--;
	}
	delete my_list->Head_ptr;
	delete my_list;
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
void printDataList(List* my_list, std::string const& choice)
{
	if (!isEmpty(my_list))
	{
		std::cout << "��� ������: " << std::endl;
		Node* current{ my_list->Head_ptr };
		if (choice == "forward")
		{
			for (int i{}; i < my_list->count;i++)
			{
				current = current->Next;
				std::cout << i + 1 << "-��/-��/-�� ������� ������:\t" << current->data << std::endl;
			}
		}
		else if (choice == "backward")
		{
			for (int i{}; i < my_list->count;i++)
			{
				current = current->Prev;
				std::cout << my_list->count - i << "-��/-��/-�� ������� ������:\t" << current->data << std::endl;
			}
		}
		std::cout << std::endl;
	}
	else
		std::cout << "��� ������ ����." << std::endl;
}
void searchDataList(List* my_list, std::string const& choice)
{
	if (!isEmpty(my_list))
	{
		while (true)
		{
			printDataList(my_list, "forward");
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				int number{ convertStrToInt(userStr) };
				int count{};
				Node* current{ my_list->Head_ptr };
				for (int i{}; i < my_list->count; i++)
				{
					if (choice == "forward") current = current->Next;
					if (choice == "backward") current = current->Prev;
					if (current->data == number)
					{
						count++;
						if (choice == "forward") std::cout << i + 1 << "-��/-��/-�� ������� ������:\t" << current->data << std::endl;
						if (choice == "backward") std::cout << my_list->count - i << "-��/-��/-�� ������� ������:\t" << current->data << std::endl;
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
void addNewElement(List*& my_list, std::string const& choice)
{
	if (isEmpty(my_list) && choice == "backward")
		std::cout << "������ �������� ������� �� ���������, ����� ������ ������!" << std::endl;
	else if (isEmpty(my_list) && choice == "forward")
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
				new_node->Next = my_list->Head_ptr;
				new_node->Prev = my_list->Head_ptr;
				my_list->Head_ptr->Next = new_node;
				my_list->Head_ptr->Prev = new_node;
				my_list->count++;
				std::cout << "������ ������� " << my_list->Head_ptr->Next->data << " ��� ������� �������� � ������." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
				clearLists(my_list);
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
				printDataList(my_list, "forward");
				if (choice == "backward") std::cout << "������� �������� ��������, �� �������� ������ ����������� ����������: ";
				if (choice == "forward") std::cout << "������� �������� ��������, ����� �������� ������ ����������� ����������: ";
				std::string userStr_2{ getUserInput_2() };
				int elem{ convertStrToInt(userStr_2) };
				Node* important_node{ searchNodeForward(my_list, elem) };
				if (important_node != nullptr)
				{
					if (choice == "backward")
					{
						try
						{
							Node* new_node = new Node{};
							new_node->data = number;
							new_node->Next = important_node;
							new_node->Prev = important_node->Prev;
							important_node->Prev->Next = new_node;
							important_node->Prev = new_node;
							my_list->count++;
							std::cout << "����� ������� " << number << " ��� ������� �������� � ������." << std::endl;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
							clearLists(my_list);
							exit(-1);
						}
					}
					if (choice == "forward")
					{
						try
						{
							Node* new_node = new Node{};
							new_node->data = number;
							new_node->Next = important_node->Next;
							new_node->Prev = important_node;
							important_node->Next = new_node;
							new_node->Next->Prev = new_node;
							my_list->count++;
							std::cout << "����� ������� " << number << " ��� ������� �������� � ������." << std::endl;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
							clearLists(my_list);
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
void removeElement(List*& my_list)
{
	if (!isEmpty(my_list))
	{
		printDataList(my_list, "forward");
		while (true)
		{
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				int number{ convertStrToInt(userStr) };
				Node* important_node{ searchNodeForward(my_list, number) };
				if (important_node != nullptr)
				{
					important_node->Prev->Next = important_node->Next;
					important_node->Next->Prev = important_node->Prev;
					important_node->Next = nullptr;
					important_node->Prev = nullptr;
					delete important_node;
					my_list->count--;
					std::cout << "������� " << number << " ��� ������� ������ �� ������." << std::endl;
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
void clearLists(List*& my_list)
{
	clearList(my_list);
	std::cout << "��� ���������� ������ ���� ������� ���������� � ����. ���������� ���������..." << std::endl;
}