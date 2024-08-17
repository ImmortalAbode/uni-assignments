#ifndef MYFUNCS_H_
#define MYFUNCS_H_
/*����� ������� ����� � ������*/
void PrintDash();
void PrePrint();
void PrintMenu();

/*������� �������� ����������������� �����*/
bool checkStrIsNumeric(std::string const& userStr);
double getEpsilon();
char GetChoice();
double convertStrToNumber(std::string const& convertStr);

/*������� ������ ���������� �����*/
void Print�ommonTable();
void PrintRungeKuttTable();

/*������ �������*/
double MyFunction(const double x_i, const double y_i);
double GetExactValue(const double x_i);

/*������� ������ ����������� ��������*/
void PrintFirstSecondTable(const double n);
void PrintThirdFourthTable(const double n, const double epsilon);

/*��������� �������*/
void ExactSolution(const double x_i);
void EulerMethod(const double h, const double x_i, double& y_i);
void RungeKuttOrder4Method(const double h, const double x_i, double& y_i);
void AdamsMethod(const double h, double x_i[], double y_i[]);
double Calculation(const double h, const double x_i, const double y_i);
void RungeKuttOrder4WithRecalculationMethod(double& h, double& x_i, double& y_i, int& i, const double epsilon, double recalculation_x_y[]);

#endif /*MYFUNCS_H_*/