#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>

/*тсмйжхх напюанрйх мейнппейрмнцн онкэгнбюрекэяйнцн ббндю*/
bool checkStrIsNumeric(std::string const& userStr);
double convertStrToNumber(std::string const& convertStr);

/*тсмйжхх бшбндю хмтнплюжхх мю йнмянкэ*/
void prePrint();
void printDash();
void printMenu();

/*бяонлнцюрекэмше тсмйжхх*/
char getChoice();

/*тсмйжхх ббндю нямнбмшу дюммшу опнцпюллш*/
double getEpsilon();
double getDeltha();
double getValueOfApproxCoordinate();
void getInitOfApproximation_v2(double approximate_mass[]);
void getInitOfApproximation(double approximate_mass[]);

void printSIM_NM_MNM_table();
void simpleIterationMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[]);
void NewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[]);
void modifiedNewtonMethod(const double& user_epsilon, const double& user_deltha, const double user_approximate_mass[]);

#endif /*MYFUNCS_H_*/