#include <iostream>
#include <string>
#include <limits> //Для std::cin.ignore()
#include <cstdlib>//Для rand() и srand()
#include <ctime> //Для time()
#include <stdlib.h> //для функции exit()

#include "StackFuncs.h"
#include "Stack.h"

//Инициализация работы со стеком.
//Проверка пустоты стека.
bool IsEmpty(Stack* sp)
{
	return sp == nullptr ? true : false;
}
//Добавление одного элемента в вершину основного стека.
void push(Stack*& sp, Stack*& dopsp)
{
	std::cout << "Вы хотите 1 - действительно добавить элемент или 2 - выбрать его с вершины вспомогательного стека? " << std::endl;;
	int choice{};
	while (true)
	{
		choice = getChoice();
		if (choice >= 1 && choice <= 2)
			break;
		std::cout << "Вы должны ввести целое число от 1 до 2. Повторите ввод: " << std::endl;
	}
	if (choice == 1)
	{
		double number{ getNumber() };
		push_back(sp, number);
		std::cout << "На вершину вашего основного стека успешно был добавлен новый элемент." << std::endl;
	}
	else if (choice == 2)
	{
		if (dopsp == nullptr)
			std::cout << "В вашем вспомогательном стеке пока что нет никаких элементов." << std::endl;
		else
		{
			push_pop_back(sp, dopsp);
			std::cout << "На вершину вашего основного стека успешно был добавлен элемент из вершины вспомогательного стека." << std::endl;
		}
	}
}
//Добавление сразу нескольких элементов в вершину основного стека.
void push_random(Stack*& sp)
{
	//Привязка rand() к календарному времени для создания неповторяющихся последовательностей случайных чисел
	srand(static_cast<unsigned int>(time(0)));

	std::cout << "Сколько элементов Вы хотите добавить?" << std::endl;
	int count{ getChoice() };

	for (int i{}; i < count; i++)
	{
		double number{ getRandomNumber(-1000, 1000) };
		push_back(sp, number);
	}

	std::cout << "На вершину вашего основного стека успешно были добавлены новые элементы (" << count << ")." << std::endl;
}
//Удаление элемента из вершины основного стека.
void pop(Stack*& sp, Stack*& dopsp)
{
	if (sp != nullptr)
	{
		std::cout << "Вы хотите 1- действительно удалить элемент (с освобождением памяти)"
			<< " или 2 - включить его в вершину вспомогательного стека удаленных элементов? " << std::endl;
		int choice{};
		while (true)
		{
			choice = getChoice();
			if (choice >= 1 && choice <= 2)
				break;
			std::cout << "Вы должны ввести целое число от 1 до 2. Повторите ввод: " << std::endl;
		}
		if (choice == 1)
		{
			pop_back(sp);
			std::cout << "Из вершины вашего основного стека успешно был удален элемент (с освобождением памяти). " << std::endl;
		}
		else if (choice == 2)
		{
			pop_push_back(sp, dopsp);
			std::cout << "Из вершины вашего основного стека успешно был удален элемент и перемещен на вершину вспомогательного стека. " << std::endl;
		}
	}
	else
		std::cout << "Ваш стек пуст, сначала заполните его элементами!" << std::endl;
}
//Вывод на экран текущего состояния основного стека.
void print_stack(Stack* sp)
{
	if (!IsEmpty(sp))
	{
		Stack* temp{ sp };
		std::cout << "\tВаш стек: " << std::endl;
		while (temp->next != nullptr)
		{
			std::cout << "\t" << temp->next->data << std::endl;
			temp = temp->next;
		}
	}
	else
		std::cout << "Ваш стек пуст!" << std::endl;
}
//Вывод на экран текущего состояния вспомогательного стека.
void print_dopstack(Stack* dopsp)
{
	if (!IsEmpty(dopsp))
	{
		Stack* doptemp{ dopsp };
		std::cout << "\tВаш вспомогательный стек: " << std::endl;
		while (doptemp->next != nullptr)
		{
			std::cout << "\t" << doptemp->next->data << std::endl;
			doptemp = doptemp->next;
		}
	}
	else
		std::cout << "Ваш вспомогательный стек пуст!" << std::endl;
}
//Возвращение всей динамически выделенной памяти в кучу при завершении программы.
void clear(Stack*& sp, Stack*& dopsp)
{
	if (sp != nullptr)
		while (sp != nullptr)
			pop_back(sp);

	//Функция pop_back была написана для sp, но для dopsp она совершенно аналогична.
	if (dopsp != nullptr)
		while (dopsp != nullptr)
			pop_back(dopsp);

	std::cout << "Вся динамически выделенная память была успешно возвращена в кучу. Закрытие программы..." << std::endl;
}

//Общие функции добавления/удаления элемента из стека, переноса из одного в другой для наглядности.
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
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
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
//Создание ГПСЧ
double getRandomNumber(float min, float max) //Генерация случайного числа между заданными min и max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<double>(rand() * fraction * (max - min + 1) + min);
}
