#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "myarray.h"

float getRandomNumber(float min, float max);

void MenuOfProgram();
char getChoice();

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();
std::string getUserChoice();

char getUserShellChoice();
std::string getUserCountSteps(Array mass, const int& max_count_steps);
int getUserSteps(Array mass, int* mass_steps, const int& mass_steps_size);

void CreateArray(Array& mass, const int& choice);
void print_array(Array& mass);
void RecreateArray(Array& mass);

void Swap_Counter(Array& mass, const int& left_elem_ind, const int& right_elem_ind);
int*& CopyArray(const Array& mass);

double Bubble_ExchangeSort(Array& mass, int& counter_swap, int& counter_comparison);
double SelectionSort(Array& mass, int& counter_swap, int& counter_comparison);
double InsertionSort(Array& mass, int& counter_swap, int& counter_comparison);
int*& UserWishes(Array mass, int& steps_size);
double UserShellSort(Array& mass, int& counter_swap, int& counter_comparison, int* steps, const int& steps_size);
double ShellSort(Array& mass, int& counter_swap, int& counter_comparison);
void QuickSort(int*& array, int first, int last, int& counter_swap, int& counter_comparison); //рекурсия
void Heapify(Array& mass, const int& current_max_index, const int& current_index, int& counter_swap, int& counter_comparison);
double HeapSort(Array& mass, int& counter_swap, int& counter_comparison);

void SortingTimePreparation(Array mass, const std::string& type_of_sort);

#endif /*MYFUNCS_H_*/