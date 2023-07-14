#include <iostream>
#include "QueueFuncs.h"
#include "Queue.h"
#include <cstdlib> //Для rand() и srand()
#include <ctime> //Для time()
#include <Windows.h>//Для Sleep()

int main()
{
	std::setlocale(LC_ALL, "Rus");

	//Привязка ГПСЧ (rand()) к календарному времени для создания неповторяющихся последовательностей случайных чисел
	srand(static_cast<unsigned int>(time(0)));
	std::cout << "Датчик псевдослучаный чисел был инициирован." << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;

	int number_operation{ 1 };
	Queue qp{};
	while (true)
	{
		std::cout << number_operation << ": ";
		int push_pop_choice{ getRandomNumber(1, 100) };
		int count_push_pop{ getRandomNumber(1, 3) };
		bool even_choice{};
		push_pop_choice % 2 == 0 ? even_choice = true : even_choice = false;
		
		switch (even_choice)
		{
		case true:
			std::cout << "В конец очереди будет добавлен (-о) " << count_push_pop << " новый (-ых) элемент (-а)." << std::endl;
			for (int i{}; i < count_push_pop;i++)
			{
				char ASCII{ static_cast<char>(getRandomNumber(65, 90)) };
				push_queue(qp, ASCII);
			}
			break;
		case false:
			std::cout << "Из начала очереди будет удален (-о) " << count_push_pop << " элемент (-a)(-ов)." << std::endl;
			for (int i{}; i < count_push_pop;i++)
			{
				if (!IsEmpty(qp))
					pop_queue(qp);
				else
				{
					std::cout << count_push_pop - i << "-ая операция удаления и оставшиеся невозможны, так как очередь стала пуста!" << std::endl;
					break;
				}
			}
			break;
		}
		print_queue(qp);
		if (isSymbolQ())
			break;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		number_operation++;
		Sleep(60000);
	}
	clear(qp);
	return 0;
}