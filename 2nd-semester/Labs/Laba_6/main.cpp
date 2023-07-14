#include <iostream>
#include "constants.h"
#include "myfuncs.h"

int main() 
{
	std::setlocale(LC_ALL, "Rus");
	std::system("chcp 1251 > nul");
	Employee* head_ptr{ nullptr };
	if (loadingList(DEFAULT_NAME_FILE_IN_OUT, head_ptr))
	{
		std::cout << "Список загружен . . ." << std::endl << std::endl;
		bool cycle{ true };
		while (cycle) {
			switch (getCase()) 
			{
			case '1':
				std::cout << std::endl;
				case1(head_ptr);
				std::cout << std::endl;
				break;
			case '2':
				std::cout << std::endl;
				case2(head_ptr);
				std::cout << std::endl;
				break;
			case '3':
				std::cout << std::endl;
				case3(head_ptr);
				std::cout << std::endl;
				break;
			case '4':
				std::cout << std::endl;
				case4(head_ptr);
				std::cout << std::endl;
				break;
			case '5':
				std::cout << std::endl;
				cycle = false;
			}
		}
		if (unloadingList(DEFAULT_NAME_FILE_IN_OUT, head_ptr)) 
		{
			std::cout << std::endl << "Список выгружен и удалён из оперативной памяти . . ." << std::endl;
			std::system("chcp 866 > nul");
		}
	}
	return 0;
}
