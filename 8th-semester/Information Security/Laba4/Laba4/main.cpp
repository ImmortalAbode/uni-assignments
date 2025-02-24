#include <iostream>

#include "myfuncs.h"

int main() {
	//setlocale(LC_ALL, "Rus");
	std::system("chcp 1251 > nul");
	//std::system("Color F0");
	ShowTitle();
	//Цикл работы с программой.
	bool cycle{ true };
	while (cycle)
	{
		switch (GetCase(MainMenu))
		{
		case '1'://Запустить программу.
			DrawLine();
			EcexuteContourPolySub();
			break;
		case '2'://Выход.
			cycle = false;
			break;
		default:;
		}
		DrawLine();
		std::cout << std::endl;
	}

	std::system("chcp 866 > nul");
	return 0;
}
