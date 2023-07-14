#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	std::ifstream fin;
	std::ofstream fout;
	unsigned char in_lab;
	unsigned char out_lab;
	double NM{};
	std::string workStr;
	while (true)
	{
		std::cout << "Ввод с консоли (0) или из файла (1): ";
		in_lab = get_0_1();
		std::cout << "Вывод на консоль (0) или в файл (1): ";
		out_lab = get_0_1();
		if (in_lab == '1')
		{
			std::string tmpFile = selectFile(Blank::INPUT, DEFAULT_NAME_FILE_IN);
			fin.open(tmpFile);
			if (!fin.is_open())
			{
				std::cout << "Не удалось открыть файл : " << tmpFile << "!" << std::endl;
				break;
			}
		}
		if (out_lab == '1')
		{
			std::string tmpFile = selectFile(Blank::OUTPUT, DEFAULT_NAME_FILE_OUT);
			fout.open(tmpFile);
			if (!fout.is_open())
			{
				std::cout << "Не удалось открыть файл : " << tmpFile << "!" << std::endl;
				break;
			}
		}
		if (in_lab == '0' && out_lab == '0')
		{
			if (initStr(Select::CONSOLE, std::cin, workStr, NM))
				result(std::cout, NM, workStr);
			if (getNext())
				continue;
			else
				break;
		}
		else if (in_lab == '0' && out_lab == '1')
		{
			if (initStr(Select::CONSOLE, std::cin, workStr, NM))
				result(fout, NM, workStr);
			if (getNext())
				continue;
			else
				break;
		}
		else if (in_lab == '1' && out_lab == '0')
		{
			if (initStr(Select::FILE, fin, workStr, NM))
				result(std::cout, NM, workStr);
			break;
		}
		else if (in_lab == '1' && out_lab == '1')
		{
			if (initStr(Select::FILE, fin, workStr, NM))
				result(fout, NM, workStr);
			break;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
