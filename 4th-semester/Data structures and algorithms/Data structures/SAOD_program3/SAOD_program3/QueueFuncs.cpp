#include <iostream>
#include <string>

#include "Queue.h"
#include "QueueFuncs.h"

//Инициализация работы с очередью.
//Проверка пустоты очереди.
bool IsEmpty(Queue qp)
{
	return qp.front == nullptr ? true : false;
}
//Добавление элемента в конец очереди.
void push_queue(Queue& qp, char ASCII)
{
	try
	{
		Node* new_element = new Node{};
		if (qp.rear == nullptr)
		{
			qp.rear = new_element;
			qp.front = qp.rear;
		}
		else
		{
			qp.rear->next = new_element;
			qp.rear = new_element;
		}
		std::cout << "В очередь был добавлен символ '" << ASCII << "'." << std::endl;
		qp.rear->data = ASCII;
		qp.rear->next = qp.front;
		qp.size++;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Не удалось выделить память из кучи. Кучи переполнена!" << std::endl;
		clear(qp);
		exit(-1);
	}
}
//Удаление элемента из начала очереди.
void pop_queue(Queue& qp)
{
	Node* temp{ qp.front };
	if (qp.front == qp.rear)
	{
		qp.rear = nullptr; 
		qp.front = nullptr;
	}
	else
	{
		qp.front = qp.front->next;
		qp.rear->next = qp.front;
	}
	std::cout << "Символ " << temp->data << "был успешно удален из начала очереди." << std::endl;
	delete temp;
	qp.size--;
}
//Вывод на экран текущего состояния очереди.
void print_queue(Queue qp)
{
	if (!IsEmpty(qp))
	{
		int count_of_elements{};
		Node* temp{ qp.front };
		std::cout << "\tВаша очередь: " << std::endl;
		for (int i{ qp.size }; i > 0; i--)
		{
			count_of_elements++;
			std::cout << temp->data;
			temp = temp->next;
			if (count_of_elements % 100 == 0)
				std::cout << "\n";
		}
		temp = nullptr;
		std::cout << std::endl;
	}
	else
		std::cout << "Ваша очередь пуста!" << std::endl;
}
//Закрытие программы.
void clear(Queue& qp)
{
	if (qp.front != nullptr)
		for (int i{ qp.size };i > 0;i--)
		{
			Node* temp{ qp.front };
			qp.front = qp.front->next;
			delete temp;
			qp.size--;
		}

	qp.front = nullptr; qp.rear = nullptr;

	std::cout << "Вся динамически выделенная память была успешно возвращена в кучу. Закрытие программы..." << std::endl;
}

//ГПСЧ.
int getRandomNumber(float min, float max) //Генерация случайного числа между заданными min и max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<int>((rand() * fraction * (max - min + 1) + min));
}
//Получение символа пользователя.
bool isSymbolQ()
{
	std::cout << "Введите символ 'q' для выхода из программы или нажмити Enter: ";
	std::string symbol{};
	std::getline(std::cin, symbol);
	if (symbol == "q")
		return true;
	return false;
}
