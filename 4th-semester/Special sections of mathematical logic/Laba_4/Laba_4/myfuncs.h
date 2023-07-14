#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>

#include "WorkWithFunc.h" //Нужен для работы с функцией, то есть хранения числа k, n, функции, а также хранения результатов функции.
#include "RPN.h" //Хранит ОПН(ОПЗ) (обратная польская нотация (запись)) для правильного преобразования функции в удобосчитываемую форму. Также содержит стек для получения результата по операциям.

/*ФУНКЦИИ ПЕЧАТИ НАЧАЛЬНОЙ ИНФОРМАЦИИ*/
void PrePrint();
void MenuPrint();
char getChoice();

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
int convertStrToInt(std::string const& convertStr);
bool checkStrIsNumeric(std::string const& userStr);
std::string CharToStr(const char& sign);
std::string getNumber(const char& sign);
std::string get0_1();

/*ФУНКЦИИ ДЛЯ ПОЛУЧЕНИЯ ВХОДНЫХ ДАННЫХ*/
void getNumberK(Func*& func);
void getNumberN(Func*& func);
bool findErrorSubstr(std::string const& func);
bool functionIsOK(const Func* func, std::string const& user_func);
void getFunction(Func*& func);

/*ФУНКЦИИ ДЛЯ ПРЕОБРАЗОВАНИЯ ИСХОДНОЙ ФУНКЦИИ В ОБРАТНУЮ ПОЛЬСКУЮ НОТАЦИЮ*/
void AddOutStringNewElem(const char& sign, OutString*& cur_char);
void AddStackNewElem(const char& sign, Stack*& sp);
void addOutStringNewElemFromStack(Stack*& sp, OutString*& cur_char);
void getRPNstring(Func*& func, Stack*& sp, OutString*& RPN_string);

/*ФУНКЦИИ, ПРЕОБРАЗУЮЩИЕ ОБРАТНУЮ ПОЛЬСКУЮ НОТАЦИЮ В РЕЗУЛЬТАТ НА СТЕКЕ*/
void AddElemResult(Result*& cur_res, const int& value);
int getResult(OutString*& outstring, const int& x, const int& y, const int& k);

/*ФУНКЦИЯ ПЕЧАТИ ЗНАЧЕНИЙ ЗАДАННОЙ ФУНКЦИИ В ВИДЕ ТАБЛИЦЫ*/
void getValuesOfFunc(Func*& func, Stack*& stack_signs, OutString*& RPN_string, int*& result_of_function);

/*ФУНКЦИЯ ПОЛУЧЕНИЯ АНАЛОГА СКНФ ЗАДАННОЙ ФУНКЦИИ*/
void getSKNFform(Func*& func, int*& result_of_function);

/*ФУНКЦИИ ПОЛУЧЕНИЯ ИНФОРМАЦИИ О ПРИНАДЛЕЖНОСТИ ЗАДАННОЙ ФУНКЦИИ КЛАССУ T(E) И СОХРАНЕНИЕ МНОЖЕСТВА E*/
bool checkStrForCorrect(std::string const& userStr, Func*& func, int*& mass_of_save_values, int& count_of_save_values);
std::string getValueString(Func*& func, int*& mass_of_save_values, int& count_of_save_values);
void printMassOfSaveValues(const int* mass_of_save_values, const int& count_of_save_values);
void getSaveData(Func*& func, int*& result_of_function);

/*ФУНКЦИИ ОЧИЩЕНИЯ МАССИВОВ И СТРУКТУР ДАННЫХ*/
void ClearSomeStructs(int*& result_of_function, OutString*& RPN_string);
void clearAllStructs(Func*& func, Stack*& stack_signs, OutString*& RPN_string);

#endif /*MYFUNCS_H_*/