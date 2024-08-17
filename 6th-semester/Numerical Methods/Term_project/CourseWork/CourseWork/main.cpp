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
	long double epsilon{};
	bool cycle{ true };
	while (cycle)
	{
		PrintMenu();
		switch (GetChoice())
		{
			//Выполнение требования, выданного к заданию.
		case '1':

			PrintDash();
			std::cout << "Выполнение алгоритма Лобачевского-Греффе." << std::endl;
			epsilon = getEpsilon();
			LobachevskyGraeffeAlgorithm(epsilon);
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
