#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>

#include "WorkWithFunc.h" //����� ��� ������ � ��������, �� ���� �������� ����� k, n, �������, � ����� �������� ����������� �������.
#include "RPN.h" //������ ���(���) (�������� �������� ������� (������)) ��� ����������� �������������� ������� � ���������������� �����. ����� �������� ���� ��� ��������� ���������� �� ���������.

/*������� ������ ��������� ����������*/
void PrePrint();
void MenuPrint();
char getChoice();

/*��������������� �������*/
int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string CharToStr(const char& sign);
std::string getNumber(const char& sign);
std::string get0_1();

/*������� ��� ��������� ������� ������*/
void getNumberK(Func*& func);
void getNumberN(Func*& func);
bool findErrorSubstr(std::string const& func);
bool functionIsOK(const Func* func, std::string const& user_func);
void getFunction(Func*& func);

/*������� ��� �������������� �������� ������� � �������� �������� �������*/
void AddOutStringNewElem(const char& sign, OutString*& cur_char);
void AddStackNewElem(const char& sign, Stack*& sp);
void addOutStringNewElemFromStack(Stack*& sp, OutString*& cur_char);
void getRPNstring(Func*& func, Stack*& sp, OutString*& RPN_string);

/*�������, ������������� �������� �������� ������� � ��������� �� �����*/
void AddElemResult(Result*& cur_res, const int& value);
int getResult(OutString*& outstring, const int& x, const int& y, const int& k);

/*������� ������ �������� �������� ������� � ���� �������*/
void getValuesOfFunc(Func*& func, Stack*& stack_signs, OutString*& RPN_string, int*& result_of_function);

/*������� ��������� ������� ���� �������� �������*/
void getSKNFform(Func*& func, int*& result_of_function);

/*������� ��������� ���������� � �������������� �������� ������� ������ T(E) � ���������� ��������� E*/
bool checkStrForCorrect(std::string const& userStr, Func*& func, int*& mass_of_save_values, int& count_of_save_values);
std::string getValueString(Func*& func, int*& mass_of_save_values, int& count_of_save_values);
void printMassOfSaveValues(const int* mass_of_save_values, const int& count_of_save_values);
void getSaveData(Func*& func, int*& result_of_function);

/*������� �������� �������� � �������� ������*/
void ClearSomeStructs(int*& result_of_function, OutString*& RPN_string);
void clearAllStructs(Func*& func, Stack*& stack_signs, OutString*& RPN_string);

#endif /*MYFUNCS_H_*/