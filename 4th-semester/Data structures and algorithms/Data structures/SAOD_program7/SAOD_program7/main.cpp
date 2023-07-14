#include <iostream>

#include "mystruct.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//Инициализация списков
	List* my_list = new List{};

	//Создание заголовочного элемента
	Node* ptr = new Node{};
	my_list->Head_ptr = ptr;
	my_list->Head_ptr->Next = my_list->Head_ptr;
	my_list->Head_ptr->Prev = my_list->Head_ptr;

	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			printDataList(my_list, "forward");
			break;
		case '2':
			printDataList(my_list, "backward");
			break;
		case '3':
			searchDataList(my_list, "forward");
			break;
		case '4':
			searchDataList(my_list, "backward");
			break;
		case '5':
			addNewElement(my_list, "forward");
			break;
		case '6':
			addNewElement(my_list, "backward");
			break;
		case '7':
			removeElement(my_list);
			break;
		case '8':
			cycle = false;
			clearLists(my_list);
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}