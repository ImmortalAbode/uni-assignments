#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include <sstream>
#include "ArrayEightStrings.h"
#include "constants.h"
#include "mystructs.h"

//Вспомогательные функции
bool CheckCorrectField(std::string data, unsigned count);
void InitializationElement(std::stringstream& Data_field, Employee*& temp);
bool GetListFromFile(Employee*& head, std::ifstream& Data_file);
void AddHeadOfList(Employee*& head);
void GetNewElement(Employee*& head, std::stringstream& Data_field);
bool CheckAmountOfElements(Employee* head, unsigned num);
void MenuForChoices();
double GetNumber();
bool FastInput_MS(Employee* ea, std::string AddElement);
bool FastInput_Budget(Employee* ea, std::string AddElement);

//Основные функции
char getCase();
bool loadingList(const std::string fileName, Employee*& head);
bool unloadingList(const std::string fileName, Employee* head);
void PrintList(const Employee* head);
void AddNewElement(Employee*& previous, Employee* ea = nullptr);
void DeleteElement(Employee* search_del, const Employee* ed);

//Пользовательские функции
void case1(Employee* &head);
void case2(Employee* &head);
void case3(const Employee* head);
void case4(Employee* head);

#endif /*MYFUNCS_H_*/