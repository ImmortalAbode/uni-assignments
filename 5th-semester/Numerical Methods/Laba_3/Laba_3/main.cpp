#include <iostream>

#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");

	//Вывод информации о задании.
	prePrint();
	printDash();
	//Объявление заданной точности эпсилон, дельта и массива, содержащего значения начального приближения.
	double epsilon{}, deltha{}, approximate_mass[2]{};
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
			getInitOfApproximation_v2(approximate_mass);
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, deltha, approximate_mass);
			//Метод Ньютона (МН).
			NewtonMethod(epsilon, deltha, approximate_mass);
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonMethod(epsilon, deltha, approximate_mass);

			printDash();

			//Задание точности эпсилон pow(10, -5) и дельты pow(10, -5).
			epsilon = 0.00001;
			deltha = 0.00001;
			std::cout << "Значение эпсилон по умолчанию: " << epsilon << std::endl;
			std::cout << "Значение дельты по умолчанию: " << epsilon << std::endl;
			//Задание начального приближения.
			std::cout << "Заданное начальное приближение: " << std::endl;
			std::cout << "x^(0) = " << approximate_mass[0] << std::endl;
			std::cout << "y^(0) = " << approximate_mass[1] << std::endl;
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, deltha, approximate_mass);
			//Метод Ньютона (МН).
			NewtonMethod(epsilon, deltha, approximate_mass);
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonMethod(epsilon, deltha, approximate_mass);
			break;
		case '2':
			//Задание точности эпсилон.
			epsilon = getEpsilon();
			//Задание точности дельта.
			deltha = getDeltha();
			//Задание начального приближения.
			getInitOfApproximation(approximate_mass);
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, deltha, approximate_mass);
			//Метод Ньютона (МН).
			NewtonMethod(epsilon, deltha, approximate_mass);
			//Модифицированный метод Ньютона (ММН).
			modifiedNewtonMethod(epsilon, deltha, approximate_mass);
			break;
		case '3':
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