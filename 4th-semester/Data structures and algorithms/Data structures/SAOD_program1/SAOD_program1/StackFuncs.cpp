#include <iostream>
#include <string>
#include <limits> //��� std::cin.ignore()
#include <cstdlib>//��� rand() � srand()
#include <ctime> //��� time()
#include <stdlib.h> //��� ������� exit()

#include "StackFuncs.h"
#include "Stack.h"

//������������� ������ �� ������.
//�������� ������� �����.
bool IsEmpty(Stack* sp)
{
	return sp == nullptr ? true : false;
}
//���������� ������ �������� � ������� ��������� �����.
void push(Stack*& sp, Stack*& dopsp)
{
	std::cout << "�� ������ 1 - ������������� �������� ������� ��� 2 - ������� ��� � ������� ���������������� �����? " << std::endl;;
	int choice{};
	while (true)
	{
		choice = getChoice();
		if (choice >= 1 && choice <= 2)
			break;
		std::cout << "�� ������ ������ ����� ����� �� 1 �� 2. ��������� ����: " << std::endl;
	}
	if (choice == 1)
	{
		double number{ getNumber() };
		push_back(sp, number);
		std::cout << "�� ������� ������ ��������� ����� ������� ��� �������� ����� �������." << std::endl;
	}
	else if (choice == 2)
	{
		if (dopsp == nullptr)
			std::cout << "� ����� ��������������� ����� ���� ��� ��� ������� ���������." << std::endl;
		else
		{
			push_pop_back(sp, dopsp);
			std::cout << "�� ������� ������ ��������� ����� ������� ��� �������� ������� �� ������� ���������������� �����." << std::endl;
		}
	}
}
//���������� ����� ���������� ��������� � ������� ��������� �����.
void push_random(Stack*& sp)
{
	//�������� rand() � ������������ ������� ��� �������� ��������������� ������������������� ��������� �����
	srand(static_cast<unsigned int>(time(0)));

	std::cout << "������� ��������� �� ������ ��������?" << std::endl;
	int count{ getChoice() };

	for (int i{}; i < count; i++)
	{
		double number{ getRandomNumber(-1000, 1000) };
		push_back(sp, number);
	}

	std::cout << "�� ������� ������ ��������� ����� ������� ���� ��������� ����� �������� (" << count << ")." << std::endl;
}
//�������� �������� �� ������� ��������� �����.
void pop(Stack*& sp, Stack*& dopsp)
{
	if (sp != nullptr)
	{
		std::cout << "�� ������ 1- ������������� ������� ������� (� ������������� ������)"
			<< " ��� 2 - �������� ��� � ������� ���������������� ����� ��������� ���������? " << std::endl;
		int choice{};
		while (true)
		{
			choice = getChoice();
			if (choice >= 1 && choice <= 2)
				break;
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 2. ��������� ����: " << std::endl;
		}
		if (choice == 1)
		{
			pop_back(sp);
			std::cout << "�� ������� ������ ��������� ����� ������� ��� ������ ������� (� ������������� ������). " << std::endl;
		}
		else if (choice == 2)
		{
			pop_push_back(sp, dopsp);
			std::cout << "�� ������� ������ ��������� ����� ������� ��� ������ ������� � ��������� �� ������� ���������������� �����. " << std::endl;
		}
	}
	else
		std::cout << "��� ���� ����, ������� ��������� ��� ����������!" << std::endl;
}
//����� �� ����� �������� ��������� ��������� �����.
void print_stack(Stack* sp)
{
	if (!IsEmpty(sp))
	{
		Stack* temp{ sp };
		std::cout << "\t��� ����: " << std::endl;
		while (temp->next != nullptr)
		{
			std::cout << "\t" << temp->next->data << std::endl;
			temp = temp->next;
		}
	}
	else
		std::cout << "��� ���� ����!" << std::endl;
}
//����� �� ����� �������� ��������� ���������������� �����.
void print_dopstack(Stack* dopsp)
{
	if (!IsEmpty(dopsp))
	{
		Stack* doptemp{ dopsp };
		std::cout << "\t��� ��������������� ����: " << std::endl;
		while (doptemp->next != nullptr)
		{
			std::cout << "\t" << doptemp->next->data << std::endl;
			doptemp = doptemp->next;
		}
	}
	else
		std::cout << "��� ��������������� ���� ����!" << std::endl;
}
//����������� ���� ����������� ���������� ������ � ���� ��� ���������� ���������.
void clear(Stack*& sp, Stack*& dopsp)
{
	if (sp != nullptr)
		while (sp != nullptr)
			pop_back(sp);

	//������� pop_back ���� �������� ��� sp, �� ��� dopsp ��� ���������� ����������.
	if (dopsp != nullptr)
		while (dopsp != nullptr)
			pop_back(dopsp);

	std::cout << "��� ����������� ���������� ������ ���� ������� ���������� � ����. �������� ���������..." << std::endl;
}

