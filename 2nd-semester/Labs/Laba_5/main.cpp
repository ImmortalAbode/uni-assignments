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
			std::cerr << "���������� ������������� ��������(�) � ����� ����: " << ia.what() << std::endl;
			return 0;
		}
		unsigned long long copynnum{ nnum };
		if (byte < 0 || byte > 255)
		{
			std::cerr << "��������� ���� ����� byte ������ ������ �����." << std::endl;
			return 0;
		}
		if ((nbyte >= 1 && nbyte <= 8) && (poz >= 0 && poz <= nbyte * 8 - 1) && (nnum >= 0 && nnum <= pow(2, nbyte*8)-1))
		{
			nnum = shiftr(nbyte, byte, nnum, poz);
		}
		else
		{
			std::cerr << "������� ������ �������� nbyte, nnum ��� poz. " << std::endl;
			return 0;
		}
		std::cout << "�������� �������� nnum: " << copynnum << std::endl;
		std::cout << "�������� nnum ����� ���������� ����� � ��������� �������: " << nnum << std::endl;
	}
	else
	{
		std::cout << "���������� ������� ���� ���������� ��������� ������: ��� ��������� � 4 ����� ";
		std::cout << "(��� - �� ������������ ������ nbyte, ���� ����� nnum, ��� ����������� ���� byte � ������� ������ ������� poz)." << std::endl;
	}
	return 0;
}
