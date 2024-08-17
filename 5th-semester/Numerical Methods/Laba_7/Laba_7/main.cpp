#include <iostream>
#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//Вывод информации о выданном задании.
	prePrint();
	printDash();
	int n_values[3]{}, m_values[3]{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			//Получение значений n и m (3 варианта пар).
			for (int i{}; i < 3; i++)
			{
				n_values[i] = get_n_m_values('n', i);
				m_values[i] = get_n_m_values('m', i);
				std::cout << std::endl;
			}
			//Вывод таблицы.
			printTable();
			for (int i{}; i < 3; i++)
				simpsonFormula(n_values[i], m_values[i]);
			break;
			//Выход из программы.
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	std::system("chcp 866 > nul");
	return 0;
}