#include "myfuncs.h"
#include "constants.h"
#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>

/*--------------------------------
 |����� �� ����������� ��������� |
 --------------------------------*/
//������ � ���� �������������� ������ ������.
static void PrintTableCurIter(std::ofstream& output_file, const int& iter, const double& t)
{
    output_file << std::setw(10) << iter
        << std::setw(65) << "t = " << t
        << std::endl;
}
//������ � ���� �����������.
static void PrintResults(std::ofstream& output_file, const Symplex_coords mass_points[], const double& t) 
{
    output_file << std::endl << "�������� ��������:" << std::endl;
    for (int i{}; i < n + 1; ++i)
        PrintTableRow(output_file, "X^" + std::to_string(i), mass_points[i]);
    Symplex_coords x_middle = Symplex_coords((mass_points[0].x1 + mass_points[1].x1 + mass_points[2].x1) / 3,
        (mass_points[0].x2 + mass_points[1].x2 + mass_points[2].x2) / 3, NAN);
    x_middle.f = Function(x_middle);
    output_file << std::setw(10) << ""
        << std::setw(10) << "X��."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << x_middle.f
        << std::setw(10) << "t = " << t
        << std::endl;
}
//���������� ������ � ������� F(X0)<=F(X1)<=...<=F(XN).
void SortPoints(Symplex_coords current_points[], const int& size)
{
    //����������� ����������.
    for (int i{}; i < size; i++)
    {
        for (int j{ i + 1 }; j < size; j++)
        {
            if (current_points[j].f <= current_points[i].f)
            {
                Symplex_coords temp = current_points[i];
                current_points[i] = current_points[j];
                current_points[j] = temp;
            }
        }
    }
}
//����� ������ ������� XC ������ X0,X1,...,X(N-1).
static Symplex_coords �entroid_n(const Symplex_coords mass_points[])
{
    Symplex_coords XC{};
    for (int j{}; j < n; j++)
    {
        XC.x1 += mass_points[j].x1;
        XC.x2 += mass_points[j].x2;
    }
    XC.x1 *= 1.0f / n;
    XC.x2 *= 1.0f / n;
    return XC;
}
//����� ������ ������� Xc ������ X0,X1,...,X(N-2),XN.
static Symplex_coords �entroid_n_minus_1(const Symplex_coords mass_points[])
{
    Symplex_coords XC{};
    for (int i{}; i <= n; ++i) {
        if (i != n - 1) 
        {
            XC.x1 += mass_points[i].x1;
            XC.x2 += mass_points[i].x2;
        }
    }
    XC.x1 *= 1.0f / n;
    XC.x2 *= 1.0f / n;
    return XC;
}
//������� ��� ��������� �����. ��� ���� 5.
Symplex_coords Reflect(const Symplex_coords& worst, const Symplex_coords& XC)
{
    return { 2 * XC.x1 - worst.x1, 2 * XC.x2 - worst.x2, NAN };
}
//������� ������� ������ �� ����������� ���������.
void SearchByCorrectSymplex(std::ofstream& file, const double& epsilon, double& t) 
{
    /*-------------------
     | �������� ������� |
     -------------------*/
    //��� 0: ���������� ���������� ���������.
    Symplex_coords X0{}, X1{}, X2{};
    X0.x1 = 5; X0.x2 = 6; //������� ����� X^0.
    double d1{ t / (n * sqrt(2)) * (sqrt(n + 1) + n - 1) },
        d2{ t / (n * sqrt(2)) * (sqrt(n + 1) - 1) };

    X1.x1 = X0.x1 + d1; X1.x2 = X0.x2 + d2;
    X2.x1 = X0.x1 + d2; X2.x2 = X0.x2 + d1;

    //��� �������� ����� �������� ���������.
    Symplex_coords mass_points[n + 1]{ X0, X1, X2 };
    
    //��� ����� ��������.
    int iter{}; 
    //������ ����������
    PrintTableHeader(file);

    while (true) 
    {
        //��� 1: ���������� �������� �������.
        for (int i{}; i < n + 1; i++)
            mass_points[i].f = Function(mass_points[i]);

        //��� 2: ���������� �� ��������� �������.
        SortPoints(mass_points, n + 1);
        //����� ������ � ������� �������� � t.
        PrintTableCurIter(file, iter, t);
        //����� ������� ������.
        for (int i{}; i < n + 1; ++i)
            PrintTableRow(file, "X^" + std::to_string(i), mass_points[i]);

        // ��� 3: �������� ������� ���������� ��������.
        double sum_achieving{};
        for (int j{ 1 }; j <= n; j++)
            sum_achieving += pow(mass_points[j].f - mass_points[0].f, 2);
        double cur_achieving{ 1.0f / n * sum_achieving };
        if (cur_achieving < epsilon)
        {
            //��� 7: ���������� ����������.
            std::cout << "�������� ������ �� ����������� ��������� ����������. ���������� �������� � ���� */outResFile_regularSymplex.txt." << std::endl;
            break;
        }

        // ��� 4.
        Symplex_coords XC = �entroid_n(mass_points);
        Symplex_coords XR = Reflect(mass_points[n], XC);
        XR.f = Function(XR);

        if (XR.f < mass_points[n].f)
        {
            mass_points[n] = XR;
            iter++;
            continue; // ������� � ���� 2.
        }

        // ��� 5.
        XC = �entroid_n_minus_1(mass_points);
        XR = Reflect(mass_points[n - 1], XC);
        XR.f = Function(XR);

        if (XR.f < mass_points[n - 1].f)
        {
            mass_points[n] = XR;
            iter++;
            continue; // ������� � ���� 2.
        }

        // ��� 6. ������ ���������.
        t = t / 2;
        for (int i{ 1 }; i < n + 1; ++i) 
        {
            mass_points[i].x1 = (mass_points[i].x1 + mass_points[0].x1) / 2;
            mass_points[i].x2 = (mass_points[i].x2 + mass_points[0].x2) / 2;
        }

        iter++;
    }

    // ��� 7.
    PrintResults(file, mass_points, t);
}

