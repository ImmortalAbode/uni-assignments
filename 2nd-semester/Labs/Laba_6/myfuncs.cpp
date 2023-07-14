#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ArrayEightStrings.h"
#include "mystructs.h"
#include "constants.h"
#include "myfuncs.h"
//��������, ����� � �������� ���� ����� 8 ���e�.
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
		std::cout << count << "-� ������� ����� ������������ ���������� ������ ��������������� ����." << std::endl;
		return false;
	}
	return true;
}

//����������� �������������� ���� �������� �� ���� � ����������� �� � ���������.
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

//��������� ����, ���� ������ ������ � ���������� ������� ��������, ���� ���� ������.
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
			std::cout << "��� ���� ������. ������ ������ ������ �������?" << std::endl <<
				"�� - 1" << std::endl <<
				"��� - 0" << std::endl;
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
					std::cerr << "������� 0 ��� 1. ��������� ����: ";
			}
		}
	}
	return true;
}

//��������� ������ �������� �� ��������� � ��������������� ����.
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

//���� ��������� �� ���������� �� �����-�� �������, �� ��������� ������ �� �������.
void AddHeadOfList(Employee*& head)
{
	std::string AddDataHead{};
	head = new Employee;
	std::cout << "������� ������ ������ ��������:" << std::endl;
	std::cout << "�������: ";
	std::getline(std::cin, AddDataHead);
	head->Surname = AddDataHead;

	std::cout << "���: ";
	std::getline(std::cin, AddDataHead);
	head->MiddleName = AddDataHead;

	std::cout << "�������� (��� ���������� ������������� ������� '-'): ";
	std::getline(std::cin, AddDataHead);
	head->Name = AddDataHead;

	std::cout << "�������: ";
	std::getline(std::cin, AddDataHead);
	head->Age = AddDataHead;

	std::cout << "�������� ���������.";
	if (!FastInput_MS(head, AddDataHead))
	{
		std::cout << "�������� ���������: ";
		std::getline(std::cin, AddDataHead);
		head->MaritalStatus = AddDataHead;
	}
	std::cout << "������(-�) (��� ���������� ������������� ������� '-'): ";
	std::getline(std::cin, AddDataHead);
	head->Spouse = AddDataHead;

	std::cout << "���� (��� ���������� ������������� ������� '-'): ";
	std::getline(std::cin, AddDataHead);
	head->Kids = AddDataHead;

	std::cout << "������.";
	FastInput_Budget(head, AddDataHead);

	head->next = head;
	std::cout << "����� ������ ������� ��� ��������." << std::endl;
}

//�������� ������� �������� ��������� �� �����.
bool loadingList(const std::string fileName, Employee*& head)
{
	std::ifstream Data_file(fileName);
	if (!Data_file)
	{
		std::cerr << "�� ������� ������� ����!" << std::endl;
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

//������� �������� ��������� � ����.
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
			std::cout << "������� " << clean_ptr->Surname << ' ' << clean_ptr->MiddleName << ' ' << clean_ptr->Name << ",... �������� � ������ �� ����������� ������." << std::endl;
			delete clean_ptr;
			if (tail == head)
				break;
		}
	}

	Data_file.close();
	return true;
}

//���������� ��������� ������������� ����� �������� � ���������� ��������� ���������.
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

//����� ��������� �� �������.
void PrintList(const Employee* head)
{
	const Employee* tail{ head };
	if (head != nullptr)
	{
		int index_number{};
		std::cout << "____________________ ��� ������: ____________________" << std::endl;
		do {
			index_number++;
			std::cout << index_number << ") " << tail->Surname << ";" << tail->MiddleName << ";" << tail->Name << ";" << tail->Age << ";" << tail->MaritalStatus << 
				";" << tail->Spouse << ";" << tail->Kids << ";" << tail->Budget << std::endl;
			tail = tail->next;
		} while (tail != head);
	}
	else
		std::cout << "������ ����." << std::endl;
}

//��������� ������ ������������.
char getCase()
{
	MenuForChoices();
	while (true)
	{
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
		{
			std::cout << "������ �����, ������� ������ ����� ������ ������. ��������� ����:" << std::endl;
		}
	}
}

//���� ��������� ��������.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) �������� �������� ������� � ������ �� ����������� ������. " << std::endl <<
		"2) ������� �������� ������� �� ������ �� ����������� ������." << std::endl <<
		"3) ������ ���� ��������� (����� �� �������)." << std::endl <<
		"4) ��������� ���� ��������� ��������������� ��������." << std::endl <<
		"5) �����." << std::endl;
}

//��������� ������������ ����� ��� �����-�� ����.
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
			std::cout << "������ �����, �� ����� �� �����. ��������� ����:\n";
		}
		else if (num != int(num))
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�� ����� �� ����������� �����. ��������� ����:\n ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
	}
}

