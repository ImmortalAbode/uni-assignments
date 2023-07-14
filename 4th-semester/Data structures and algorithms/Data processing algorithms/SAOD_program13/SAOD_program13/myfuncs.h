#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "myarray.h"

float getRandomNumber(float min, float max);

void MenuOfProgram();
char getChoice();

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();

void CreateArray(Array& mass, const int& choice);
void print_array(Array& mass);
void RecreateArray(Array& mass);

void Swap_Counter(Array& mass, const int& left_elem, const int& right_elem);
int*& CopyArray(const Array& mass);

void Bubble_ExchangeSort(Array mass);
void SelectionSort(Array mass);
void InsertionSort(Array mass);

#endif /*MYFUNCS_H_*/