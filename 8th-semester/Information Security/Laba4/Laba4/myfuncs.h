#ifndef MEFUNCS_H_
#define MYFUNVS_H_

#include <string>
#include <vector>
#include <functional>

/*-----------------+
| ФУНКЦИИ ПРОВЕРОК |
+------------------*/
const std::string CheckMixedAlphabet(const std::string& text);
char LowerToUpper(const char& c, const std::string& type_alphabet);
/*----------------------------------+
| ФУНКЦИИ ВЫВОДА ОСНОВНЫХ СООБЩЕНИЙ |
+-----------------------------------*/
void ShowTitle();
const int& MainMenu();
char GetCase(std::function<const int& ()> showMenu);
/*----------------------------------+
| ФУНКЦИИ ВЫВОДА ТАБЛИЦ ПОДСТАНОВОК |
+-----------------------------------*/
void HorizontalDoubleLineForTable(const int& col_width);
void HorizontalLineForTable(const int& col_width);
std::string CenterText(const std::string& text, const int& width);
void DrawLine();
void DisplayContourPolyTable(const std::string& type_alphabet, const std::string& text, const std::vector<std::string>& keys);
/*----------------------------------------+
| ФУНКЦИИ РЕАЛИЗАЦИИ АЛГОРИТМА ШИФРОВАНИЯ |
+-----------------------------------------*/
bool CheckKeyCorrect(const std::string& type_alphabet, const std::string& key);
int GetShift(const char& c_key, const std::string& type_alphabet);
char EncryptChar(const char& c, const int& shift, const std::string& alphabet, const int& M);
std::string ProcessWithKey(const std::string& text, const std::string& key, const std::string& type_alphabet, const bool& encrypt);
std::string ProcessText(const std::string& text, const std::vector<std::string>& keys, const std::string& type_alphabet, bool encrypt);
std::string ContourPolyEncryption(const std::string& text, const std::vector<std::string>& keys, const std::string& type_alphabet);
std::string ContourPolyDecryption(const std::string& text, const std::vector<std::string>& keys, const std::string& type_alphabet);
void EcexuteContourPolySub();

#endif /*MYFUNCS_H_*/