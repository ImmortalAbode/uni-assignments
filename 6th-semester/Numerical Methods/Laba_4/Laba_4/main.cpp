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
	//Значение a для метода сеток.
	double a{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//Выполнение требования, выданного к заданию.
		case '1':

			//a = GetaValue();
			PrintDash();
			std::cout << std::endl;
			//std::cout << "Результаты вычислений при a = " << a << std::endl;
			std::cout << "Метод сеток:" << std::endl;
			GridMethod(1);

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
