#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ArrayEightStrings.h"
#include "mystructs.h"
#include "constants.h"
#include "myfuncs.h"
//Проверка, чтобы в элементе было ровно 8 полeй.
bool CheckCorrectField(std::string data, unsigned count)
{
	std::stringstream Element{ data };
	std::string field{}, check{};
	int index_field{1};
	std::getline(Element, check, ';');
	while (std::getline(Element, field, ';'))
		index_field++;
	if (index_field != 8)
	{
		std::cout << count << "-й элемент имеет неправильное количество данных информационного поля." << std::endl;
		return false;
	}
	return true;
}

//Преобразует информационное поле элемента на поля и привязывает их к указателю.
void InitializationElement(std::stringstream&Data_field, Employee*&temp)
{
	std::string data{};
	ArrayEightStrings str_value;
	int index_field{};
	while (std::getline(Data_field, data, ';'))
	{
		str_value[index_field] = data;
		index_field++;
	}
	temp->Surname = str_value[0];
	temp->MiddleName = str_value[1];
	temp->Name = str_value[2];
	temp->Age = str_value[3];
	temp->MaritalStatus = str_value[4];
	temp->Spouse = str_value[5];
	temp->Kids = str_value[6];
	temp->Budget = str_value[7];
}

//Считывает файл, либо выдает запрос о добавлении первого элемента, если файл пустой.
bool GetListFromFile(Employee*&head, std::ifstream& Data_file)
{
	int count{ 1 }, flag{};
	std::string data{};
	while (!Data_file.eof())
	{
		if (std::getline(Data_file, data))
		{
			flag++;
			std::stringstream Data_field{ data };
			if (CheckCorrectField(data, count))
				GetNewElement(head, Data_field);
			else
				return false;
		}
		else if (flag == 0)
		{
			std::cout << "Ваш файл пустой. Хотите ввести первый элемент?" << std::endl <<
				"Да - 1" << std::endl <<
				"Нет - 0" << std::endl;
			while (true)
			{
				char sm;
				std::cin >> sm;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (sm == '0')
					return false;
				else if (sm == '1')
				{
					Employee* ea{ head };
					AddHeadOfList(head);
					return true;
				}
				else
					std::cerr << "Введите 0 или 1. Повторите ввод: ";
			}
		}
	}
	return true;
}

//Получение нового элемента по указателю и информационному полю.
void GetNewElement(Employee*& head, std::stringstream& Data_field)
{
	if (head == nullptr)
	{
		head = new Employee;
		InitializationElement(Data_field, head);
		head->next = head;
	}
	else
	{
		Employee* tail{ head };
		while (tail->next != head)
		{
			tail = tail->next;
		}
		tail->next = new Employee;
		tail = tail->next;
		InitializationElement(Data_field, tail);
		tail->next = head;
	}
}

//Если структуры не существует по какой-то причине, то добавляет первый ее элемент.
void AddHeadOfList(Employee*& head)
{
	std::string AddDataHead{};
	head = new Employee;
	std::cout << "Введите данные нового элемента:" << std::endl;
	std::cout << "Фамилия: ";
	std::getline(std::cin, AddDataHead);
	head->Surname = AddDataHead;

	std::cout << "Имя: ";
	std::getline(std::cin, AddDataHead);
	head->MiddleName = AddDataHead;

	std::cout << "Отчество (при отсутствии рекомендовано ставить '-'): ";
	std::getline(std::cin, AddDataHead);
	head->Name = AddDataHead;

	std::cout << "Возраст: ";
	std::getline(std::cin, AddDataHead);
	head->Age = AddDataHead;

	std::cout << "Семейное положение.";
	if (!FastInput_MS(head, AddDataHead))
	{
		std::cout << "Семейное положение: ";
		std::getline(std::cin, AddDataHead);
		head->MaritalStatus = AddDataHead;
	}
	std::cout << "Супруг(-а) (при отсутствии рекомендовано ставить '-'): ";
	std::getline(std::cin, AddDataHead);
	head->Spouse = AddDataHead;

	std::cout << "Дети (при отсутствии рекомендовано ставить '-'): ";
	std::getline(std::cin, AddDataHead);
	head->Kids = AddDataHead;

	std::cout << "Бюджет.";
	FastInput_Budget(head, AddDataHead);

	head->next = head;
	std::cout << "Новый первый элемент был добавлен." << std::endl;
}

//Основная функция загрузки структуры из файла.
bool loadingList(const std::string fileName, Employee*& head)
{
	std::ifstream Data_file(fileName);
	if (!Data_file)
	{
		std::cerr << "Не удалось открыть файл!" << std::endl;
		return false;
	}
	else
	{
		int flag{};
		flag = GetListFromFile(head, Data_file);
		if (flag == 1)
			return true;
		else
			return false;
	}
} 

