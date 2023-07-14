#include <iostream>
#include <string>
#include "myfuncs.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	if (argc == 5)
	{
		unsigned char nbyte{1};
		unsigned long long nnum{};
		unsigned long long byte{};
		unsigned char poz{};
		try
		{
			nbyte = static_cast<unsigned char>(std::stoi(argv[1]));
			nnum = std::stoull(argv[2]);
			byte = static_cast<unsigned long long>(std::stoi(argv[3]));
			poz = static_cast<unsigned char>(std::stoi(argv[4]));
		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << "Ќевозможно преобразовать аргумент(ы) в число типа: " << ia.what() << std::endl;
			return 0;
		}
		unsigned long long copynnum{ nnum };
		if (byte < 0 || byte > 255)
		{
			std::cerr << "”казанное вами число byte больше одного байта." << std::endl;
			return 0;
		}
		if ((nbyte >= 1 && nbyte <= 8) && (poz >= 0 && poz <= nbyte * 8 - 1) && (nnum >= 0 && nnum <= pow(2, nbyte*8)-1))
		{
			nnum = shiftr(nbyte, byte, nnum, poz);
		}
		else
		{
			std::cerr << "Ќеверно задано значение nbyte, nnum или poz. " << std::endl;
			return 0;
		}
		std::cout << "»сходное значение nnum: " << copynnum << std::endl;
		std::cout << "«начение nnum после вставлени€ байта с указанной позиции: " << nnum << std::endl;
	}
	else
	{
		std::cout << "Ќеобходимо указать п€ть аргументов командной строки: им€ программы и 4 числа ";
		std::cout << "(кол - во используемых байтов nbyte, само число nnum, сам вставл€емый байт byte и позицию начала вставки poz)." << std::endl;
	}
	return 0;
}
