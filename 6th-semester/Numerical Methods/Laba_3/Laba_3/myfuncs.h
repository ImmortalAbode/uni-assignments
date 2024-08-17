#ifndef MYFUNCS_H_
#define MYFUNCS_H_

/*����� ������� ����� � ������*/
void PrintDash();
void PrePrint();
void PrintMenu();

/*������� �������� ����������������� �����*/
bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);
char GetChoice();
long double getSvalue();

/*�������� �������*/
//����� �������.
void printTable(const double* const& x, const double* const& t, const double* const* const& u);
void ExplicitSchema();
void ImplicitSchema(const double& S);

#endif /*MYFUNCS_H_*/