//Функция выгрузки структуры в файл.
bool unloadingList(const std::string fileName, Employee* head)
{
	Employee* tail{ head };
	std::ofstream Data_file(fileName);
	if (head != nullptr)
	{
		do {
			if (tail->next != head)
			{
				Data_file << tail->Surname << ";" << tail->MiddleName << ";" << tail->Name << ";" << tail->Age << ";" << tail->MaritalStatus << ";" << 
					tail->Spouse << ";" << tail->Kids << ";" << tail->Budget << std::endl;
				tail = tail->next;
			}
			else
			{
				Data_file << tail->Surname << ";" << tail->MiddleName << ";" << tail->Name << ";" << tail->Age << ";" << tail->MaritalStatus << ";" <<
					tail->Spouse << ";" << tail->Kids << ";" << tail->Budget;
				tail = tail->next;
			}
		} while (tail != head);
		while (true)
		{
			Employee* clean_ptr{ tail };
			tail = tail->next;
			std::cout << "Человек " << clean_ptr->Surname << ' ' << clean_ptr->MiddleName << ' ' << clean_ptr->Name << ",... выгружен и удален из оперативной памяти." << std::endl;
			delete clean_ptr;
			if (tail == head)
				break;
		}
	}

	Data_file.close();
	return true;
}

//Сравнивает введенный пользователем номер элемента и количество элементов структуры.
bool CheckAmountOfElements(Employee* head, unsigned num)
{
	Employee* tail{ head };
	unsigned count{1};
	tail = tail->next;
	while (tail != head)
	{
		tail = tail->next;
		count++;
	}
	return (num >= 1 && num <= count) ? true : false;
}

//Вывод структуры на консоль.
void PrintList(const Employee* head)
{
	const Employee* tail{ head };
	if (head != nullptr)
	{
		int index_number{};
		std::cout << "____________________ Ваш список: ____________________" << std::endl;
		do {
			index_number++;
			std::cout << index_number << ") " << tail->Surname << ";" << tail->MiddleName << ";" << tail->Name << ";" << tail->Age << ";" << tail->MaritalStatus << 
				";" << tail->Spouse << ";" << tail->Kids << ";" << tail->Budget << std::endl;
			tail = tail->next;
		} while (tail != head);
	}
	else
		std::cout << "Список пуст." << std::endl;
}

//Получение выбора пользователя.
char getCase()
{
	MenuForChoices();
	while (true)
	{
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
		{
			std::cout << "Ошибка ввода, введите только номер вашего выбора. Повторите ввод:" << std::endl;
		}
	}
}

//Меню возможных действий.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Добавить заданный элемент в список по порядковому номеру. " << std::endl <<
		"2) Удалить заданный элемент из списка по порядковому номеру." << std::endl <<
		"3) Печать всех элементов (вывод на консоль)." << std::endl <<
		"4) Присвоить всем элементам предусмотренные значения." << std::endl <<
		"5) Выход." << std::endl;
}

//Получение натурального числа для каких-то нужд.
double GetNumber()
{
	while (true)
	{
		double num;
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ошибка ввода, вы ввели не число. Повторите ввод:\n";
		}
		else if (num != int(num))
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Вы ввели не натуральное число. Повторите ввод:\n ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
	}
}

//Добавление нового элемента в структуру.
void AddNewElement(Employee*& previous, Employee *ea)
{
	std::string AddElement{};
	Employee* current{};

	ea = new Employee;
	current = previous->next;
	previous->next = ea;
	std::cout << "Введите данные нового элемента:" << std::endl;

	std::cout << "Фамилия: ";
	std::getline(std::cin, AddElement);
	ea->Surname = AddElement;

	std::cout << "Имя: ";
	std::getline(std::cin, AddElement);
	ea->MiddleName = AddElement;

	std::cout << "Отчество (при отсутствии рекомендовано ставить '-'): ";
	std::getline(std::cin, AddElement);
	ea->Name = AddElement;

	std::cout << "Возраст: ";
	std::getline(std::cin, AddElement);
	ea->Age = AddElement;

	std::cout << "Семейное положение.";
	if (!FastInput_MS(ea, AddElement))
	{
		std::cout << "Семейное положение: ";
		std::getline(std::cin, AddElement);
		ea->MaritalStatus = AddElement;
	}
	std::cout << "Супруг(-а) (при отсутствии рекомендовано ставить '-'): ";
	std::getline(std::cin, AddElement);
	ea->Spouse = AddElement;

	std::cout << "Дети (при отсутствии рекомендовано ставить '-'): ";
	std::getline(std::cin, AddElement);
	ea->Kids = AddElement;

	std::cout << "Бюджет: ";
	FastInput_Budget(ea, AddElement);

	ea->next = current;
}

//Предложение быстрого ввода пятого поля элемента.
bool FastInput_MS(Employee*ea, std::string AddElement)
{
	std::cout << "Выберете один из следующих вариантов или введите свой, отказавшись." << std::endl << 
		"Холост -\t 1" << std::endl <<
		"Женат -\t\t 2" << std::endl <<
		"Не замужем -\t 3" << std::endl <<
		"Замужем -\t 4" << std::endl <<
		"Ввести свой -\t 5" << std::endl;
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (sm)
		{
		case '1':
			AddElement = "Холост";
			ea->MaritalStatus = AddElement;
			return true;
		case '2':
			AddElement = "Женат";
			ea->MaritalStatus = AddElement;
			return true;
		case '3':
			AddElement = "Не замужем";
			ea->MaritalStatus = AddElement;
			return true;
		case '4':
			AddElement = "Замужем";
			ea->MaritalStatus = AddElement;
			return true;
		case '5':
			return false;
		default:
			std::cout << "Введите один из вариантов выше (цифру). Повторите ввод:" << std::endl;
		}
	}
}

