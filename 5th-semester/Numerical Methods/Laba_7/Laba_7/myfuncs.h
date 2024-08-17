#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <vector>

bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);

void prePrint();
void printDash();
void printTable();

void printMenu();
char getChoice();

int get_n_m_values(const char& n_or_m, const int& i);
long double get_step_h(const int& n);
long double get_step_k(const int& m);
long double get_f(const long double& x, const long double& y);
long double get_xi(const long double& i, const int& n);
long double get_yj(const long double& j, const int& m);
std::vector<std::vector<int>> get_lambda_matrix(const std::size_t& n, const std::size_t& m);

long double get_integral_simp_one(const long double& x);
long double get_integral_simp_two_part_one(const long double& t);
long double get_integral_simp_two_part_two(const long double& t);
void simpsonFormula(const int& n, const int& m);

#endif /* MYFUNCS_H_ */