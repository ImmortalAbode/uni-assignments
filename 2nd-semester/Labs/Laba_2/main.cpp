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
	double mass[NM];
	double a{}, b{};
	int n{};
	while (true)
	{
		if (fin.is_open() && fout.is_open())
		{
			std::cout << "���� � ������� (0) ��� �� ����� \"in.txt\" (1): ";
			in_lab = get_0_1();
			std::cout << "����� �� ������� (0) ��� � ���� \"out.txt\"(1): ";
			out_lab = get_0_1();
			if (in_lab == '0' && out_lab == '0') {
				if (init(mass, a, n))
					forder(std::cout, mass, a, n);
				if (getNext())
					continue;
				else
					break;
			}
			else if (in_lab == '0' && out_lab == '1') {
				if (init(mass, a, n))
					forder(fout, mass, a, n);
				if (getNext())
					continue;
				else
					break;
			}
			else if (in_lab == '1' && out_lab == '0') {
				if (finit(fin, mass, a, n, b))
					forder(std::cout, mass, a, n);
				break;
			}
			else if (in_lab == '1' && out_lab == '1') {
				if (finit(fin, mass, a, n, b))
					forder(fout, mass, a, n);
				break;
			}
		}
		else {
			std::cout << "�� ������� ������� ����(�)!" << std::endl;
			break;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
