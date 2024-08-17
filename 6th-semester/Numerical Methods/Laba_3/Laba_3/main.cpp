#include <iostream>
#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	std::system("color F0");
	//Вывод информации о выданном задании.
	PrePrint();
	PrintDash();
	//Значение S для неявной схемы метода сеток.
	double S{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//Выполнение требования, выданного к заданию.
		case '1':

			S = getSvalue();
			PrintDash();
			std::cout << std::endl;
			std::cout << "Результаты вычислений при S = " << S << std::endl;
			std::cout << "Метод сеток. Явная схема:" << std::endl;
			ExplicitSchema();
			std::cout << std::endl;
			std::cout << "Метод сеток. Неявная схема:" << std::endl;
			ImplicitSchema(S);

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
