#ifndef QUEUEFUNCS_H_
#define QUEUEFUNCS_H_

#include "Queue.h"

//Функции для работы с очередью.
bool IsEmpty(Queue qp);
void push_queue(Queue& qp, char ASCII);
void pop_queue(Queue& qp);
void print_queue(Queue qp);
void clear(Queue& qp);

//ГПСЧ.
int getRandomNumber(float min, float max);
//Получение символа пользователя.
bool isSymbolQ();

#endif /*QUEUEFUNCS_H_*/