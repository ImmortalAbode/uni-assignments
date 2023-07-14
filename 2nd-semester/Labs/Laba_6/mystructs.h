#ifndef MYSTRUCTS_H_
#define MYSTRUCTS_H_

#include <string>

struct Employee {
	Employee* next;
	std::string Surname;
	std::string MiddleName;
	std::string Name;
	std::string Age;
	std::string MaritalStatus;
	std::string Spouse;
	std::string Kids;
	std::string Budget;
};

struct DefaultEmployee {
	std::string def_Surname;
	std::string def_MiddleName;
	std::string def_Name;
	std::string def_Age;
	std::string def_MaritalStatus;
	std::string def_Spouce;
	std::string def_Kids;
	std::string def_Budget;
};


#endif /*MYSTRUCTS_H_*/
