#include <iostream> // ��� �������
#include <string> // ��� �����

#include "WorkWithFunc.h"
#include "RPN.h"

#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	PrePrint();
	Func* func = new Func{};					//��������� ��� �������� ������ �������.
	Stack* stack_signs = new Stack{};			//����, ������� ������ ���������, ����� ��������� �� ������������ � ���(���).
	OutString* RPN_string = new OutString{};	//��������� ��� ���������� ��� (���).

	int* result_of_function{ nullptr };			//������������ ������, ������ ����������� �������� �������.

	bool cycle{ true };
	while (cycle)
	{
		MenuPrint();
		switch (getChoice())
		{
		case '1'://�������� �������� k-������� ������.
			getNumberK(func);
			ClearSomeStructs(result_of_function, RPN_string);//������� ����������� ���-�� ���������, ���� ������� ����� ������.
			break;
		case '2'://�������� ���-�� ������������ ���������� �������.
			getNumberN(func);
			ClearSomeStructs(result_of_function, RPN_string);//������� ����������� ���-�� ���������, ���� ������� ����� ������.
			break;
		case '3'://�������� ���� �������, ���� ������ k � n.
			if (func->k != 0 && func->n != 0)
			{
				getFunction(func);
				ClearSomeStructs(result_of_function, RPN_string);//������� ����������� ���-�� ��������� ����� ������� � ��������.
			}
			else
				std::cout << "������� ������� ����� k � ����� n" << std::endl;
			break;
		case '4'://��������� �������� ������� � �� �����.
			if (func->func != "")
				getValuesOfFunc(func, stack_signs, RPN_string, result_of_function);
			else
				std::cout << "������� ������� �������." << std::endl;
			break;
		case '5'://��������� ������ ����� �������.
			if (result_of_function != nullptr)
				getSKNFform(func, result_of_function);
			else
				std::cout << "������� ���������� �������." << std::endl;
			break;
		case '6'://�������� ���������� ������������� ��������� ��������.
			if (result_of_function != nullptr)
				getSaveData(func, result_of_function);
			else
				std::cout << "������� ���������� �������." << std::endl;
			break;
		case '7'://����� �� ���������.
			cycle = false;
			clearAllStructs(func, stack_signs, RPN_string);
			if (result_of_function != nullptr) delete[] result_of_function;
			std::cout << "��� ���������� ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
			break;
		}
		std::cout << std::string(125, '-') << std::endl << std::endl;
	}
	return 0;
}