#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool init(double*** massOut, unsigned& NMOut);
bool finit(std::istream& f, double*** massOut, unsigned& NMOut, double& b);
void forder(std::ostream& f, double** mass, unsigned NM);
double getValue_mass(unsigned& NMOut);
double getValue();
bool makeMass(double*** massOut, unsigned NM);
bool getNext();
unsigned char get_0_1();

#endif /*MYFUNCS_H_*/
