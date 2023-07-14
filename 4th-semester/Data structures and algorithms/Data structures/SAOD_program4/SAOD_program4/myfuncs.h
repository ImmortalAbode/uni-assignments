#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "MyList.h"

void MenuOfProgram();
char getChoice();

bool isEmpty(List list);
bool isFull(List list);

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();

void printDataList(List list);
void searchDataList(List list);
void addNewElement(List& list);
void removeElement(List& list);

#endif /*MYFUNCS_H_*/