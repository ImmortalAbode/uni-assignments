#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <vector>

/*ÎÁÙÈÅ ÔÓÍÊÖÈÈ ÂÂÎÄÀ È ÂÛÂÎÄÀ*/
void PrintDash();
void PrePrint();
void PrintMenu();

/*ÔÓÍÊÖÈÈ ÏĞÎÂÅĞÊÈ ÏÎËÜÇÎÂÀÒÅËÜÑÊÎÃÎ ÂÂÎÄÀ*/
char GetChoice();
bool checkStrIsNumeric(std::string const& userStr);
double getEpsilon();
double convertStrToNumber(std::string const& convertStr);

/*ÎÑÍÎÂÍÛÅ ÔÓÍÊÖÈÈ*/
void PrintHeadTable();
long long int GetValueOrder(const long double& num);
long long int LowerValueOrder(const long double& num);
long double UpdateDegrees(std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees, long double& num, const long long int& k, const long long int& s, const std::string& type);
int GetMaxLength(const std::vector<std::vector<std::vector<long double>>>& table);
void FindComplexColumns(const std::vector<std::vector<std::vector<long double>>>& table, long long int& first_complex_column, long long int& second_complex_column);
void Add2aa(std::vector<std::vector<long double>>& cur_row, std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees);
void AddNewCoef(std::vector<std::vector<std::vector<long double>>>& table, std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees);
void PrintTable(const std::vector<std::vector<std::vector<long double>>>& table, std::vector<std::vector<long long int>>& coefs_degrees, std::vector<std::vector<long long int>>& values_degrees);
bool Equal(const std::vector<std::vector<std::vector<long double>>>& table, const std::vector<std::vector<long long int>>& coefs_degrees, const long double& epsilon);
void GetSolutions(const std::vector<std::vector<std::vector<long double>>>& table, std::vector<std::vector<long long int>>& coefs_degrees, const long double& rude_up, const long double& rude_down);
void LobachevskyGraeffeAlgorithm(const long double& epsilon);

#endif /*MYFUNCS_H_*/