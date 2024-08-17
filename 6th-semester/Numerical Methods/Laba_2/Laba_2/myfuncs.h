#ifndef MYFUNCS_H_
#define MYFUNCS_H_

/*ÎÁÙÈÅ ÔÓÍÊÖÈÈ ÂÂÎÄÀ È ÂÛÂÎÄÀ*/
void PrintDash();
void PrePrint();
void PrintMenu();

/*ÔÓÍÊÖÈÈ ÏĞÎÂÅĞÊÈ ÏÎËÜÇÎÂÀÒÅËÜÑÊÎÃÎ ÂÂÎÄÀ*/
char GetChoice();

/*ÂÑÏÎÌÎÃÀÒÅËÜÍÛÅ ÔÓÍÊÖÈ*/
double* get_mass_x(const int& n, const double& h);
double* get_mass_p(const double* const mass_x, const int& n, const double& h);
double* get_mass_q(const double* const mass_x, const int& n, const double& h);
double* get_mass_f(const double* const mass_x, const int& n, const double& h);
double* get_mass_m(const double* const mass_p, const double* const mass_q, const int& n, const double& h);
double* get_mass_r(const double* const mass_p, const int& n, const double& h);
double* get_mass_fi(const double* const mass_p, const double* const mass_f, const int& n, const double& h);
double* get_mass_c(const double* const mass_m, const double* const mass_r, const int& n, const double& h);
double* get_mass_d(const double* const mass_fi, const double* const mass_r, const double* const mass_c, const int& n, const double& h);
double* get_mass_y(const double* const mass_c, const double* const mass_d, const int& n, const double& h);

/*ÎÑÍÎÂÍÛÅ ÔÓÍÊÖÈÈ*/
void PrintTable();
void SweepMethod(const int& n);

#endif /*MYFUNCS_H_*/