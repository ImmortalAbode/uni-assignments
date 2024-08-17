#include <iostream>

#include "constants.h"
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//Вывод информации о задании.
	prePrint();
	printDash();
	//Объявление заданной точности эпсилон, дельта и начального приближения x0.
	double epsilon{}, deltha{}, approximate_x0{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//Задание точности эпсилон pow(10, -3) и дельты pow(10, -3).
			epsilon = 0.001;
			deltha = 0.001;
			std::cout << "Значение эпсилон по умолчанию: " << epsilon << std::endl;
			std::cout << "Значение дельты по умолчанию: " << deltha << std::endl;
			//Задание начального приближения.
			getInitOfApproximation(approximate_x0);
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, deltha, approximate_x0);
			//Метод Ньютона (МН).
			NewtonMethod(epsilon, deltha, approximate_x0);
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonMethod(epsilon, deltha, approximate_x0);

			printDash();

			//Задание точности эпсилон pow(10, -5) и дельты pow(10, -5).
			epsilon = 0.00001;
			deltha = 0.00001;
			std::cout << "Значение эпсилон по умолчанию: " << epsilon << std::endl;
			std::cout << "Значение дельты по умолчанию: " << epsilon << std::endl;
			//Задание начального приближения.
			std::cout << "Заданное начальное приближение: " << std::endl;
			std::cout << "x_(0) = " << approximate_x0 << std::endl;
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, deltha, approximate_x0);
			//Метод Ньютона (МН).
			NewtonMethod(epsilon, deltha, approximate_x0);
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonMethod(epsilon, deltha, approximate_x0);
			break;
		case '2':
			//Задание точности эпсилон.
			epsilon = getEpsilon();
			//Задание точности дельта.
			deltha = getDeltha();
			//Задание начального приближения.
			getInitOfApproximation(approximate_x0);
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, deltha, approximate_x0);
			//Метод Ньютона (МН).
			NewtonMethod(epsilon, deltha, approximate_x0);
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonMethod(epsilon, deltha, approximate_x0);
			break;
		case '3':
			std::cout << "Закрытие программы . . ." << std::endl;
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}