#ifndef QUEUE_H_
#define QUEUE_H_

//Узел очереди.
struct Node
{
	Node* next{ nullptr };//Указатель на следующий элемент очереди
	char data{};//Данные в элементе очереди
};

//Сама очередь.
struct Queue
{
	int size{};
	Node* front{ nullptr };
	Node* rear{ nullptr };
};

#endif /*QUEUE_H_*/