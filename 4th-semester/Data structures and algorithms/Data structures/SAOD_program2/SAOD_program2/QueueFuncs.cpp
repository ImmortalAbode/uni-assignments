#include <iostream>
#include <string>
#include <limits> //��� std::cin.ignore()

#include "Queue.h"
#include "QueueFuncs.h"

//������������� ������ � ��������.
//�������� ������� �������.
bool IsEmpty(Queue qp)
{
	return qp.front == -1 ? true : false;
}
//�������� ������������� �������.
bool IsFull(Queue qp)
{
	return (qp.front == 0 && qp.rear == qp.size - 1 || qp.front == qp.rear + 1) ? true : false;
}
//���������� �������� � ����� �������.
void push(Queue& qp)
{
	if (!IsFull(qp))
	{
		if (qp.front == -1) qp.front = 0;
		qp.rear = (qp.rear + 1) % qp.size;
		double number{ getNumber() };
		qp.queue[qp.rear] = number;

		std::cout << "� ����� ������� ������� ��� �������� ����� �������." << std::endl;
	}
	else
	{
		std::cout << "���� ������� ���������, ������ �������� ����� �������." << std::endl;
	}
}
//�������� �������� �� ������ �������.
void pop(Queue& qp)
{
	if (!IsEmpty(qp))
	{
		if (qp.front == qp.rear)
		{
			qp.front = -1;
			qp.rear = -1;
		}
		else
		{
			qp.queue[qp.front] = 0;
			qp.front = (qp.front + 1) % qp.size;
			std::cout << "�� ������ ����� ������� ������� ��� ������ �������." << std::endl;
		}
	}
	else
	{
		std::cout << "���� ������� �����. �������� �������� ����������." << std::endl;
	}
}
//����� �� ����� �������� ��������� �������.
void print_queue(Queue qp)
{
	if (!IsEmpty(qp))
	{
		std::cout << "��������� front -> " << qp.front << std::endl;
		std::cout << "��������� rear -> " << qp.rear << std::endl;
		std::cout << "\t���� �������: " << std::endl;
		for (int i{ qp.front }; i != qp.rear; i = (i + 1) % qp.size)
		{
			std::cout << qp.queue[i] << " ";
		}
		std::cout << qp.queue[qp.rear] << std::endl;
	}
	else
		std::cout << "���� ������� �����!" << std::endl;
}
//�������� ���������.
void clear()
{
	std::cout << "�������� ���������..." << std::endl;
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

