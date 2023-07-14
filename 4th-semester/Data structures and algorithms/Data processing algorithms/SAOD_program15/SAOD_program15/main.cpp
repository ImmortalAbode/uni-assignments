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
		case 1:
			if (!create)
			{
				create = true;
				CreateArray(mass, -1);
			}
			else
			{
				std::cout << "Массив уже был создан!" << std::endl;
				std::cout << "Вы хотите заново создать массив? (введите количество элементов или 'q', чтобы выйти): ";
				RecreateArray(mass, 0);
			}
			break;
		case 2:
			if (create)
			{
				SortingTimePreparation(mass, "bubble");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 3:
			if (create)
			{
				SortingTimePreparation(mass, "selection");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 4:
			if (create)
			{
				SortingTimePreparation(mass, "insertion");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 5:
			if (create)
			{
				SortingTimePreparation(mass, "shell");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 6:
			if (create)
			{
				SortingTimePreparation(mass, "quick");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 7:
			if (create)
			{
				SortingTimePreparation(mass, "heap");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 8:
			if (create)
			{
				SortingTimePreparation(mass, "bucket_with_array");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 9:
			if (create)
			{
				SortingTimePreparation(mass, "bucket_without_array");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 10:
			if (create)
			{
				SortingTimePreparation(mass, "generic_bucket");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 11:
			if (create)
			{
				SortingTimePreparation(mass, "radix");
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 12:
			if (create)
			{
				print_array(mass);
			}
			else
				std::cout << "Сначала необходимо создать массив." << std::endl;
			break;
		case 13:
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