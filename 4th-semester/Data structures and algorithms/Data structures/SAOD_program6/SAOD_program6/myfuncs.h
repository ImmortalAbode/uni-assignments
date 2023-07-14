#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "list.h"

void MenuOfProgram();
char getChoice();

bool isEmpty(List* my_list);
Node* searchNode(List* my_list, const int& searching_elem);
void clearList(List*& list);

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();
std::string getUserInput_2();

void printDataList(List* list);
void searchDataList(List* my_list);
void addNewElement(List*& my_list, const int& choice, List*& sub_list);
void removeElement(List*& my_list, List*& sub_list);
void clearLists(List*& my_list, List*& sub_list);

#endif /*MYFUNCS_H_*/