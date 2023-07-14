#include <iostream>
#include <string>

#include "MyList.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");

	List list{};

	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			printDataList(list);
			break;
		case '2':
			searchDataList(list);
			break;
		case '3':
			addNewElement(list);
			break;
		case '4':
			removeElement(list);
			break;
		case '5':
			cycle = false;
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}