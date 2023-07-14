#include <iostream>
#include <string>

#include "MyList.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");

	List list{};
	list.index[0] = 0;
	for (int i{ 1 }; i < size;i++)
		list.index[i] = -1;

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
			addNewElement(list, 1); //До заданного
			break;
		case '4':
			addNewElement(list, 2); //После заданного
			break;
		case '5':
			removeElement(list);
			break;
		case '6':
			cycle = false;
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}