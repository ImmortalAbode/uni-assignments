#include <iostream>
#include <string>

#include "myfuncs.h"
#include "mystruct.h"

//Функции для выбора операции со списком.
void MenuOfProgram()
{
	std::cout << "Что вы хотите сделать со структурой?" << std::endl;
	std::cout << "1 - Полный проход по всей структуре с выводом на экран информационных частей элементов.\n"
		<< "2 - Поиск элемента с заданной информационной частью в прямом направлении (для подсписков).\n"
		<< "3 - Поиск элемента с заданной информационной частью в обратном направлении (для подсписков).\n"
		<< "4 - Добавление нового элемента в список с пустым связанным списком (в базовый список) после заданного подсписка.\n"
		<< "5 - Добавление нового элемента в список с пустым связанным списком (в базовый список) до заданного подсписка.\n"
		<< "6 - Добавление элемента в связанный список до заданного элемента.\n"
		<< "7 - Добавление элемента в связанный список после заданного элемента.\n"
		<< "8 - Удаление элемента из связанного списка.\n"
		<< "9 - Удаление элемента из базового списка.\n"
		<< "q - Выход из программы.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || 
			choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "q")
			return choice[0];
		else
			std::cout << "Вы должны ввести целое число от 1 до 9 или 'q'. Повторите ввод. " << std::endl;
	}
}

//Вспомогательные проверяющие функции.
bool isEmptyStruct(MainList* my_mainList)
{
	return my_mainList->Head_ptr->Next == my_mainList->Head_ptr ? true : false;
}
bool isEmptyList(Node* my_subList)
{
	return  my_subList->subHead_ptr->Next == my_subList->subHead_ptr ? true : false;
}
Node* searchNode(MainList* my_mainList, const int& searching_elem)
{
	Node* current{ my_mainList->Head_ptr };
	for (int i{}; i < my_mainList->count; i++)
	{
		current = current->Next;
		if (current->ListData == searching_elem)
			return current;
	}
	return nullptr;
}
SubNode* searchSubNodeForward(Node* my_subList, const int& searching_elem)
{
	SubNode* current{ my_subList->subHead_ptr };
	for (int i{}; i < my_subList->count; i++)
	{
		current = current->Next;
		if (current->data == searching_elem)
			return current;
	}
	return nullptr;
}
SubNode* searchSubNodeBackward(Node* my_subList, const int& searching_elem)
{
	SubNode* current{ my_subList->subHead_ptr };
	for (int i{}; i < my_subList->count; i++)
	{
		current = current->Prev;
		if (current->data == searching_elem)
			return current;
	}
	return nullptr;
}
std::string createNumList(MainList* my_mainList)
{
	printDataStruct(my_mainList);
	std::cout << "Введите номер списка, которого еще нет в структуре, или нажмите 'q', чтобы вернуться в меню: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите целое положительное число или 'q': ";
		else if (userStr == "q" || checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0)
		{
			int num{ convertStrToInt(userStr) };
			bool isNum{ false };
			Node* current{ my_mainList->Head_ptr };
			for (int i{}; i < my_mainList->count;i++)
			{
				current = current->Next;
				if (current->ListData == num)
				{
					isNum = true;
					break;
				}
			}
			if (num >= 1 && !isNum)
				return userStr;
			else
				std::cout << "Подсписок с данным номером уже есть в структуре! Измените номер, повторите ввод: " << std::endl;
		}
		else
			std::cout << "Ошибка ввода. Введите целое положительное число или 'q': ";
	}
}
int getNumList(MainList* my_mainList)
{
	while (true)
	{
		printDataStruct(my_mainList);
		std::cout << "Выберите список из структуры, который хотите изменить: ";
		std::string userStr{ getUserInput_2() };
		int num{ convertStrToInt(userStr) };
		bool isNum{ false };
		Node* current{ my_mainList->Head_ptr };
		for (int i{}; i < my_mainList->count;i++)
		{
			current = current->Next;
			if (current->ListData == num)
			{
				isNum = true;
				break;
			}
		}
		if (isNum)
			return num;
		else
			std::cout << "Подсписка с данным номером нет в структуре. Повторите ввод. " << std::endl;
	}
}
void clearList(Node*& my_subList)
{
	int count{ my_subList->count };
	for (int i{}; i < count;i++)
	{
		SubNode* current{ my_subList->subHead_ptr->Next };
		my_subList->subHead_ptr->Prev->Next = current;
		current->Prev = my_subList->subHead_ptr->Prev;
		my_subList->subHead_ptr->Next = nullptr;
		my_subList->subHead_ptr->Prev = nullptr;
		delete my_subList->subHead_ptr;
		my_subList->subHead_ptr = current;
		my_subList->count--;
	}
	delete my_subList->subHead_ptr;
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
std::string getUserInput_3(MainList* my_mainList)
{
	std::cout << "Введите список из структуры, который хотите изменить, или нажмите 'q', чтобы вернуться в меню: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "Ошибка ввода. Введите целое положительное число или 'q': ";
		else if (userStr == "q" || checkStrIsNumeric(userStr) && convertStrToInt(userStr) > 0)
		{
			int num{ convertStrToInt(userStr) };
			bool isNum{ false };
			Node* current{ my_mainList->Head_ptr };
			for (int i{}; i < my_mainList->count;i++)
			{
				current = current->Next;
				if (current->ListData == num)
				{
					isNum = true;
					break;
				}
			}
			if (isNum || userStr == "q")
				return userStr;
			else
				std::cout << "Подсписка с данным номером нет в структуре! Повторите ввод: " << std::endl;
		}
		else
			std::cout << "Ошибка ввода. Введите целое положительное число или 'q': ";
	}
}