/*---------------------------------------
 |����� �� �������������� ������������� |
 ---------------------------------------*/
 //������ � ���� �������������� ������ ������.
static void PrintTableCurIter(std::ofstream& output_file, const int& iter) 
{
    output_file << std::setw(10) << iter
        << std::endl;
}
//������� � ���� ������� ������.
static void PrintCurrentPoints(std::ofstream& output_file, const Symplex_coords mass_points[]) 
{
    for (int i{}; i < n + 1; ++i) 
        PrintTableRow(output_file, "X^" + std::to_string(i + 1), mass_points[i]);
}
//������ � ���� �����������.
static void PrintResults(std::ofstream& output_file, const Symplex_coords mass_points[])
{
    output_file << std::endl << "�������� ��������:" << std::endl;
    for (int i{}; i < n + 1; ++i)
        PrintTableRow(output_file, "X^" + std::to_string(i + 1), mass_points[i]);
    Symplex_coords x_middle = Symplex_coords((mass_points[0].x1 + mass_points[1].x1 + mass_points[2].x1) / 3,
        (mass_points[0].x2 + mass_points[1].x2 + mass_points[2].x2) / 3, NAN);
    x_middle.f = Function(x_middle);
    output_file << std::setw(10) << ""
        << std::setw(10) << "X��."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << x_middle.f
        << std::endl;
}
// �������� �������� ��������� ������.
static bool AchievingPrecision(const Symplex_coords mass_points[], const Symplex_coords& X_n_plus_2, const double& epsilon)
{
    double sum_achieving{};
    for (int j{}; j < n + 1; ++j)
        sum_achieving += pow(mass_points[j].f - X_n_plus_2.f, 2);
    long double accuracy = sqrt(sum_achieving / (n + 1));
    if (accuracy <= epsilon)
    {
        std::cout << "�������� ������ �� �������������� ������������� ����������. ���������� �������� � ���� */deformablePolyhedron.txt." << std::endl;
        return true;
    }
    return false;
}
//����� ������ ������� Xh, �������� ������� � ������� ������������.
static int MaxFValue(const Symplex_coords mass_points[])
{
    int h{};
    for (int i{}; i < n + 1; ++i)
        if (mass_points[i].f > mass_points[h].f)
            h = i;
    return h;
}
//����� ������ ������� XL, �������� ������� � ������� �����������.
static int MinFValue(const Symplex_coords mass_points[])
{
    int L{};
    for (int i{}; i < n + 1; ++i)
        if (mass_points[i].f < mass_points[L].f)
            L = i;
    return L;
}
//����� ������� X^(n+2) ���� ������, �������� Xh.
static Symplex_coords Centroid_h(const Symplex_coords mass_points[], const int& h)
{
    Symplex_coords n_plus_2{};
    for (int i{}; i < n + 1; ++i) 
    {
        if (i != h) 
        {
            n_plus_2.x1 += mass_points[i].x1;
            n_plus_2.x2 += mass_points[i].x2;
        }
    }
    n_plus_2.x1 *= 1.0f / n;
    n_plus_2.x2 *= 1.0f / n;
    return n_plus_2;
}
//��������� ������� Xh ����� ����� ������� X^(n+2).
static Symplex_coords Reflect(const Symplex_coords& X_n_plus_2, const Symplex_coords& Xh, const double& alpha) {
    Symplex_coords X_n_plus_3{};
    X_n_plus_3.x1 = X_n_plus_2.x1 + alpha * (X_n_plus_2.x1 - Xh.x1);
    X_n_plus_3.x2 = X_n_plus_2.x2 + alpha * (X_n_plus_2.x2 - Xh.x2);
    return X_n_plus_3;
}
// ���������� ������� X(n+3)-X(n+2).
static Symplex_coords Stretch(const Symplex_coords& X_n_plus_3, const Symplex_coords& X_n_plus_2, const double& gamma) 
{
    Symplex_coords X_n_plus_4{};
    X_n_plus_4.x1 = X_n_plus_2.x1 + gamma * (X_n_plus_3.x1 - X_n_plus_2.x1);
    X_n_plus_4.x2 = X_n_plus_2.x2 + gamma * (X_n_plus_3.x2 - X_n_plus_2.x2);
    return X_n_plus_4;
}
// ������ ������� Xh-X(n+2).
static Symplex_coords Contract(const Symplex_coords& Xh, const Symplex_coords& X_n_plus_2, const double& beta) 
{
    Symplex_coords X_n_plus_5{};
    X_n_plus_5.x1 = X_n_plus_2.x1 + beta * (Xh.x1 - X_n_plus_2.x1);
    X_n_plus_5.x2 = X_n_plus_2.x2 + beta * (Xh.x2 - X_n_plus_2.x2);
    return X_n_plus_5;
}
// �������� �������� Xj-XL � 2 ����.
static void Reduce(Symplex_coords mass_points[], const Symplex_coords& XL)
{
    for (int j{}; j < n + 1; ++j) 
    {
        mass_points[j].x1 = XL.x1 + (mass_points[j].x1 - XL.x1) / 2;
        mass_points[j].x2 = XL.x2 + (mass_points[j].x2 - XL.x2) / 2;
    }
}
//��������, ����� ������������ ����������� � ���������� ����������� ������ ������������.
bool Degenerate(const Symplex_coords mass_points[])
{
    const double value{ mass_points[0].f };
    for (int i{ 1 }; i < n + 1; ++i)
        if (mass_points[i].f != value)
            return false;
    return true;
}
//������� ������� ������ �� �������������� �������������.
void SearchByDeformablePolyhedron(std::ofstream& file, const double& epsilon, const double& alpha, const double& beta, const double& gamma)
{
    /*-------------------
     | �������� ������� |
     -------------------*/
    //��������� ������������.
    Symplex_coords X1{ 8, 9, NAN },
        X2{ 10, 11, NAN },
        X3{ 8, 11, NAN };
    Symplex_coords mass_points[3]{ X1, X2, X3 };
    //���������� �������� ������� � �������� X1, X2, X3.
    for (int i{}; i < n + 1; i++)
        mass_points[i].f = Function(mass_points[i]);

    //��� ��������� ��������� �������, � ������� F(X) ����� ������ ��������.
    Symplex_coords X_n_plus_2{}; //����� ������� X^(n+2).
    Symplex_coords X_n_plus_3{}; //��������� - X^(n+3).
    Symplex_coords X_n_plus_4{}; //���������� - X^(n+4).
    Symplex_coords X_n_plus_5{}; //������ - X^(n+5).

    int iter{}; // ��� ����� ����� ��������.

    //����� � ���� �������� ������.
    PrintTableHeader(file); //����� ��������� ������� � ����.
    PrintTableCurIter(file, iter); // ����� ������ � ������� ��������.
    PrintCurrentPoints(file, mass_points); // ����� ������� ������.

    while (true)
    {
        int h = MaxFValue(mass_points); //����� �������, �������� ������� � ������� �����������, - Xh (������).
        int L = MinFValue(mass_points); //����� �������, �������� ������� � ������� ����������, - XL (������).
        //����� �������.
        X_n_plus_2 = Centroid_h(mass_points, h);
        X_n_plus_2.f = Function(X_n_plus_2);

        //�������� �������� ��������� ������.
        if (AchievingPrecision(mass_points, X_n_plus_2, epsilon))
            break;
        //����� ������ � ������� ��������.
        PrintTableCurIter(file, iter + 1);

        //���������.
        X_n_plus_3 = Reflect(X_n_plus_2, mass_points[h], alpha);
        X_n_plus_3.f = Function(X_n_plus_3);

        //���� ���������� ������� ����� �� ������ ������, �� ����� ����� ��������� ����������, ����� - ������.
        //�������� �� ������.
        //���������� ������� ���� ��������� ������, �� ����� ������?
        bool contract{ true };
        for (int j{}; j < n + 1; ++j)
        {
            if (j != h)
            {
                if (!(X_n_plus_3.f > mass_points[j].f) || X_n_plus_3.f > mass_points[h].f)
                {
                    contract = false;
                    break;
                }
            }
        }
        //�������� �� ����������.
        //���������� ������� �� ������ ����� ������?
        if (X_n_plus_3.f < mass_points[h].f && !contract)
        {
            //����������.
            X_n_plus_4 = Stretch(X_n_plus_3, X_n_plus_2, gamma);
            X_n_plus_4.f = Function(X_n_plus_4);
            //���������� ���������� ������� ����� ������ � ����� ����������?
            if (X_n_plus_4.f < mass_points[L].f && X_n_plus_4.f < X_n_plus_3.f)
            {
                //���� ��, �� ������ ������� = ���������� ���������� �������.
                file << "����� ���� " << iter << " ��������� ���������->����������." << std::endl;
                mass_points[h] = X_n_plus_4; // Xh = X^(n+4).
                PrintCurrentPoints(file, mass_points);
                iter++;
                continue;
            }
            else
            {
                //����� ������ ������� = ����������.
                file << "����� ���� " << iter << " ��������� ���������." << std::endl;
                mass_points[h] = X_n_plus_3; // Xh = X^(n+3).
                PrintCurrentPoints(file, mass_points);
                iter++;
                continue;
            }
        }

        //������.
        //���� ����� ����� ��������� ������, � ��������� � ���������� �� ���� ������ �����������.
        if (contract)
        {
            file << "����� ���� " << iter << " ��������� ������." << std::endl;
            X_n_plus_5 = Contract(mass_points[h], X_n_plus_2, beta);
            X_n_plus_5.f = Function(X_n_plus_5);
            mass_points[h] = X_n_plus_5; // Xh = X^(n+5).
            PrintCurrentPoints(file, mass_points);
            iter++;
            continue;
        }
        //��������.
        //���������� ������� ��� ����, ��� ������ => ��������.
        if (X_n_plus_3.f > mass_points[h].f)
        {
            file << "����� ���� " << iter << " ��������� ��������." << std::endl;
            Reduce(mass_points, mass_points[L]);
            for (int i{}; i < n + 1; ++i)
                mass_points[i].f = Function(mass_points[i]);
            PrintCurrentPoints(file, mass_points);
            iter++;
            continue;
        }

        //��������, ����� ������������ �����������.
        if (Degenerate(mass_points))
        {
            file << "����� ���� " << iter << " ������������� ������������ ���������. ����������� ���� �������� ���������." << std::endl;
            break;
        }
    }
    PrintResults(file, mass_points);
}

