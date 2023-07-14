#include <iostream>
#include <string>
#include <Windows.h>

#include "Town.h"
#include "Republic.h"
#include "Country.h"
#include "myfuncs.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	std::system("color F0");

	Country* ptr_struct = new Country{}; //Указатель на структуру данных "Страна"

	int choice_for_file{};
	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getPointOfMenu())
		{
		case 0:
			std::cout << "Вы хотите сохранить текущую структуру и попробовать загрузить данные файла в нее(0) или удалить текущую структуру и загрузить файл(1)? ";
			choice_for_file = get0_1();
			if (choice_for_file == 1 && ptr_struct->getHeadOfRepublics() != nullptr)
			{
				ClearStruct(ptr_struct);
				ptr_struct = new Country{};
			}
			LoadFromFile(ptr_struct);
			break;
		case 1:
			GiveNameToCountry(ptr_struct);
			break;
		case 2:
			showAllStruct(ptr_struct);
			break;
		case 3:
			AddElemToStruct(ptr_struct);
			break;
		case 4:
			DeleteElemFromStruct(ptr_struct);
			break;
		case 5:
			FindElemInStruct(ptr_struct);
			break;
		case 6:
			LoadInFile(ptr_struct);
			break;
		case 7:
			cycle = false;
			ClearStruct(ptr_struct);
			std::cout << "Завершение программы ..." << std::endl;
			break;
		}
		std::cout << std::string(70, '-') << std::endl;
	}
	std::system("chcp 866 > nul");
	return 0;
}