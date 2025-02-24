#include <iostream>

#include "myfuncs.h"

int main() 
{
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
		case '1'://Провести частотный анализ символов.
			DrawLine('-');
			ExecuteSymbolFrequency();
			break;
		case '2'://Дншифровка файла.
			DrawLine('-');
			ExecuteDecryptFile();
			break;
		case 'q'://Выход.
			cycle = false;
			break;
		default:;
		}
		DrawLine('-');
		std::cout << std::endl;
	}

	std::system("chcp 866 > nul");
	return 0;
}