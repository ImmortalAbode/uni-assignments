#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool init(double mass[NM], double& a, double& h, double& b, int& n);
bool finit(std::ifstream& f, double mass[NM], double& a, double& h, double& b, int& n);
void fsum(std::ostream& f, double mass[NM], double a, double h, double b, int n, double sum);
unsigned checkValue();
double getValue();
bool getNext();
unsigned char get_0_1();
bool checkValue_mass(int n);

#endif /*MYFUNCS_H_*/