//����� ������� ����������/�������� �������� �� �����, �������� �� ������ � ������ ��� �����������.
void push_back(Stack*& sp, double number)
{
	try
	{
		if (sp == nullptr)
		{
			sp = new Stack;
			sp->next = new Stack;
			Stack* temp{ sp->next };
			temp->data = number;
			temp->next = nullptr;
		}
		else
		{
			Stack* temp{ sp->next };
			sp->next = new Stack;
			sp->next->data = number;
			sp->next->next = temp;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		if (sp != nullptr)
			while (sp != nullptr)
				pop_back(sp);
		exit(-1);
	}
}
void pop_back(Stack*& sp)
{
	Stack* temp{ sp->next };
	sp->next = temp->next;
	temp->next = nullptr;
	delete temp;
	if (sp->next == nullptr)
	{
		delete sp;
		sp = nullptr;
	}
}
void push_pop_back(Stack*& sp, Stack*& dopsp)
{
	Stack* doptemp{ dopsp->next };
	dopsp->next = doptemp->next;
	Stack* temp{ sp->next };
	sp->next = doptemp;
	doptemp->next = temp;
	if (dopsp->next == nullptr)
	{
		delete dopsp;
		dopsp = nullptr;
	}
}
void pop_push_back(Stack*& sp, Stack*& dopsp)
{
	Stack* temp{ sp->next };
	sp->next = temp->next;
	if (dopsp == nullptr)
	{
		dopsp = new Stack;
		dopsp->next = temp;
		temp->next = nullptr;
	}
	else
	{
		Stack* doptemp{ dopsp->next };
		dopsp->next = temp;
		temp->next = doptemp;
	}
	if (sp->next == nullptr)
	{
		delete sp;
		sp = nullptr;
	}
}

//��������� ������ ����� (����� ��� ������ �������� �����)
int getChoice()
{
	while (true)
	{
		std::string tempStr{};
		std::cout << "��� �����: ";
		std::getline(std::cin, tempStr);
		if (!checkStrIsNumeric(tempStr))
		{
			std::cin.clear();
			std::cout << "������ �����. �� ������ ������ ����������� �����. ��������� ����:\n";
		}
		else
		{
			return convertStrToInt(tempStr);
		}
	}
}
//��������� �������� ������ �� ����������� �������������� � �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//����������� ������ � �����.
int convertStrToInt(std::string const& convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i);
	return static_cast<int>(number);
}
//��������� ����� (����� ��� ���������� �������� � ����).
double getNumber()
{
	while (true)
	{
		double a{};
		std::cout << "������� �����: ";
		std::cin >> a;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�� ������ ������ �����. ��������� ����: " << std::endl;
		}
		else
		{
			std::cout << "���� �� ������ ������ ����� � ��������� ������, �� ������������ �������, �� ��� ���� ��������������� "
				<< "� ������ �����, � �������� ������ ����� �����." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return a;
		}
	}
}
//�������� ����
double getRandomNumber(float min, float max) //��������� ���������� ����� ����� ��������� min � max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<double>(rand() * fraction * (max - min + 1) + min);
}
