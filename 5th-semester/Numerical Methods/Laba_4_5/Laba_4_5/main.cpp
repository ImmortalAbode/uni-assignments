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
	//Выбор трех значений, принадлежащих отрезку [a; b]
	long double user_values_of_X[3]{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//Ввод пользователем 3-х значений, принадлежащих отрезку [a; b]
			getValuesXFromUser(user_values_of_X);
			//Вывод информации о полученных значениях.
			printDash();
			std::cout << "Из отрезка [" << a << ";" << b << "] были выбраны следующие значения:" << std::endl;
			std::cout << "Первое значение x: " << user_values_of_X[0] << std::endl;
			std::cout << "Второе значение x: " << user_values_of_X[1] << std::endl;
			std::cout << "Третье значение x: " << user_values_of_X[2] << std::endl;

			//Вывод таблицы для интерполирования.
			std::cout << std::endl << "Интерполирование" << std::endl;
			printTableInterpolation();
			interpolation_formulas(user_values_of_X);

			std::cout << std::endl;

			//Вывод таблицы для численного дифференцирования.
			std::cout << std::endl << "Численное дифференцирование" << std::endl;
			printTableNumericalDefferentiation();
			numerical_differentation_formulas(user_values_of_X);

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