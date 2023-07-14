#include <iostream>
#include <string>

#include "Queue.h"
#include "QueueFuncs.h"

//������������� ������ � ��������.
//�������� ������� �������.
bool IsEmpty(Queue qp)
{
	return qp.front == nullptr ? true : false;
}
//���������� �������� � ����� �������.
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
		std::cout << "� ������� ��� �������� ������ '" << ASCII << "'." << std::endl;
		qp.rear->data = ASCII;
		qp.rear->next = qp.front;
		qp.size++;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		clear(qp);
		exit(-1);
	}
}
//�������� �������� �� ������ �������.
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
	std::cout << "������ " << temp->data << "��� ������� ������ �� ������ �������." << std::endl;
	delete temp;
	qp.size--;
}
//����� �� ����� �������� ��������� �������.
void print_queue(Queue qp)
{
	if (!IsEmpty(qp))
	{
		int count_of_elements{};
		Node* temp{ qp.front };
		std::cout << "\t���� �������: " << std::endl;
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
		std::cout << "���� ������� �����!" << std::endl;
}
//�������� ���������.
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

	std::cout << "��� ����������� ���������� ������ ���� ������� ���������� � ����. �������� ���������..." << std::endl;
}

//����.
int getRandomNumber(float min, float max) //��������� ���������� ����� ����� ��������� min � max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<int>((rand() * fraction * (max - min + 1) + min));
}
//��������� ������� ������������.
bool isSymbolQ()
{
	std::cout << "������� ������ 'q' ��� ������ �� ��������� ��� ������� Enter: ";
	std::string symbol{};
	std::getline(std::cin, symbol);
	if (symbol == "q")
		return true;
	return false;
}
