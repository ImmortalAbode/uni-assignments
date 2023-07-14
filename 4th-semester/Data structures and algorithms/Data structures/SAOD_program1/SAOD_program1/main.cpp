#include <iostream>

#include "StackFuncs.h"
#include "Stack.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	Stack* sp{ nullptr };
	Stack* dopsp{ nullptr };

	bool cycle{ true };
	while (cycle)
	{
		std::cout << "Что вы хотите сделать со стеком?" << std::endl;
		std::cout << "1 - Проверка пустоты стека.\n"
			<< "2 - Добавление элемента в вершину основного стека.\n"
			<< "3 - Добавление сразу нескольких элементов в основной стек.\n"
			<< "4 - Удаление элемента из основного стека.\n"
			<< "5 - Вывод текущего состояния стека на экран.\n"
			<< "6 - Вывод содержимого вспомогательного стека удаленных элементов.\n"
			<< "7 - Выход из программы.";
		std::cout << std::endl;

		int choice{};
		while (true)
		{
			choice = getChoice();
			if (choice >= 1 && choice <= 7)
				break;
			std::cout << "Вы должны ввести целое число от 1 до 7. Повторите ввод: " << std::endl;
		}

		switch (choice)
		{
		case 1:
			if (IsEmpty(sp))
				std::cout << "Ваш стек пуст." << std::endl;
			else
			{
				int count{};
				Stack* temp{ sp };
				while (temp != nullptr)
				{
					count += 1;
					temp = temp->next;
				}
				std::cout << "Ваш стек содержит " << count-1 << " элементов (-а)." << std::endl;
			}
			break;
		case 2:
			push(sp, dopsp);
			break;
		case 3:
			push_random(sp);
			break;
		case 4:
			pop(sp, dopsp);
			break;
		case 5:
			print_stack(sp);
			break;
		case 6:
			print_dopstack(dopsp);
			break;
		case 7:
			clear(sp, dopsp);
			cycle = false;
			break;
		default:;
		}
		std::cout << std::endl;
	}
	return 0;
}