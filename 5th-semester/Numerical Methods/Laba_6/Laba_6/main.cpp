#include <iostream>

#include "myfuncs.h"
#include "Constants.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//Вывод информации о задании.
	prePrint();
	printDash();
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//Вывод таблицы.
			printTable();
			formulas_for_n_4();
			formulas_for_n_8();
			break;
		case '2':
			std::cout << "Закрытие программы . . ." << std::endl;
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	std::system("chcp 866 > nul");
	return 0;
}