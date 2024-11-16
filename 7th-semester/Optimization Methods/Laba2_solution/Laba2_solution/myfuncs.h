#ifndef MYFUNCS_H_
#define MYFUNCS_H_ 

#include <vector>
#include <fstream>

//Структура для удобного хранения точек симплекса.
struct Symplex_coords
{
    double x1{}; //первая координата
    double x2{}; //вторая координата
    double f{};  //значение функции в точке

    Symplex_coords() = default;
    Symplex_coords(const double x1_value, const double x2_value, const double f_value)
        : x1(x1_value), x2(x2_value), f(f_value) {};
};

/*ПОИСК ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ*/
static void PrintTableCurIter(std::ofstream& output_file, const int& iter, const double& t);
static void PrintResults(std::ofstream& output_file, const Symplex_coords current_points[], const double& t);
void SortPoints(Symplex_coords current_points[], const int& size);
static Symplex_coords Сentroid_n(const Symplex_coords mass_points[]);
static Symplex_coords Сentroid_n_minus_1(const Symplex_coords mass_points[]);
Symplex_coords Reflect(const Symplex_coords& worst, const Symplex_coords& XC);
void SearchByCorrectSymplex(std::ofstream& file, const double& epsilon, double& t);

/*ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ*/
static void PrintTableCurIter(std::ofstream& output_file, const int& iter);
static void PrintCurrentPoints(std::ofstream& output_file, const Symplex_coords mass_points[]);
static void PrintResults(std::ofstream& output_file, const Symplex_coords mass_points[]);
static bool AchievingPrecision(const Symplex_coords mass_points[], const Symplex_coords& X_n_plus_2, const double& epsilon);
static int MaxFValue(const Symplex_coords mass_points[]);
static int MinFValue(const Symplex_coords mass_points[]);
static Symplex_coords Centroid_h(const Symplex_coords mass_points[], const int& h);
static Symplex_coords Reflect(const Symplex_coords& X_n_plus_2, const Symplex_coords& Xh, const double& alpha);
static Symplex_coords Stretch(const Symplex_coords& X_n_plus_3, const Symplex_coords& X_n_plus_2, const double& gamma);
static Symplex_coords Contract(const Symplex_coords& Xh, const Symplex_coords& X_n_plus_2, const double& beta);
static void Reduce(Symplex_coords mass_points[], const Symplex_coords& XL);
bool Degenerate(const Symplex_coords mass_points[]);
void SearchByDeformablePolyhedron(std::ofstream& file, const double& epsilon, const double& alpha, const double& beta, const double& gamma);

/*ОБЩИЙ ВЫВОД*/
void PerformCorrectSymplex(std::ofstream& results_file, const double& epsilon, double t);
void PerformDeformablePolyhedron(std::ofstream& results_file, const double& epsilon, const double& alpha, const double& beta, const double& gamma);
void PrintTableHeader(std::ofstream& output_file);
static void PrintTableRow(std::ofstream& output_file, const std::string& pointName, const Symplex_coords& point);
double Function(const Symplex_coords& point);

#endif /* MYFUNCS_H_ */