//���������� ������ �������� � ���������.
void AddNewElement(Employee*& previous, Employee *ea)
{
	std::string AddElement{};
	Employee* current{};

	ea = new Employee;
	current = previous->next;
	previous->next = ea;
	std::cout << "������� ������ ������ ��������:" << std::endl;

	std::cout << "�������: ";
	std::getline(std::cin, AddElement);
	ea->Surname = AddElement;

	std::cout << "���: ";
	std::getline(std::cin, AddElement);
	ea->MiddleName = AddElement;

	std::cout << "�������� (��� ���������� ������������� ������� '-'): ";
	std::getline(std::cin, AddElement);
	ea->Name = AddElement;

	std::cout << "�������: ";
	std::getline(std::cin, AddElement);
	ea->Age = AddElement;

	std::cout << "�������� ���������.";
	if (!FastInput_MS(ea, AddElement))
	{
		std::cout << "�������� ���������: ";
		std::getline(std::cin, AddElement);
		ea->MaritalStatus = AddElement;
	}
	std::cout << "������(-�) (��� ���������� ������������� ������� '-'): ";
	std::getline(std::cin, AddElement);
	ea->Spouse = AddElement;

	std::cout << "���� (��� ���������� ������������� ������� '-'): ";
	std::getline(std::cin, AddElement);
	ea->Kids = AddElement;

	std::cout << "������: ";
	FastInput_Budget(ea, AddElement);

	ea->next = current;
}

//����������� �������� ����� ������ ���� ��������.
bool FastInput_MS(Employee*ea, std::string AddElement)
{
	std::cout << "�������� ���� �� ��������� ��������� ��� ������� ����, �����������." << std::endl << 
		"������ -\t 1" << std::endl <<
		"����� -\t\t 2" << std::endl <<
		"�� ������� -\t 3" << std::endl <<
		"������� -\t 4" << std::endl <<
		"������ ���� -\t 5" << std::endl;
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (sm)
		{
		case '1':
			AddElement = "������";
			ea->MaritalStatus = AddElement;
			return true;
		case '2':
			AddElement = "�����";
			ea->MaritalStatus = AddElement;
			return true;
		case '3':
			AddElement = "�� �������";
			ea->MaritalStatus = AddElement;
			return true;
		case '4':
			AddElement = "�������";
			ea->MaritalStatus = AddElement;
			return true;
		case '5':
			return false;
		default:
			std::cout << "������� ���� �� ��������� ���� (�����). ��������� ����:" << std::endl;
		}
	}
}

//���� �������� ���� ��������.
bool FastInput_Budget(Employee*ea, std::string AddElement)
{
	std::cout << "�������� ���� �� ��������� ���������:" << std::endl <<
		"���������������� ������ -\t 1" << std::endl <<
		"����������� ������ -\t\t 2" << std::endl <<
		"���������� ������ -\t\t 3" << std::endl <<
		"��� �������, ������� ��� -\t 4" << std::endl;
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (sm)
		{
		case '1':
			AddElement = "���������������� ������";
			ea->Budget = AddElement;
			return true;
		case '2':
			AddElement = "����������� ������";
			ea->Budget = AddElement;
			return true;
		case '3':
			AddElement = "���������� ������";
			ea->Budget = AddElement;
			return true;
		case '4':
			AddElement = "-";
			ea->Budget = AddElement;
			return true;
		default:
			std::cout << "������� ���� �� ��������� ���� (�����). ��������� ����:" << std::endl;
		}
	}
}

//�������� �������� ���������.
void DeleteElement(Employee* search_del, const Employee* ed)
{
	while (search_del->next != ed)
	{
		search_del = search_del->next;
	}
	search_del->next = ed->next;
	delete ed;
}

//������ �������� ����.
void case1(Employee*& head)
{
	if (head != nullptr)
	{
		Employee* previous{ head }, * ea{};
		unsigned num{};
		std::cout << "����� ������ ����������� ������ �� ������ �������� �������?" << std::endl;
		bool amount{ false };
		while (!amount)
		{
			num = int(GetNumber());
			amount = CheckAmountOfElements(head, num);
			if (amount == false)
			{
				std::cout << "��� ��������� ��������� nullptr, ������ �������� �� ����������." << std::endl;
			}
		}
		for (unsigned i = 1;i < num;i++)
		{
			previous = previous->next;
		}
		AddNewElement(previous, ea);
		std::cout << "����� " << num + 1 << "-� ������� ��� ��������." << std::endl;
	}	
	else
		AddHeadOfList(head);
}

//������ �������� ����.
void case2(Employee* &head)
{
	if (head != nullptr)
	{
		Employee* current{ head }, * search{ head };
		unsigned num{};
		std::cout << "����� ������� �� ����������� ������ �� ������ �������?" << std::endl;
		bool amount{ false };
		while (!amount)
		{
			num = int(GetNumber());
			amount = CheckAmountOfElements(head, num);
			if (amount == false)
			{
				std::cout << "��� ��������� ��������� nullptr, ������ �������� �� ����������." << std::endl;
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
		std::cout << num << "-� ������� ��� ������." << std::endl;
	}
	else
		std::cerr << "������ ����, ������ �������� ����������." << std::endl;
}

//������ �������� ����.
void case3(const Employee* head)
{
	PrintList(head);
}

//��������� �������� ����.
void case4(Employee* head)
{
	if (head != nullptr)
	{
		DefaultEmployee;
		Employee* tail{ head };
		std::cout << "�� �������?" << std::endl <<
			"�� - 1" << std::endl <<
			"��� - 2" << std::endl;
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
				std::cout << "\t ������ ��� �������� � �������� � ��������������� ���������." << std::endl;
				break;
			}
			else if (sm == '2')
				break;
			else
				std::cout << "������ �����. ������� 1 ��� 2: \n";
		}
	}
	else
		std::cerr << "������ ����, ������ �������� ����������." << std::endl;
}
