#include <iostream>
#include <string>
#include <limits> //Для std::cin.ignore()

#include "Queue.h"
#include "QueueFuncs.h"

//Инициализация работы с очередью.
//Проверка пустоты очереди.
bool IsEmpty(Queue qp)
{
	return qp.front == -1 ? true : false;
}
//Проверка заполненности очереди.
bool IsFull(Queue qp)
{
	return (qp.front == 0 && qp.rear == qp.size - 1 || qp.front == qp.rear + 1) ? true : false;
}
//Добавление элемента в конец очереди.
void push(Queue& qp)
{
	if (!IsFull(qp))
	{
		if (qp.front == -1) qp.front = 0;
		qp.rear = (qp.rear + 1) % qp.size;
		double number{ getNumber() };
		qp.queue[qp.rear] = number;

		std::cout << "В конец очереди успешно был добавлен новый элемент." << std::endl;
	}
	else
	{
		std::cout << "Ваша очередь заполнена, нельзя добавить новый элемент." << std::endl;
	}
}
//Удаление элемента из начала очереди.
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
			std::cout << "Из начала вашей очереди успешно был удален элемент." << std::endl;
		}
	}
	else
	{
		std::cout << "Ваша очередь пуста. Удаление элемента невозможно." << std::endl;
	}
}
//Вывод на экран текущего состояния очереди.
void print_queue(Queue qp)
{
	if (!IsEmpty(qp))
	{
		std::cout << "Указатель front -> " << qp.front << std::endl;
		std::cout << "Указатель rear -> " << qp.rear << std::endl;
		std::cout << "\tВаша очередь: " << std::endl;
		for (int i{ qp.front }; i != qp.rear; i = (i + 1) % qp.size)
		{
			std::cout << qp.queue[i] << " ";
		}
		std::cout << qp.queue[qp.rear] << std::endl;
	}
	else
		std::cout << "Ваша очередь пуста!" << std::endl;
}
//Закрытие программы.
void clear()
{
	std::cout << "Закрытие программы..." << std::endl;
}


//Получение целого числа (нужно для выбора операции стека)
int getChoice()
{
	while (true)
	{
		std::string tempStr{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, tempStr);
		if (!checkStrIsNumeric(tempStr))
		{
			std::cin.clear();
			std::cout << "Ошибка ввода. Вы должны ввести натуральное число. Повторите ввод:\n";
		}
		else
		{
			return convertStrToInt(tempStr);
		}
	}
}
//Проверяет вводимую строку на возможность преобразования в число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//Преобразует строку в число.
int convertStrToInt(std::string const& convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i);
	return static_cast<int>(number);
}
//Получение числа (нужно для добавления элемента в стек).
double getNumber()
{
	while (true)
	{
		double a{};
		std::cout << "Введите число: ";
		std::cin >> a;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Вы должны ввести число. Повторите ввод: " << std::endl;
		}
		else
		{
			std::cout << "Если Вы хотели ввести число с плавающей точкой, но использовали запятую, то она была проигнорирована "
				<< "в потоке ввода, а осталась только целая часть." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return a;
		}
	}
}

