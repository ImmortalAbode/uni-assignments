#ifndef QUEUEFUNCS_H_
#define QUEUEFUNCS_H_

#include "Queue.h"

//Функции для работы с очередью.
bool IsEmpty(Queue qp);
bool IsFull(Queue qp);
void push(Queue& qp);
void pop(Queue& qp);
void print_queue(Queue qp);
void clear();

//Вспомогательные функции для предотвращения ошибок ввода.
int getChoice();
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string const& convertStr);
double getNumber();

#endif /*QUEUEFUNCS_H_*/