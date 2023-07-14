#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuOfProgram();
char getChoice();

bool isEmptyStruct(MainList* my_mainList);
bool isEmptyList(Node* my_subList);
Node* searchNode(MainList* my_mainList, const int& searching_elem);
SubNode* searchSubNodeForward(Node* my_subList, const int& searching_elem);
SubNode* searchSubNodeBackward(Node* my_subList, const int& searching_elem);
std::string createNumList(MainList* my_mainList);
int getNumList(MainList* my_mainList);
void clearList(Node*& my_subList);

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string getUserInput();
std::string getUserInput_2();
std::string getUserInput_3(MainList* my_mainList);

void printDataStruct(MainList* my_mainList);
void searchDataStruct(MainList* my_mainList, std::string const& choice);
void addNewElementInStruct(MainList*& my_mainList, std::string const& choice);
void addNewElementInList(MainList*& my_mainList, std::string const& choice);
void removeElementFromList(MainList*& my_mainList);
void removeElementFromStruct(MainList*& my_mainList);
void clearStruct(MainList*& my_mainList);

#endif /*MYFUNCS_H_*/