//Ввод восьмого поля элемента.
bool FastInput_Budget(Employee*ea, std::string AddElement)
{
	std::cout << "Выберете один из следующих вариантов:" << std::endl <<
		"Сбалансированный бюджет -\t 1" << std::endl <<
		"Профицитный бюджет -\t\t 2" << std::endl <<
		"Дефицитный бюджет -\t\t 3" << std::endl <<
		"Это ребенок, бюджета нет -\t 4" << std::endl;
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (sm)
		{
		case '1':
			AddElement = "Сбалансированный бюджет";
			ea->Budget = AddElement;
			return true;
		case '2':
			AddElement = "Профицитный бюджет";
			ea->Budget = AddElement;
			return true;
		case '3':
			AddElement = "Дефицитный бюджет";
			ea->Budget = AddElement;
			return true;
		case '4':
			AddElement = "-";
			ea->Budget = AddElement;
			return true;
		default:
			std::cout << "Введите один из вариантов выше (цифру). Повторите ввод:" << std::endl;
		}
	}
}

//Удаление элемента структуры.
void DeleteElement(Employee* search_del, const Employee* ed)
{
	while (search_del->next != ed)
	{
		search_del = search_del->next;
	}
	search_del->next = ed->next;
	delete ed;
}

//Первое действие меню.
void case1(Employee*& head)
{
	if (head != nullptr)
	{
		Employee* previous{ head }, * ea{};
		unsigned num{};
		std::cout << "После какого порядкового номера Вы хотите добавить элемент?" << std::endl;
		bool amount{ false };
		while (!amount)
		{
			num = int(GetNumber());
			amount = CheckAmountOfElements(head, num);
			if (amount == false)
			{
				std::cout << "Был возвращен указатель nullptr, такого элемента не существует." << std::endl;
			}
		}
		for (unsigned i = 1;i < num;i++)
		{
			previous = previous->next;
		}
		AddNewElement(previous, ea);
		std::cout << "Новый " << num + 1 << "-й элемент был добавлен." << std::endl;
	}	
	else
		AddHeadOfList(head);
}

//Второе действие меню.
void case2(Employee* &head)
{
	if (head != nullptr)
	{
		Employee* current{ head }, * search{ head };
		unsigned num{};
		std::cout << "Какой элемент по порядковому номеру Вы хотите удалить?" << std::endl;
		bool amount{ false };
		while (!amount)
		{
			num = int(GetNumber());
			amount = CheckAmountOfElements(head, num);
			if (amount == false)
			{
				std::cout << "Был возвращен указатель nullptr, такого элемента не существует." << std::endl;
			}
		}
		for (unsigned i = 1;i < num;i++)
		{
			current = current->next;
		}
		if (num != 1)
			DeleteElement(search, current);
		else
		{
			while (search->next != head)
				search = search->next;
			if (current->next != head)
			{
				search->next = head->next;
				head = head->next;
				delete current;
			}
			else
				head = nullptr;
		}
		std::cout << num << "-й элемент был удален." << std::endl;
	}
	else
		std::cerr << "Список пуст, данное действие невозможно." << std::endl;
}

//Третье действие меню.
void case3(const Employee* head)
{
	PrintList(head);
}

//Четвертое действие меню.
void case4(Employee* head)
{
	if (head != nullptr)
	{
		DefaultEmployee;
		Employee* tail{ head };
		std::cout << "Вы уверены?" << std::endl <<
			"Да - 1" << std::endl <<
			"Нет - 2" << std::endl;
		while (true)
		{
			char sm;
			std::cin >> sm;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (sm == '1')
			{
				do {
					tail->Surname = DEFAULT_EMPLOYEE.def_Surname;
					tail->MiddleName = DEFAULT_EMPLOYEE.def_MiddleName;
					tail->Name = DEFAULT_EMPLOYEE.def_Name;
					tail->Age = DEFAULT_EMPLOYEE.def_Age;
					tail->MaritalStatus = DEFAULT_EMPLOYEE.def_MaritalStatus;
					tail->Spouse = DEFAULT_EMPLOYEE.def_Spouce;
					tail->Kids = DEFAULT_EMPLOYEE.def_Kids;
					tail->Budget = DEFAULT_EMPLOYEE.def_Budget;
					tail = tail->next;
				} while (tail != head);
				std::cout << "\t Список был обновлен и приведен к предусмотренным значениям." << std::endl;
				break;
			}
			else if (sm == '2')
				break;
			else
				std::cout << "Ошибка ввода. Введите 1 или 2: \n";
		}
	}
	else
		std::cerr << "Список пуст, данное действие невозможно." << std::endl;
}
