#include <iostream>

#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//Вывод информации о задании.
	prePrint();
	printDash();
	//Объявление заданной точности эпсилон и массива, содержащего значения начального приближения.
	double epsilon{}, approximate_mass[3]{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		printMenu();
		switch (getChoice())
		{
		case '1':
			//Задание точности эпсилон pow(10, -3).
			epsilon = 0.001;
			std::cout << "Значение эпсилон по умолчанию: " << epsilon << std::endl;
			//Задание начального приближения.
			getInitOfApproximation(approximate_mass);
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, approximate_mass);
			//Метод Зейделя (МЗ).
			seidelMethod(epsilon, approximate_mass);
			//Метод релаксации (ослабления).
			relaxationMethod(epsilon, approximate_mass);

			printDash();

			//Задание точности эпсилон pow(10, -5).
			epsilon = 0.00001;
			std::cout << "Значение эпсилон по умолчанию: " << epsilon << std::endl;
			//Задание начального приближения.
			std::cout << "Заданное начальное приближение: " << std::endl;
			std::cout << "x_(0) = " << approximate_mass[0] << std::endl;
			std::cout << "y_(0) = " << approximate_mass[1] << std::endl;
			std::cout << "z_(0) = " << approximate_mass[2] << std::endl;
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, approximate_mass);
			//Метод Зейделя (МЗ).
			seidelMethod(epsilon, approximate_mass);
			//Метод релаксации (ослабления).
			relaxationMethod(epsilon, approximate_mass);
			break;
		case '2':
			//Задание точности эпсилон.
			epsilon = getEpsilon();
			//Задание начального приближения.
			getInitOfApproximation(approximate_mass);
			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, approximate_mass);
			//Метод Зейделя (МЗ).
			seidelMethod(epsilon, approximate_mass);
			//Метод релаксации (ослабления).
			relaxationMethod(epsilon, approximate_mass);
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