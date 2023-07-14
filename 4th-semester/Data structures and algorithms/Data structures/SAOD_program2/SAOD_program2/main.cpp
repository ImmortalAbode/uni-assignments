#include <iostream>
#include "QueueFuncs.h"
#include "Queue.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	
	Queue qp{};

	bool cycle{ true };
	while (cycle)
	{
		std::cout << "Что вы хотите сделать с очередью?" << std::endl;
		std::cout << "1 - Проверить пустоту очереди.\n"
			<< "2 - Проверить заполненность очереди.\n"
			<< "3 - Добавить элемент в конец очереди.\n"
			<< "4 - Удалить элемент из начала очереди.\n"
			<< "5 - Вывести текущее состояние очереди на экран.\n"
			<< "6 - Выход из программы.";
		std::cout << std::endl;

		int choice{};
		while (true)
		{
			choice = getChoice();
			if (choice >= 1 && choice <= 6)
				break;
			std::cout << "Вы должны ввести целое число от 1 до 6. Повторите ввод: " << std::endl;
		}

		switch (choice)
		{
		case 1:
			if (IsEmpty(qp))
				std::cout << "Ваша очередь пуста." << std::endl;
			else
			{
				if (qp.front <= qp.rear)
					std::cout << "Ваша очередь содержит " << qp.rear - qp.front + 1 << " элемент (-ов)(-а)." << std::endl;
				else 
					std::cout << "Ваша очередь содержит " << (qp.size - qp.front) + (qp.rear + 1) << " элемент (-ов)(-а)." << std::endl;
			}
			break;
		case 2:
			if (IsFull(qp))
				std::cout << "Ваша очередь заполнена." << std::endl;
			else
				if (qp.front != -1 && qp.rear != -1)
					if (qp.front <= qp.rear)
						std::cout << "В вашей очереди еще доступно для заполнения " << qp.size - (qp.rear - qp.front + 1) << " элементов." << std::endl;
					else
						std::cout << "В вашей очереди еще доступно для заполнения " << qp.size - ((qp.size - qp.front) + (qp.rear + 1)) << " элементов." << std::endl;
				else
					std::cout << "В вашей очереди еще доступно для заполнения " << qp.size << " элементов." << std::endl;
			break;
		case 3:
			push(qp);
			break;
		case 4:
			pop(qp);
			break;
		case 5:
			print_queue(qp);
			break;
		case 6:
			clear();
			cycle = false;
			break;
		default:;
		}
		std::cout << std::endl;
	}
	return 0;
}