#include <iostream>

#include "list.h"
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "RUS");
	//Инициализация списков
	List* my_list = new List{}, * sub_list = new List{};

	//Создание заголовочных элементов
	Node* ptr = new Node{};
	my_list->Head_ptr = ptr;

	Node* sub_ptr = new Node{};
	sub_list->Head_ptr = sub_ptr;

	bool cycle{ true };
	while (cycle)
	{
		MenuOfProgram();
		switch (getChoice())
		{
		case '1':
			printDataList(my_list);
			break;
		case '2':
			searchDataList(my_list);
			break;
		case '3':
			addNewElement(my_list, 1, sub_list); //До заданного
			break;
		case '4':
			addNewElement(my_list, 2, sub_list); //После заданного
			break;
		case '5':
			removeElement(my_list, sub_list);
			break;
		case '6':
			printDataList(sub_list);
			break;
		case '7':
			cycle = false;
			clearLists(my_list, sub_list);
			break;
		}
		std::cout << "---------------------------------------------------------------------" << std::endl;
	}
	return 0;
}