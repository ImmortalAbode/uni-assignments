#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <functional>
#include <map>
#include <vector>
#include <string>

#include "mystruct.h"

/*----------------------------------+
| ФУНКЦИИ ВЫВОДА ОСНОВНЫХ СООБЩЕНИЙ |
+-----------------------------------*/
void ShowTitle();
const int& MainMenu();
char GetCase(std::function<const int& ()> showMenu);
/*------------------------------+
| ФУНКЦИИ ВЫВОДА ФОРМАТИРОВАНИЯ |
+-------------------------------*/
std::string CenterText(const std::string& text, const int& width);
void DrawLine(const char& del);
/*-----------------------------------+
| ФУНКЦИИ ЧАСТОТНОГО АНАЛИЗА СИМВОЛОВ|
+------------------------------------*/
bool compare(const std::pair<unsigned char, CharStat>& a, const std::pair<unsigned char, CharStat>& b);
bool PrintFreqResults(const std::string& file, const std::map<unsigned char, CharStat>& chars_frequency);
void ComputePercentages(std::map<unsigned char, CharStat>& chars_frequency, const int& total_chars);
bool ExecuteFileAnalysis(const std::string& file, std::map<unsigned char, CharStat>& chars_frequency, int& total_chars);
void ExecuteSymbolFrequency();
/*--------------------------------------------+
| ФУНКЦИИ ДЕШИФРОВАНИЯ ФАЙЛА НА ОСНОВЕ АНАЛИЗА|
+---------------------------------------------*/
bool SaveSubstitutionTable(const std::vector<std::pair<unsigned char, unsigned char>>& substitution, const std::string& file);
bool ExecuteFileDecrypt(const std::string& freq1_file, const std::string& freq2_file, const std::string& encrypt_file, const std::string& decrypt_file, const std::string& table_file);
void ExecuteDecryptFile();

#endif /*MYFUNCS*/