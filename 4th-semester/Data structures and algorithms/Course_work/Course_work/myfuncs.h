#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "Country.h"

void MenuOfProgram();
int getPointOfMenu();

int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);

bool NameOfObjectIsCorrect(std::string const& ObjectName);
std::string getDataUserElem();
int get0_1();
int getPopulation();

void GiveNameToCountry(Country*& ptr_struct);
void showAllStruct(Country*& ptr_struct);
void AddElemToStruct(Country*& ptr_struct);
void FindElemInStruct(Country*& ptr_struct);
void DeleteElemFromStruct(Country*& ptr_struct);
void ClearStruct(Country*& ptr_struct);

int getCountOfFields(std::string ss_data);
void addObjectToCheckingMass(std::string*& old_mass_of_objects, int& old_count_of_objects, std::string const& new_name);
bool checkSSIsCorrect(std::string ss_data, std::string*& mass_of_republics, int& count_of_republics);
void DataFromFile(Country*& ptr_struct, std::stringstream& data_field);
void LoadFromFile(Country*& ptr_struct);
bool NameFileIsCorrect(std::string const& name_saving_file);
std::string getNameOfFile();
void LoadInFile(Country*& ptr_struct);

#endif /*MYFUNCS_H_*/