#include <iostream> // для консоли
#include <string> // для строк

#include "WorkWithFunc.h"
#include "RPN.h"

#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	PrePrint();
	Func* func = new Func{};					//Структура для хранения данных функции.
	Stack* stack_signs = new Stack{};			//Стек, который хранит операторы, чтобы выгрузить их своевременно в ОПН(ОПЗ).
	OutString* RPN_string = new OutString{};	//Структура для построения ОПН (ОПЗ).

	int* result_of_function{ nullptr };			//Динамический массив, хранит вычисленные значения функции.

	bool cycle{ true };
	while (cycle)
	{
		MenuPrint();
		switch (getChoice())
		{
		case '1'://Получить значение k-значной логики.
			getNumberK(func);
			ClearSomeStructs(result_of_function, RPN_string);//Очищаем заполненные чем-то структуры, если создаем новый пример.
			break;
		case '2'://Получить кол-во существенных переменных функции.
			getNumberN(func);
			ClearSomeStructs(result_of_function, RPN_string);//Очищаем заполненные чем-то структуры, если создаем новый пример.
			break;
		case '3'://Получаем саму функцию, если заданы k и n.
			if (func->k != 0 && func->n != 0)
			{
				getFunction(func);
				ClearSomeStructs(result_of_function, RPN_string);//Очищаем заполненные чем-то структуры перед работой с функцией.
			}
			else
				std::cout << "Сначала задайте число k и число n" << std::endl;
			break;
		case '4'://Получение значений функции и их вывод.
			if (func->func != "")
				getValuesOfFunc(func, stack_signs, RPN_string, result_of_function);
			else
				std::cout << "Сначала задайте функцию." << std::endl;
			break;
		case '5'://Получение второй формы функции.
			if (result_of_function != nullptr)
				getSKNFform(func, result_of_function);
			else
				std::cout << "Сначала посчитайте функцию." << std::endl;
			break;
		case '6'://Проверка сохранения определенного множества функцией.
			if (result_of_function != nullptr)
				getSaveData(func, result_of_function);
			else
				std::cout << "Сначала посчитайте функцию." << std::endl;
			break;
		case '7'://Выход из программы.
			cycle = false;
			clearAllStructs(func, stack_signs, RPN_string);
			if (result_of_function != nullptr) delete[] result_of_function;
			std::cout << "Вся выделенная память была возвращена в кучу. Завершение программы . . ." << std::endl;
			break;
		}
		std::cout << std::string(125, '-') << std::endl << std::endl;
	}
	return 0;
}