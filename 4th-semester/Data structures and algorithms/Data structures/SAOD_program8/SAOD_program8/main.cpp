#include <iostream>

#include "mystruct.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	
	MainList* my_mainList = new MainList{};

	//Создание заголовочного элемента
	Node* ptr = new Node{};
	my_mainList->Head_ptr = ptr;
	my_mainList->Head_ptr->Next = my_mainList->Head_ptr;
	my_mainList->Head_ptr->Prev = my_mainList->Head_ptr;

	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			printDataStruct(my_mainList);
			break;
		case '2':
			searchDataStruct(my_mainList, "forward");
			break;
		case '3':
			searchDataStruct(my_mainList, "backward");
			break;
		case '4':
			addNewElementInStruct(my_mainList, "forward");
			break;
		case '5':
			addNewElementInStruct(my_mainList, "backward");
			break;
		case '6':
			addNewElementInList(my_mainList, "backward");
			break;
		case '7':
			addNewElementInList(my_mainList, "forward");
			break;
		case '8':
			removeElementFromList(my_mainList);
			break;
		case '9':
			removeElementFromStruct(my_mainList);
			break;
		case 'q':
			cycle = false;
			clearStruct(my_mainList);
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}