#ifndef QUEUE_H_
#define QUEUE_H_

//���� �������.
struct Node
{
	Node* next{ nullptr };//��������� �� ��������� ������� �������
	char data{};//������ � �������� �������
};

//���� �������.
struct Queue
{
	int size{};
	Node* front{ nullptr };
	Node* rear{ nullptr };
};

#endif /*QUEUE_H_*/