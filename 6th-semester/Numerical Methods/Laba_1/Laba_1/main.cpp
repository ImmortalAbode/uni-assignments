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
	double epsilon{};
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
			std::cout << "Приближенное решение задачи Коши методом Эйлера, Рунге-Кутта 4-ого порядка точности и методом Адамса." << std::endl;
			std::cout << "Рассчеты произведены при n = 10 без двойного пересчета в методе Рунге-Кутта." << std::endl;
			PrintFirstSecondTable(10);

			PrintDash();
			std::cout << "Приближенное решение задачи Коши методом Эйлера, Рунге-Кутта 4-ого порядка точности и методом Адамса." << std::endl;
			std::cout << "Рассчеты произведены при n = 20 без двойного пересчета в методе Рунге-Кутта." << std::endl;
			PrintFirstSecondTable(20);

			PrintDash();
			epsilon = getEpsilon();
			PrintDash();
			std::cout << "Приближенное решение задачи Коши методом Рунге-Кутта 4-ого порядка точности." << std::endl;
			std::cout << "Рассчеты произведены при n = 10 с двойным пересчетом и выбранной точностью epsilon = " << epsilon << "." << std::endl;
			PrintThirdFourthTable(10, epsilon);

			PrintDash();
			epsilon = getEpsilon();
			PrintDash();
			std::cout << "Приближенное решение задачи Коши методом Рунге-Кутта 4-ого порядка точности." << std::endl;
			std::cout << "Рассчеты произведены при n = 20 с двойным пересчетом и выбранной точностью epsilon = " << epsilon << "." << std::endl;
			PrintThirdFourthTable(20, epsilon);

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
