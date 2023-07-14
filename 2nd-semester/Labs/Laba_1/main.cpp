#include <iostream>
#include <fstream>
#include "constants.h"
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	std::ifstream fin(NAME_FILE_IN);
	std::ofstream fout(NAME_FILE_OUT);
	unsigned char in_lab;
	unsigned char out_lab;
	double a{}, h{}, b{};
	int n{ 1 };
	double sum{};
	double mass[NM];
	while (true)
	{
		if (fin.is_open() && fout.is_open())
		{
			std::cout << "Ввод с консоли (0) или из файла \"in.txt\" (1): ";
			in_lab = get_0_1();
			std::cout << "Вывод на консоль (0) или в файл \"out.txt\"(1): ";
			out_lab = get_0_1();
			if (in_lab == '0' && out_lab == '0') {
				if (init(mass, a, h, b, n))
					fsum(std::cout, mass, a, h, b, n, sum);
				if (getNext())
					continue;
				else
					break;
			}
			else if (in_lab == '0' && out_lab == '1') {
				if (init(mass, a, h, b, n))
					fsum(fout, mass, a, h, b, n, sum);
				if (getNext())
					continue;
				else
					break;
			}
			else if (in_lab == '1' && out_lab == '0') {
				if (finit(fin, mass, a, h, b, n))
					fsum(std::cout, mass, a, h, b, n, sum);
				break;
			}
			else if (in_lab == '1' && out_lab == '1') {
				if (finit(fin, mass, a, h, b, n))
					fsum(fout, mass, a, h, b, n, sum);
				break;
			}
		}
		else {
			std::cout << "Не удалось открыть файл(ы)!" << std::endl;
			break;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