//Функции для работы со структурой.
void printDataStruct(MainList* my_mainList)
{
	if (!isEmptyStruct(my_mainList))
	{
		std::cout << "\tВаш список списков: " << std::endl;
		Node* current{ my_mainList->Head_ptr };
		for (int i{}; i < my_mainList->count;i++)
		{
			current = current->Next;
			std::cout << "[" << current->ListData << "]:\t";
			SubNode* subCurrent{ current->subHead_ptr };
			for (int j{}; j < current->count; j++)
			{
				subCurrent = subCurrent->Next;
				std::cout << subCurrent->data << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "Ваш список списков пуст." << std::endl;
}
void searchDataStruct(MainList* my_mainList, std::string const& choice)
{
	if (!isEmptyStruct(my_mainList))
	{
		bool isSubElem{ false };
		Node* current{ my_mainList->Head_ptr };
		for (int i{}; i < my_mainList->count;i++)
		{
			current = current->Next;
			if (!isEmptyList(current))
				isSubElem = true;
		}
		if (isSubElem)
		{
			while (true)
			{
				printDataStruct(my_mainList);
				std::string userStr{ getUserInput() };
				if (userStr != "q")
				{
					int number{ convertStrToInt(userStr) };
					int count{};
					Node* current{ my_mainList->Head_ptr };
					for (int i{}; i < my_mainList->count; i++)
					{
						bool flag{ true };
						if (choice == "forward") current = current->Next;
						if (choice == "backward") current = current->Prev;
						SubNode* subCurrent{ current->subHead_ptr };
						for (int j{}; j < current->count; j++)
						{
							if (choice == "forward") subCurrent = subCurrent->Next;
							if (choice == "backward") subCurrent = subCurrent->Prev;
							if (subCurrent->data == number)
							{
								count++;
								if (flag)
								{
									flag = false;
									std::cout << "Список [" << current->ListData << "]: " << std::endl;
								}
								if (choice == "forward")
								{
									std::cout << j + 1 << "-ой/-ий/-ый элемент списка:\t" << subCurrent->data << std::endl;
								}
								if (choice == "backward")
								{
									std::cout << current->count - j << "-ой/-ий/-ый элемент списка:\t" << subCurrent->data << std::endl;
								}
							}
						}
					}
					if (count != 0)
						std::cout << "Всего было найдено " << count << " элемент(-a/-ов)." << std::endl;
					else
						std::cout << "В списке списков нет элементов с данной информационной частью." << std::endl;
					break;
				}
				else
				{
					std::cout << "Возвращение в меню. " << std::endl;
					break;
				}
			}
		}
		else std::cout << "Ваши связные списки пусты. Добавьте сначала в них элементы." << std::endl;
	}
	else
		std::cout << "Ваш список списков пуст, сначала добавьте элементы." << std::endl;
}
void addNewElementInStruct(MainList*& my_mainList, std::string const& choice)
{
	if (isEmptyStruct(my_mainList) && choice == "backward")
		std::cout << "Нельзя добавить новый подсписок в структуру, когда она пустая!" << std::endl;
	else if (isEmptyStruct(my_mainList) && choice == "forward")
	{
		std::cout << "Добавьте первый подсписок списка списков." << std::endl;
		std::string userStr{ createNumList(my_mainList) };
		if (userStr != "q")
		{
			try
			{
				int numList{ convertStrToInt(userStr) };

				Node* new_Node = new Node{};
				my_mainList->Head_ptr->Next = new_Node;
				my_mainList->Head_ptr->Prev = new_Node;
				new_Node->Next = my_mainList->Head_ptr;
				new_Node->Prev = my_mainList->Head_ptr;

				new_Node->ListData = numList;

				SubNode* new_subNode = new SubNode{};
				new_Node->subHead_ptr = new_subNode;

				new_subNode->Next = new_subNode;
				new_subNode->Prev = new_subNode;

				my_mainList->count++;
				
				std::cout << "Первый подсписок [" << new_Node->ListData << "] был успешно добавлен в структуру." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
				clearStruct(my_mainList);
				exit(-1);
			}
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
	}
	else
	{
		std::cout << "Добавьте новый подсписок списка списков." << std::endl;
		std::string userStr{ createNumList(my_mainList) };
		if (userStr != "q")
		{
			while (true)
			{
				try
				{
					int numList{ convertStrToInt(userStr) };

					Node* new_Node = new Node{};
					new_Node->ListData = numList;
					printDataStruct(my_mainList);
					if (choice == "forward") std::cout << "Введите номер подсписка, после которого хотите осуществить добавление: ";
					else std::cout << "Введите номер подсписка, до которого хотите осуществить добавление: ";

					std::string userStr_2{ getUserInput_2() };
					int elem{ convertStrToInt(userStr_2) };
					Node* important_node{ searchNode(my_mainList, elem) };
					if (important_node != nullptr)
					{
						if (choice == "forward")
						{
							new_Node->Next = important_node->Next;
							new_Node->Prev = important_node;
							important_node->Next->Prev = new_Node;
							important_node->Next = new_Node;
						}
						else
						{
							new_Node->Next = important_node;
							new_Node->Prev = important_node->Prev;
							important_node->Prev->Next = new_Node;
							important_node->Prev = new_Node;
						}
						SubNode* new_subNode = new SubNode{};
						new_Node->subHead_ptr = new_subNode;
						new_subNode->Next = new_subNode;
						new_subNode->Prev = new_subNode;
						my_mainList->count++;
						std::cout << "Подсписок [" << new_Node->ListData << "] был успешно добавлен в структуру." << std::endl;
						break;
					}
					else
						std::cout << "Заданного вами подсписка нет в структуре! Повторите ввод. " << std::endl;
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
					std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
					clearStruct(my_mainList);
					exit(-1);
				}
			}
		}
		else
			std::cout << "Возвращение в меню." << std::endl;
	}
}
void addNewElementInList(MainList*& my_mainList, std::string const& choice)
{
	if (isEmptyStruct(my_mainList))
		std::cout << "Ваша структура пустая. Сначала добавьте новый список." << std::endl;
	else
	{
		int numList{ getNumList(my_mainList) };
		Node* current{ searchNode(my_mainList, numList) };
		if (isEmptyList(current) && choice == "backward")
			std::cout << "Нельзя добавить элемент до заданного, когда список пустой!" << std::endl;
		else if (isEmptyList(current) && choice == "forward")
		{
			std::cout << "Добавьте первый элемент в список." << std::endl;
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				try
				{
					int number{ convertStrToInt(userStr) };
					SubNode* new_subNode = new SubNode{};
					new_subNode->data = number;
					new_subNode->Next = current->subHead_ptr;
					new_subNode->Prev = current->subHead_ptr;
					current->subHead_ptr->Next = new_subNode;
					current->subHead_ptr->Prev = new_subNode;
					current->count++;
					std::cout << "Первый элемент " << new_subNode->data << " был успешно добавлен в подсписок." << std::endl;
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
					std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
					clearStruct(my_mainList);
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
					try
					{
						printDataStruct(my_mainList);
						if (choice == "backward") std::cout << "Введите значение элемента, до которого хотите осуществить добавление: ";
						if (choice == "forward") std::cout << "Введите значение элемента, после которого хотите осуществить добавление: ";
						std::string userStr_2{ getUserInput_2() };
						int elem{ convertStrToInt(userStr_2) };
						SubNode* important_subNode{ searchSubNodeForward(current, elem) };
						if (important_subNode != nullptr)
						{
							SubNode* new_subNode = new SubNode{};
							if (choice == "forward")
							{
								new_subNode->Next = important_subNode->Next;
								important_subNode->Next = new_subNode;
								new_subNode->Prev = important_subNode;
								new_subNode->Next->Prev = new_subNode;
							}
							else
							{
								new_subNode->Next = important_subNode;
								new_subNode->Prev = important_subNode->Prev;
								important_subNode->Prev = new_subNode;
								new_subNode->Prev->Next = new_subNode;
							}
							new_subNode->data = number;
							current->count++;
							break;
						}
						else
							std::cout << "Заданного вами элемента нет в списке! Повторите ввод. " << std::endl;
					}
					catch (const std::exception& e)
					{
						std::cout << e.what() << std::endl;
						std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
						clearStruct(my_mainList);
						exit(-1);
					}
				}
			}
			else
				std::cout << "Возвращение в меню." << std::endl;
		}
	}
}
void removeElementFromList(MainList*& my_mainList)
{
	if (!isEmptyStruct(my_mainList))
	{
		int numList{ getNumList(my_mainList) };
		while (true)
		{
			printDataStruct(my_mainList);
			std::string userStr{ getUserInput() };
			if (userStr != "q")
			{
				Node* current{ searchNode(my_mainList, numList)};
				int number{ convertStrToInt(userStr) };
				SubNode* important_subNode{ searchSubNodeForward(current, number) };
				if (important_subNode != nullptr)
				{
					important_subNode->Prev->Next = important_subNode->Next;
					important_subNode->Next->Prev = important_subNode->Prev;
					important_subNode->Next = nullptr;
					important_subNode->Prev = nullptr;
					delete important_subNode;
					current->count--;
					std::cout << "Элемент " << number << " был успешно удален из подсписка [" << current->ListData << "]." << std::endl;
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
		std::cout << "Ваша структура пуста, сначала добавьте список." << std::endl;
}
void removeElementFromStruct(MainList*& my_mainList)
{
	if (!isEmptyStruct(my_mainList))
	{
		while (true)
		{
			printDataStruct(my_mainList);
			std::string userStr{ getUserInput_3(my_mainList) };
			if (userStr != "q")
			{
				Node* important_Node{ searchNode(my_mainList, convertStrToInt(userStr)) };
				if (important_Node != nullptr)
				{
					clearList(important_Node);
					important_Node->Prev->Next = important_Node->Next;
					important_Node->Next->Prev = important_Node->Prev;
					important_Node->Next = nullptr;
					important_Node->Prev = nullptr;
					std::cout << "Список [" << important_Node->ListData << "] был успешно удален из структуры." << std::endl;
					delete important_Node;
					my_mainList->count--;
					break;
				}
				else
					std::cout << "Заданного вами списка нет в структуре! Повторите ввод. " << std::endl;
			}
			else
			{
				std::cout << "Возвращение в меню. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "Ваш список списков пуст, сначала добавьте подсписок." << std::endl;
}
void clearStruct(MainList*& my_mainList)
{
	int count{ my_mainList->count };
	for (int i{}; i < count;i++)
	{
		Node* current{ my_mainList->Head_ptr->Next };
		clearList(current);
		my_mainList->Head_ptr->Prev->Next = current;
		current->Prev = my_mainList->Head_ptr->Prev;
		my_mainList->Head_ptr->Next = nullptr;
		my_mainList->Head_ptr->Prev = nullptr;
		delete my_mainList->Head_ptr;
		my_mainList->Head_ptr = current;
		my_mainList->count--;
	}
	delete my_mainList->Head_ptr;
	delete my_mainList;
	std::cout << "Вся выделенная память была успешно возвращена в кучу. Завершение программы..." << std::endl;
}