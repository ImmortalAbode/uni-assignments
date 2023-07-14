#include <iostream>
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time() и clock()

#include "myarray.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//Привязка ГПСЧ (rand()) к календарному времени для создания неповторяющихся последовательностей случайных чисел
	srand(static_cast<unsigned int>(time(0)));

	Array mass{};

	bool create{ false };
	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			if (!create)
			{
				create = true;
				CreateArray(mass, -1);
			}
			else
			{
				std::cout << "Массив уже был создан!" << std::endl;
				std::cout << "Вы хотите заново создать массив? (введите количество элементов или 'q', чтобы выйти): ";
				RecreateArray(mass);
			}
			break;
		case '2':
			if (create)
			{
				Bubble_ExchangeSort(mass);
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case '3':
			if (create)
			{
				SelectionSort(mass);
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case '4':
			if (create)
			{
				InsertionSort(mass);
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case '5':
			if (create)
			{
				print_array(mass);
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case '6':
			cycle = false;
			create = false;
			delete[] mass.array;
			std::cout << "Вся выделенная память была возвращена в кучу. Закрытие программы..." << std::endl;
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}