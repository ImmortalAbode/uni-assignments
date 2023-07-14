#include <iostream>
#include <bitset>
#include "myfuncs.h"

unsigned long long shiftr(unsigned char nbyte, unsigned long long byte, unsigned long long nnum, unsigned char poz)
{
	unsigned long long mask{};
	switch (nbyte)
	{
	case 1: mask = 0xFF; break;
	case 2: mask = 0xFFFF; break;
	case 3: mask = 0xFFFFFF; break;
	case 4: mask = 0xFFFFFFFF; break;
	case 5: mask = 0xFFFFFFFFFF; break;
	case 6: mask = 0xFFFFFFFFFFFF; break;
	case 7: mask = 0xFFFFFFFFFFFFFF; break;
	case 8: mask = 0xFFFFFFFFFFFFFFFF; break;
	default:;
	}
	std::bitset<64> BinaryNumber = nnum;
	std::cout << "¬аше исходное число nnum в двоичном представлении (по 4 бита): ";
	for (int i = nbyte*2-1; i > -1; i--)
	{
		for (int j = 3;j > -1 ;j--)
		{
			std::cout << BinaryNumber[j + i * 4];
		}
		std::cout << ' ';
	}
	std::cout << std::endl;
	std::bitset<8> BinaryByte = byte;
	std::cout << "¬аш байт byte в двоичном представлении (по 4 бита): ";
	for (int i = 1; i > -1; i--)
	{
		for (int j = 3;j > -1;j--)
		{
			std::cout << BinaryByte[j + i * 4];
		}
		std::cout << ' ';
	}
	std::cout << std::endl;
	std::cout << "ѕозици€, с которой начинать вставл€ть байт: " << (mask & poz) << std::endl;
	unsigned long long a{};
	if (nbyte * 8 - (nbyte * 8 - poz) + 1 >= 8)
	{
		for (unsigned i = 0;i <= 7;i++)
		{
			a = byte & (static_cast<unsigned long long>(0x1) << (7 - i));
			if (a != 0)
			{
				nnum |= a << (poz-7);
			}
			else
			{
				a = a | (static_cast<unsigned long long>(0x1) << (7-i));
				nnum &= ~(a << (poz-7));
			}

		}
	}
	else
	{
		for (unsigned i = 0;i <= poz;i++)
		{
			a = byte & (static_cast < unsigned long long>(0x1) << (7-i));
			if (a != 0)
			{
				nnum |= a >> (7-poz);
			}
			else
			{
				a = a | (static_cast<unsigned long long>(0x1) << (7-i));
				nnum &= ~(a >> (7-poz));
			}

		}
	}
	nnum &= mask;
	std::bitset<64> BinaryNewNumber = nnum;
	std::cout << "¬аше число nnum после вставлени€ байта с указанной позиции (по 4 бита): ";
	for (int i = nbyte * 2 - 1; i > -1; i--)
	{
		for (int j = 3;j > -1;j--)
		{
			std::cout << BinaryNewNumber[j + i * 4];
		}
		std::cout << ' ';
	}
	std::cout << std::endl;
	return nnum;
}