/*----------------
 | ����� ������� |
 ----------------*/
 //������� ��� ���������� ������ �� ����������� ��������� � ��������� �����������.
void PerformCorrectSymplex(std::ofstream& results_file, const double& epsilon, double t)
{
    for (int i{}; i <= 99; ++i)
        results_file << "-";
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "t = " << t << "." << std::endl;
    SearchByCorrectSymplex(results_file, epsilon, t);
}
//������� ��� ���������� ������ �� �������������� �������������.
void PerformDeformablePolyhedron(std::ofstream& results_file, const double& epsilon, const double& alpha, const double& beta, const double& gamma) {
    for (int i{}; i < 99; ++i)
        results_file << "-";
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << "." << std::endl;
    SearchByDeformablePolyhedron(results_file, epsilon, alpha, beta, gamma);
}
//������ � ���� ��������� �������.
void PrintTableHeader(std::ofstream& output_file) {
    output_file << std::setw(10) << "��������"
        << std::setw(10) << "�����"
        << std::setw(15) << "x1"
        << std::setw(15) << "x2"
        << std::setw(15) << "F(X)"
        << std::endl;
}
//������ � ���� ������ �������.
static void PrintTableRow(std::ofstream& output_file, const std::string& pointName, const Symplex_coords& point)
{
    output_file << std::setw(20) << pointName
        << std::setw(15) << point.x1
        << std::setw(15) << point.x2
        << std::setw(15) << point.f
        << std::endl;
}
//���������� �������� �������� ������� F(X)=4*x1^2 + x2^2 - 40*x1 - 12*x2 + 136.
double Function(const Symplex_coords& point)
{
    return (4 * pow(point.x1, 2) + pow(point.x2, 2) - 40 * point.x1 - 12 * point.x2 + 136);
}