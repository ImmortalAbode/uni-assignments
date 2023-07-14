#include <iostream>
#include <string>

#include "myfuncs.h"
#include "list.h"

//Функции для выбора операции со списком.
void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать со списком?" << std::endl;
	std::cout << "1 - Проход по списку с выводом на экран информационных частей элементов.\n"
		<< "2 - Поиск элемента с заданной информационной частью.\n"
		<< "3 - Добавление нового элемента до заданного.\n"
		<< "4 - Добавление нового элемента после заданного.\n"
		<< "5 - Удаление заданного элемента.\n"
		<< "6 - Просмотр вспомогательного списка удаленных элементов.\n"
		<< "7 - Выход из программы.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
			std::cout << "Вы должны ввести целое число от 1 до 7. Повторите ввод. " << std::endl;
	}
}

//Вспомогательные проверяющие функции.
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
//Функции получения и проверки пользовательского ввода.
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
	std::cout << "Введите информационную часть элемента или нажмите 'q', чтобы вернуться в меню: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите целое число или 'q': ";
		else if (userStr == "q" || checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите целое число или 'q': ";
	}
}
std::string getUserInput_2()
{
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите целое число.";
		else if (checkStrIsNumeric(userStr))
			return userStr;
		else
			std::cout << "Ошибка ввода. Введите целое число.";
	}
}

//Функции для работы со списком.
void printDataList(List* list)
{
	if (!isEmpty(list))
	{
		std::cout << "Ваш список: " << std::endl;
		Node* current{ list->Head_ptr };
		for (int i{}; i < list->count;i++)
		{
			current = current->Next;
			std::cout << i + 1 << "-ой/-ий/-ый элемент списка:\t" << current->data << std::endl;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "Ваш список пуст." << std::endl;
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
						std::cout << i+1 << "-ой/-ий/-ый элемент списка:\t" << current->data << std::endl;
					}
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
void addNewElement(List*& my_list, const int& choice, List*& sub_list)
{
	if (isEmpty(my_list) && choice == 1)
		std::cout << "Нельзя добавить элемент до заданного, когда список пустой!" << std::endl;
	else if (isEmpty(my_list) && choice == 2)
	{
		std::cout << "Добавьте первый элемент в список." << std::endl;
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
				std::cout << "Первый элемент " << my_list->Head_ptr->Next->data << " был успешно добавлен в список." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
				clearLists(my_list, sub_list);
				exit(-1);
			}
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
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
				if (choice == 1) std::cout << "Введите значение элемента, до которого хотите осуществить добавление: ";
				if (choice == 2) std::cout << "Введите значение элемента, после которого хотите осуществить добавление: ";
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
							std::cout << "Новый элемент " << number << " был успешно добавлен в список." << std::endl;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
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
							std::cout << "Новый элемент " << number << " был успешно добавлен в список." << std::endl;
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
							clearLists(my_list, sub_list);
							exit(-1);
						}
					}
					break;
				}
				else
					std::cout << "Заданного вами элемента нет в списке! Повторите ввод. " << std::endl;
			}
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
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
					std::cout << "Элемент "<< number << " был успешно удален из списка и добавлен во вспомогательный список (стек)." << std::endl;
					break;
				}
				else
					std::cout << "Заданного вами элемента нет в списке! Повторите ввод. " << std::endl;
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
void clearLists(List*& my_list, List*& sub_list)
{
	clearList(my_list);
	clearList(sub_list);
	std::cout << "Вся выделенная память была успешно возвращена в кучу. Завершение программы..." << std::endl;
}