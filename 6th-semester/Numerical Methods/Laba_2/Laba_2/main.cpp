#include <iostream>

#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//std::system("color F0");
	//Вывод информации о выданном задании.
	PrePrint();
	PrintDash();
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//Выполнение требования, выданного к заданию.
		case '1':

			PrintDash();
			std::cout << "Приближенное решение краевой задачи для обыкновенного дифференциального уравнения второго порядка методом прогонки." << std::endl;
			std::cout << "Рассчеты произведены при n = 10." << std::endl;
			SweepMethod(10);

			PrintDash();
			std::cout << "Приближенное решение краевой задачи для обыкновенного дифференциального уравнения второго порядка методом прогонки." << std::endl;
			std::cout << "Рассчеты произведены при n = 20." << std::endl;
			SweepMethod(20);
			break;
		case '2':
			cycle = false;
			break;
		default:;
		}
		PrintDash();
	}
	std::system("chcp 866 > nul");
	return 0;
}
