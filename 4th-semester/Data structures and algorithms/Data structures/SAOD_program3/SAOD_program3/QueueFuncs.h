#ifndef QUEUEFUNCS_H_
#define QUEUEFUNCS_H_

#include "Queue.h"

//������� ��� ������ � ��������.
bool IsEmpty(Queue qp);
void push_queue(Queue& qp, char ASCII);
void pop_queue(Queue& qp);
void print_queue(Queue qp);
void clear(Queue& qp);

//����.
int getRandomNumber(float min, float max);
//��������� ������� ������������.
bool isSymbolQ();

#endif /*QUEUEFUNCS_H_*/