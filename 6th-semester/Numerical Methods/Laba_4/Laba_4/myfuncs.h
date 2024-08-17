#ifndef MYFUNCS_H_
#define MYFUNCS_H_

/*наыхе тсмйжхх ббндю х бшбндю*/
void PrintDash();
void PrePrint();
void PrintMenu();

/*тсмйжхх опнбепйх онкэгнбюрекэяйнцн ббндю*/
bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);
char GetChoice();
long double GetaValue();

/*нямнбмше тсмйжхх*/
//бШБНД РЮАКХЖШ.
void printTable(const double* const& x, const double* const& t, const double* const* const& u_virtual, const double* const* const& u);
void GridMethod(const double& a);

#endif /*MYFUNCS_H_*/