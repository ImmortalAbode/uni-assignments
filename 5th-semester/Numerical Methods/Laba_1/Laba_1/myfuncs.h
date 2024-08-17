#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>

/*������� ��������� ������������� ����������������� �����*/
bool checkStrIsNumeric(std::string const& userStr);
double convertStrToNumber(std::string const& convertStr);

/*������� ������ ���������� �� �������*/
void prePrint();	
void printDash();
void printMenu();

/*��������������� �������*/
double getMaxOfThreeNumbers(const double& number_1, const double& number_2, const double& number_3);
char getChoice();

/*������� ����� �������� ������ ���������*/
double getEpsilon();
double getValueOfApproxCoordinate();
void getInitOfApproximation(double approximate_mass[]);

void printSIMandSMTable();
void simpleIterationMethod(const double& user_epsilon, const double user_approximate_mass[]);
void seidelMethod(const double& user_epsilon, const double user_approximate_mass[]);

void printRMTable();
void relaxationMethod(const double& user_epsilon, const double user_approximate_mass[]);

#endif /*MYFUNCS_H_*/