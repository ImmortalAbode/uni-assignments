#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuOfProgram();
char getChoice();

bool isEmpty(List* my_list);
Node* searchNodeForward(List* my_list, const int& searching_elem);
Node* searchNodeBackward(List* my_list, const int& searching_elem);
void clearList(List*& list);

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();
std::string getUserInput_2();

void printDataList(List* my_list, std::string const& choice);
void searchDataList(List* my_list, std::string const& choice);
void addNewElement(List*& my_list, std::string const& choice);
void removeElement(List*& my_list);
void clearLists(List*& my_list);

#endif /*MYFUNCS_H_*/