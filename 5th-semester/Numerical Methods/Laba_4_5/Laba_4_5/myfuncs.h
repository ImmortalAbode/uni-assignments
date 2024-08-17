#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>

/*������� ��������� ������������� ����������������� �����*/
bool checkStrIsNumeric(std::string const& userStr);
long double convertStrToNumber(std::string const& convertStr);

/*������� ������ ���������� �� �������*/
void prePrint();
void printDash();
void printMenu();

/*��������������� �������*/
char getChoice();
long double getX();
void getValuesXFromUser(long double user_values_of_X[]);

/*������� ������ �������� ������ ���������*/
void printTableInterpolation();
void printTableNumericalDefferentiation();

/*�������� ������� ���������*/
void  interpolation_formulas(long double user_values_of_X[]);
long double getClosestToX(const long double& cur_x_value, const int& method);
void numerical_differentation_formulas(long double user_values_of_X[]);

#endif /*MYFUNCS_H_*/