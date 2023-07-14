#ifndef STACKFUNCS_H_
#define STACKFUNCS_H_

#include "Stack.h"

//������� ��� ������ �� ������.
bool IsEmpty(Stack* sp);
void push(Stack*& sp, Stack*& dopsp);
void push_random(Stack*& sp);
void pop(Stack*& sp, Stack*& dopsp);
void print_stack(Stack* sp);
void print_dopstack(Stack* dopsp);
void clear(Stack*& sp, Stack*& dopsp);

//����� ������� ���������� / �������� �������� �� �����, �������� �� ������ � ������ ��� �����������.
void push_back(Stack*& sp, double number);
void pop_back(Stack*& sp);
void push_pop_back(Stack*& sp, Stack*& dopsp);
void pop_push_back(Stack*& sp, Stack*& dopsp);

//��������������� ������� ��� �������������� ������ �����.
int getChoice();
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string const& convertStr);
double getNumber();
double getRandomNumber(float min, float max);

#endif /*STACKFUNCS_H_*/