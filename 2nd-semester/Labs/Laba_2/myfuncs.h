#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool init(double mass[NM], double& a, int& n);
bool finit(std::ifstream& f, double mass[NM], double& a, int& n, double& b);
void forder(std::ostream& f, double mass[NM], double a, int n);
double checkValue();
double getValue_mass(int& n);
bool getNext();
unsigned char get_0_1();

#endif /*MYFUNCS_H_*/
